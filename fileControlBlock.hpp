#ifndef __FILE_CONTROL_BLOCK_HPP
#define __FILE_CONTROL_BLOCK_HPP

#include <iostream>
#include <string>
#include <map>
#include "cereal/include/cereal/archives/binary.hpp"
#include "cereal/include/cereal/types/map.hpp"

class FCB {
private :
    std::map <std::string, short> whichInode;
public : 
    template <class Archive>
    void serialize (Archive& ar) {
        ar (whichInode);
    }
    void insert (std::string fileName, short inodeCnt) {
        if (whichInode.count (fileName)) {
            std::cout << "Error : " << fileName << "is existed!" << std::endl;
            return;
        }
        whichInode[fileName] = inodeCnt;
    }
    void erase (std::string fileName) {
        if (!whichInode.count (fileName)) {
            std::cout << "Error : " << fileName << "is not existed!" << std::endl;
            return;
        }
        whichInode.erase (fileName);
    }
    void rename (std::string previousName, std::string newName) {
        if (whichInode.count (newName)) {
            std::cout << "Error : " << newName << " is existed!" << std::endl;
            return;
        }
        whichInode[newName] = whichInode[previousName];
        whichInode.erase (previousName);
    }
};

#endif 
