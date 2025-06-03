#include "command.hpp"
#include "SuperBlock.hpp"
#include "fileTree.hpp"
#include "general.hpp"
#include "inodeTree.hpp"
#include "user.hpp"
#include "IndexNode.hpp"

void formatDisk (std::string diskName) {
    if (diskName == VDISK_START_FILE) {
        
    } else if (diskName == VDISK_FILE) {

    } else {
        std::cout << "Warning : No such disk." << std::endl;
    }
}

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
}

void logout () {
    if (currentUserId == -1) {
        std::cout << "Now is no user." << std::endl;
        return;
    }
    currentUserId = -1;
    std::cout << "log out success." << std::endl;
}

extern int currentAddress;
extern fileTree ft;
extern SuperBlock super;
extern inodeForest forest;
extern DiskIndexNodeCluster cluster;

void create (std::string fileName) {
    DiskIndexNode node;
    node.init (currentUserId);
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
