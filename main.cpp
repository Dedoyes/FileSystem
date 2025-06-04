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
#include "fileOpenTable.hpp"
#include "command.hpp"
#include <conio.h>

short currentUserId = -1;
std::string fileStr[MAX_BLOCK_NUM];
SuperBlock super;
inodeForest forest;
DiskIndexNodeCluster cluster;
fileTree ft;
UserCluster userGroup;
short currentAddress;
fileOpenTable table;

// 自定义 my_getline 方法


int main () {
    std::cout << "Do you want a new start ?" << std::endl;
    std::cout << "please input Y or N" << std::endl;
    std::string isnew;
    std::cin >> isnew;
    if (isnew == "Y" || isnew == "y" || isnew == "yes" || isnew == "Yes") {
        formatDisk ();
        varInit ();
    } else {
        load ();
    }
    std::cin.ignore ();
    std::cout << "Loading Success :)" << std::endl;
    while (true) {
        std::string command;
        std::string name;
        std::string address;
        //std::cout << "ok!" << std::endl;
        if (currentUserId != -1) {
            name = userGroup.user[currentUserId].getName ();
        } 
        if (currentAddress == 0) {
            address = "/";
        } else {
            address = ft.getFilePath (currentAddress);
            //std::cout << "address = " << address << std::endl;
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
        } else if (opt == "ls") {
            ls ();
        } else if (opt == "create") {
            std::string fileName;
            iss >> fileName;
            create (fileName);
        } else if (opt == "mkdir") {
            std::string dirName;
            iss >> dirName;
            mkdir (dirName, false);
        } else if (opt == "cd") {
            std::string dirName;
            iss >> dirName;
            cd (dirName);
        } else if (opt == "open") {
            std::string fileName;
            iss >> fileName;
            open (fileName);
        } else if (opt == "close") {
            std::string fileName;
            iss >> fileName;
            close (fileName);
        } else if (opt == "shutdown") {
            break;
        } else if (opt == "lopen") {
            lopen ();
        } else if (opt == "format") {
            formatDisk ();
            varInit ();
        } else if (opt == "write") {
            std::string fileName, content;
            iss >> fileName;
            std::cout << "please input what you want to write : " << std::endl;
            my_getline(content);
            std::cout << "content = " << content << std::endl;
            writeFile (fileName, content);
        } else if (opt == "read") {
            std::string fileName, content;
            iss >> fileName;
            readFile (fileName);
        } else if (opt == "remove") {
            std::string fileName;
            iss >> fileName;
            remove (fileName);
        } else if (opt == "rmdir") {
            std::string dirName;
            iss >> dirName;
            removeDir (dirName);
        } else {
            std::cout << "don't find this command" << std::endl;
            continue;
        }
        //std::cout << "currentAddress = " << currentAddress << std::endl;
    }
    storage ();
    std::cout << "see you next time :)" << std::endl;
    return 0;
}

