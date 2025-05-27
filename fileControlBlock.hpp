#ifndef __FILE_CONTROL_BLOCK_H
#define __FILE_CONTROL_BLOCK_H

#include <string>
#include <map>
#include "cereal/include/cereal/archives/binary.hpp"
#include "cereal/include/cereal/types/map.hpp"
#include <iostream>

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
};

#endif 
