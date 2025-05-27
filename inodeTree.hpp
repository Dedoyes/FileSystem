#ifndef __INODE_TREE_H
#define __INODE_TREE_H

#include <string>
#include <vector>
#include "general.hpp"

class InodeIndexTree {
private : 
    int idxcnt;
    std::vector <int> tree[BLOCK_SIZE >> 2];
public : 
    void insert (int address) {
        
    }
};

#endif
