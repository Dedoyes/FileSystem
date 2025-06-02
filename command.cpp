#include "command.hpp"
#include "general.hpp"
#include "user.hpp"

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
}

void logout () {
    if (currentUserId == -1) {
        std::cout << "Now is no user." << std::endl;
        return;
    }
    currentUserId = -1;
    std::cout << "log out success." << std::endl;
}
