#include <fstream>
#include <unistd.h>
#include "command.hpp"
#include "SuperBlock.hpp"
#include "fileTree.hpp"
#include "general.hpp"
#include "inodeTree.hpp"
#include "user.hpp"
#include "IndexNode.hpp"
#include "utilize.hpp"
#include "fileOpenTable.hpp"

extern short currentUserId;
extern std::string fileStr[MAX_BLOCK_NUM];
extern SuperBlock super;
extern inodeForest forest;
extern DiskIndexNodeCluster cluster;
extern fileTree ft;
extern UserCluster userGroup;
extern short currentAddress;
extern fileOpenTable table;

void chmod (std::string fileName, short newId, std::string newPermission) {
    bool flag = false;
    for (auto x : ft.son[currentAddress]) {
        if (ft.fileName[x] == fileName) {
            flag = true;
            break;
        }
    }
    if (!flag) {
        std::cout << "Warning : no such file." << std::endl;
        return;
    }
    std::string dirPath = ft.getFilePath (currentAddress);
    std::string absPath = dirPath + fileName;
    if (!table.count (absPath)) {
        open (fileName);
    }
    int index = table.getIndex (absPath);
    if (cluster[index].getOwnerId () != currentUserId) {
        std::cout << "Sorry, you don't have permission :(" << std::endl;
        return;
    }
    cluster[index].changeStoragePermission (newPermission, newId, currentUserId);
}

void writeFile (std::string fileName, std::string content) {
    bool flag = false;
    for (auto x : ft.son[currentAddress]) {
        if (ft.fileName[x] == fileName && cluster[x].getType () == REGULAR_FILE) {
            flag = true;
            break;
        } 
    }
    if (!flag) {
        std::cout << "Warning : no such file." << std::endl;
        return;
    }
    std::string dirPath = ft.getFilePath (currentAddress);
    std::string absPath = dirPath + fileName;
    if (!table.count (absPath)) {
        open (fileName);
    }
    int index = table.getIndex (absPath);
    if (!hasWrite (cluster[index].getPermission (currentUserId))) {
        std::cout << "Sorry, you don't have permission :(" << std::endl;
        return;
    }
    inodeTree tree = forest[index];
    int len = cluster[index].getFileLength ();
    int rearLen = len % BLOCK_SIZE;
    flag = true;
    for (int l = 0, r = 0; l < content.size (); l = r) {
        int blockId = tree.lastAddress ();
        int start = flag ? rearLen : 0;
        int end = BLOCK_SIZE - 1;
        int freeLen = end - start + 1;
        if (freeLen < content.size () - 1 - l + 1) {
            r = l + freeLen;
            write_block (blockId, start, content.substr (l, r).c_str ());
            blockId = super.askFreeBlock ();
            super.occupyBlock (blockId);
            tree.assignAddress (blockId);
        } else {
            r = content.size ();
            write_block (blockId, start, content.substr (l, r).c_str ());
        }
        flag = false;
    }
    cluster[index].changeFileLength (len + content.size ());
}

void readFile (std::string fileName) {
    bool flag = false;
    for (auto x : ft.son[currentAddress]) {
        if (ft.fileName[x] == fileName && cluster[x].getType () == REGULAR_FILE) {
            flag = true;
            break;
        }
    }
    if (!flag) {
        std::cout << "Warning : no such file" << std::endl;
        return;
    }
    std::string dirPath = ft.getFilePath (currentAddress);
    std::string absPath = dirPath + fileName;
    if (!table.count (absPath)) {
        open (fileName);
    }
    int index = table.getIndex (absPath);
    if (!hasRead (cluster[index].getPermission (currentUserId))) {
        std::cout << "Sorry, you don't have permission :(" << std::endl;
        return;
    }
    inodeTree tree = forest[index];
    int fileLen = cluster[index].getFileLength ();
    std::cout << "fileLen = " << fileLen << std::endl;
    std::string res = "";
    if (fileLen == 0) {
        std::cout << std::endl;
        return;
    }
    for (int i = 0; i < tree.blockAddress.size (); i++) {
        auto x = tree.blockAddress[i];
        int len = BLOCK_SIZE;
        if (i == tree.blockAddress.size () - 1) {
            len = fileLen % BLOCK_SIZE;
            if (len == 0) 
                len = BLOCK_SIZE;
        }
        std::cout << "len = " << len << std::endl;
        std::vector <char> tempStr (len);
        read_block (x, 0, tempStr.data (), len);
        res.append (tempStr.begin (), tempStr.end ());
    }
    std::cout << res << std::endl;
}

void remove (std::string fileName) {
    std::string dirPath = ft.getFilePath (currentAddress);
    std::string absPath = dirPath + fileName;
    if (table.count (absPath)) {
        close (fileName);
    }
    int index = -1;
    for (auto x : ft.son[currentAddress]) {
        if (ft.fileName[x] == fileName && cluster[x].getType () == REGULAR_FILE) {
            index = x;
            break;
        }
    }
    if (index == -1) {
        std::cout << "Warning : No such File" << std::endl;
        return;
    }
    if (!hasExecute (cluster[index].getPermission (currentUserId))) {
        std::cout << "Sorry, you don't have permission :(" << std::endl;
    }
    inodeTree& tree = forest[index];
    for (auto x : tree.blockAddress) {
        super.realeaseBlockAddress (x);
    }
    super.realeaseIndexAddress (index);
    forest.erase (index);
    ft.cut (currentAddress, index);
    ft.fileName[index] = "";
}

void removeDir (std::string dirName) {
    bool flag = false;
    for (auto x : ft.son[currentAddress]) {
        if (ft.fileName[x] == dirName && cluster[x].getType () == DIRETORY) {
            flag = true;
            break;
        }
    }
    if (!flag) {
        std::cout << "Warning : No such directory." << std::endl;
        return;
    }
    std::string dirPath = ft.getFilePath (currentAddress);
    std::string absPath = dirPath + dirName;
    int index = ft.findIndex (currentAddress, dirName);
    if (!hasExecute (cluster[index].getPermission (currentUserId))) {
        std::cout << "Sorry, you don't have permission :(" << std::endl;
    }
    if (cluster[index].getType () == DIRETORY) {
        remove_rf (index);
    } else {
        std::cout << "Warning : this file isn't directory." << std::endl;
    }
}

void remove_rf (short index) {
    std::cout << "remove_rf " << index << std::endl;
    std::vector <short> vec;
    vec.clear ();
    for (auto x : ft.son[index]) 
        vec.push_back (x);
    for (auto x : vec) 
        remove_rf (x);
    if (cluster[index].getType () == REGULAR_FILE) {
        std::string filePath = ft.getFilePath (index);
        if (table.count (filePath)) {
            table.erase (filePath);
        }
    }
    inodeTree& tree = forest[index];
    for (auto x : tree.blockAddress) {
        super.realeaseBlockAddress (x);
    }
    super.realeaseIndexAddress (index);
    ft.cut (ft.father[index], index);
    ft.fileName[index] = "";
    forest.erase (index);
}

void varInit () {
    currentUserId = -1;
    for (int i = 0; i < MAX_BLOCK_NUM; i++)
        fileStr[i] = "";
    super = SuperBlock ();
    forest = inodeForest ();
    cluster = DiskIndexNodeCluster ();
    ft = fileTree ();
    userGroup = UserCluster ();
    currentAddress = 0;
    table = fileOpenTable ();
    mkdir ("", true);
}

void formatDisk () {
    std::ofstream ofs (VDISK_START_FILE, std::ios::trunc);
    FILE* start_disk = fopen (VDISK_START_FILE, "wb");
    if (!start_disk) {
        perror ("Failed to create virtual start disk");
        exit (1);
    }
    ftruncate (fileno (start_disk), START_DISK_SIZE);
    fclose (start_disk);
    varInit ();
    std::cout << "virtual disk format success." << std::endl;
    std::ofstream _ofs (VDISK_FILE, std::ios::trunc);
    FILE* disk = fopen (VDISK_FILE, "wb");
    if (!disk) {
        perror ("Failed to create virtual data disk");
        exit (1);
    }
    ftruncate (fileno (disk), DATA_DISK_SIZE);
    fclose (disk);
    std::cout << "data disk format success." << std::endl; 
}

void login (std::string userName, std::string password) {
    if (currentUserId != -1) {
        std::cout << "There is already an user." << std::endl;
        return;
    }
    for (int i = 0; i < userGroup.userNum; i++) {
        auto usr = userGroup.user[i];
        if (usr.getName () == userName) {
            if (currentUserId == usr.getUserId ()) {
                std::cout << "You have been logged :)" << std::endl;
                return;
            } else if (usr.getPassword () != password) {
                std::cout << "Sorry, your password is wrong." << std::endl;
                return;
            } else {
                std::cout << "log in success." << std::endl;
                currentUserId = usr.getUserId ();
                return;
            }
        }
    }
    userGroup.addNewUser (userName, password);
    std::cout << "add new user success." << std::endl;
    currentAddress = 0;
}

void logout () {
    if (currentUserId == -1) {
        std::cout << "Now is no user." << std::endl;
        return;
    }
    currentUserId = -1;
    std::cout << "log out success." << std::endl;
    currentAddress = 0;
}

void mkdir (std::string dirName, bool general) {
    for (auto x : ft.son[currentAddress]) {
        if (ft.fileName[x] == dirName && cluster[x].getType() == DIRETORY) {
            std::cout << "Warning: Directory with the same name already exists!" << std::endl;
            return;
        }
    }
    DiskIndexNode node;
    node.init (currentUserId, DIRETORY, general);
    //std::cout << "ok" << std::endl;
    inodeTree tree;
    int index = node.getIndex ();
    int freeblock = super.askFreeBlock ();
    //std::cout << "index = " << index << std::endl;
    //std::cout << "freeblock = " << freeblock << std::endl;
    super.occupyBlock (freeblock);
    tree.assignAddress (freeblock);
    forest.insert (tree, index);
    cluster.insert (node);
    ft.addNode (index, dirName);
    if (!general)
        ft.connect (currentAddress, index);
}

void create (std::string fileName) {
    for (auto x : ft.son[currentAddress]) {
        if (ft.fileName[x] == fileName) {
            std::cout << "Warning : " << fileName << " has been existed!" << std::endl;
            return;
        }
    }
    DiskIndexNode node;
    node.init (currentUserId, REGULAR_FILE, false);
    inodeTree tree;
    int index = node.getIndex ();
    int freeblock = super.askFreeBlock ();
    //std::cout << "index = " << index << std::endl;
    //std::cout << "freeblock = " << freeblock << std::endl;
    super.occupyBlock (freeblock);
    tree.assignAddress (freeblock);
    forest.insert (tree, index);
    cluster.insert (node);
    ft.addNode (index, fileName);
    ft.connect (currentAddress, index);
}

void ls () {
    for (auto x : ft.son[currentAddress]) {
        std::cout << ft.fileName[x];
        if (ft.deg[x] != 1) 
            std::cout << "/";
        std::cout << " ";
    }
    std::cout << std::endl;
}

void cd (std::string path) {
    if (path == "..") {
        if (!currentAddress)
            return;
        currentAddress = ft.father[currentAddress];
        return;
    }

    bool isAbsolute = !path.empty() && path[0] == '/';
    short addr = currentAddress;

    if (isAbsolute) {
        addr = 0; 
        path = path.substr(1);
    }
    std::vector<std::string> tokens;
    std::istringstream ss(path);
    std::string token;
    while (std::getline(ss, token, '/')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    if (tokens.empty()) {
        for (auto x : ft.son[addr]) {
            if (cluster[x].getType() == DIRETORY &&
                ft.fileName[x] == path &&
                hasRead(cluster[x].getPermission(currentUserId))) {
                currentAddress = x;
                return;
            }
        }
    } else {
        for (const auto& dir : tokens) {
            bool found = false;
            for (auto x : ft.son[addr]) {
                if (cluster[x].getType() == DIRETORY &&
                    ft.fileName[x] == dir &&
                    hasRead(cluster[x].getPermission(currentUserId))) {
                    addr = x;
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cout << "No such dir" << std::endl;
                return;
            }
        }
        currentAddress = addr;
        return;
    }

    std::cout << "No such dir" << std::endl;
}

void open (std::string fileName) {
    std::string dirPath = ft.getFilePath (currentAddress);
    std::string absPath = dirPath + fileName;
    if (table.count (absPath)) {
        std::cout << fileName << "is already existed" << std::endl;
        return;
    }
    short index = ft.findIndex (currentAddress, fileName);
    if (cluster[index].getType () == REGULAR_FILE) {
        table.storage (absPath, index);
    } else {
        std::cout << fileName << "isn't a regular file" << std::endl;
    }
}

void close (std::string fileName) {
    std::string dirPath = ft.getFilePath (currentAddress);
    std::string absPath = dirPath + fileName;
    if (!table.count (absPath)) {
        std::cout << fileName << "dosn't be opened" << std::endl;
        return;
    }
    table.erase (absPath);
}

void lopen () {
    table.print ();
}
