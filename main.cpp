#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include "general.hpp"
#include "IndexNode.hpp"
#include "inodeTree.hpp"
#include "fileTree.hpp"
#include "storage.hpp"
#include "user.hpp"
#include "utilize.hpp"
#include "FileTreePrinter.hpp"
#include "command.hpp"

short currentUserId = -1;
std::string fileStr[MAX_BLOCK_NUM];
SuperBlock super;
inodeForest forest;
DiskIndexNodeCluster cluster;
fileTree ft;
UserCluster userGroup;
short currentAddress;

int main () {
    FILE* start_disk = fopen (VDISK_START_FILE, "wb");
    if (!start_disk) {
        perror ("Failed to create virtual start disk");
        exit (1);
    }
    ftruncate (fileno (start_disk), 10 * 1024 * 1024);
    fclose (start_disk);
    std::cout << "virtual disk init success." << std::endl;
    while (true) {
        std::string command;
        std::string name;
        std::string address;
        if (currentUserId != -1) {
            name = userGroup.user[currentUserId].getName ();
        } 
        if (currentAddress == 0) {
            address = "/";
        } else {
            address = ft.getFilePath (currentAddress);
        }
        std::cout << address << "@" << name << ":";
        std::getline (std::cin, command);
        std::istringstream iss (command);
        std::string opt;
        iss >> opt;
        if (opt == "login") {
            std::string userName;
            iss >> userName;
            std::cout << "please input password : ";
            std::string password;
            std::cin >> password;
            login (userName, password);
            std::cin.ignore ();
        } else if (opt == "logout") {
            logout ();
        } else {
            std::cout << "don't find this command" << std::endl;
            continue;
        }
    } 
    return 0;
}

/*
std::cint main() {
    fileTree ft;

    // 构建一个简单的树
    ft.connect(0, 1);
    ft.connect(0, 2);
    ft.connect(1, 3);
    ft.connect(1, 4);
    ft.connect(2, 5);

    std::cout << "FileTree Structure:" << std::endl;
    printTree(ft, 0, "", true);

    // 演示 cut
    std::cout << "Cut edge (1 -> 4)" << std::endl;
    ft.cut(1, 4);

    std::cout << "FileTree Structure after cut:" << std::endl;
    printTree(ft, 0, "", true);

    return 0;
}
*/
