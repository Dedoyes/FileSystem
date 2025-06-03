#include "command.hpp"
#include "SuperBlock.hpp"
#include "fileTree.hpp"
#include "general.hpp"
#include "inodeTree.hpp"
#include "user.hpp"
#include "IndexNode.hpp"
#include "utilize.hpp"
#include "fileOpenTable.hpp"

void formatDisk (std::string diskName) {
    if (diskName == VDISK_START_FILE) {
        
    } else if (diskName == VDISK_FILE) {

    } else {
        std::cout << "Warning : No such disk." << std::endl;
    }
}

extern short currentAddress;
extern short currentUserId;
extern UserCluster userGroup; 

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

extern fileTree ft;
extern SuperBlock super;
extern inodeForest forest;
extern DiskIndexNodeCluster cluster;

void mkdir (std::string dirName, bool general) {
    std::cout << "in mkdir function." << std::endl;
    DiskIndexNode node;
    node.init (currentUserId, DIRETORY, general);
    std::cout << "ok" << std::endl;
    inodeTree tree;
    int index = node.getIndex ();
    int freeblock = super.askFreeBlock ();
    std::cout << "index = " << index << std::endl;
    std::cout << "freeblock = " << freeblock << std::endl;
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
            std::cout << "Warning : " << fileName << "has been existed!" << std::endl;
            return;
        }
    }
    DiskIndexNode node;
    node.init (currentUserId, REGULAR_FILE, false);
    inodeTree tree;
    int index = node.getIndex ();
    int freeblock = super.askFreeBlock ();
    std::cout << "index = " << index << std::endl;
    std::cout << "freeblock = " << freeblock << std::endl;
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

void cd (std::string dirName) {
    if (dirName == "..") {
        if (!currentAddress)
            return;
        currentAddress = ft.father[currentAddress];
        return;
    }
    for (auto x : ft.son[currentAddress]) {
        if (cluster[x].getType () != DIRETORY)
            continue;
        if (ft.fileName[x] == dirName && hasRead (cluster[x].getPermission(currentUserId))) {
            currentAddress = x;
            return;
        }
    }
    std::cout << "No such dir" << std::endl;
}

extern fileOpenTable table;

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
