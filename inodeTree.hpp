#ifndef __INODE_TREE_H
#define __INODE_TREE_H

#include <string>
#include <vector>
#include "general.hpp"
#include <map>
#include "./cereal/include/cereal/archives/binary.hpp"
#include "./cereal/include/cereal/types/map.hpp"

class inodeTree {
private : 
    std::map <short, std::set <int> > blockAddress;
public :
    void assignAddress (short )
};

#endif
