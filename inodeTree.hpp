#ifndef __INODE_TREE_HPP
#define __INODE_TREE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "general.hpp"
#include "./cereal/include/cereal/archives/binary.hpp"
#include "./cereal/include/cereal/types/map.hpp"
#include "./cereal/include/cereal/types/vector.hpp"

class inodeTree {
private :
    std::map <short, std::vector <short> > blockAddress;
public :
    template <class Archive>
    void serialize (Archive& ar) {
        ar (blockAddress);
    }
    void assignAddress (short fileId, short blockId) {
        if (!blockAddress.count (fileId)) {
            std::cout << "Warning : this file id is not existed." << std::endl;
            return;
        }
        bool flag = true;
        for (auto x : blockAddress[fileId]) {
            if (x == blockId) {
                flag = false;
                break;
            }
        } 
        if (!flag) {
            std::cout << "Warning : this file has repeat block address." << std::endl;
            return;
        }
        blockAddress[fileId].push_back (blockId);
    }
    void popAddress (short fileId) {
        if (!blockAddress.count (fileId)) {
            std::cout << "Warning : this file id is not existed." << std::endl;
            return;
        }
        if (blockAddress[fileId].empty ()) {
            std::cout << "Warning : this file has no block." << std::endl;
            return;
        }
        blockAddress[fileId].pop_back ();
    }
};

class inodeForest {
private :
    bool vis[MAX_INDEX_NODE_NUM];
    int current;
    int usedNum;
    inodeTree forest[MAX_INDEX_NODE_NUM];
public :
    template <class Archive>
    void serialize (Archive& ar) {
        ar (forest);
    }
    inodeTree& operator [] (int index) {
        if (index < 0 || index >= MAX_INDEX_NODE_NUM) {
            std::cout << "Error : Subscipt is illegal!" << std::endl;
            exit (1);
        }
        if (!vis[index]) {
            std::cout << "Error : this tree was empty!" << std::endl;
            exit (1);
        }
        return forest[index];
    }
    void insert (inodeTree tree) {
        if (usedNum == MAX_INDEX_NODE_NUM) {
            std::cout << "Warning : inode Forest was full." << std::endl;
            return;
        }
        if (vis[current]) {
            std::cout << "Warning : this place is occupied." << std::endl;
            return;
        }
        usedNum++;
        vis[current] = true;
        forest[current] = tree;
        for (int i = 0; i < MAX_INDEX_NODE_NUM; i++) {
            if (!vis[i]) {
                current = i;
                break;
            }
        }
    }
    void erase (int index) {
        if (index < 0 || index >= MAX_INDEX_NODE_NUM) {
            std::cout << "Warning : Subscipt is not existed." << std::endl;
            return;
        }
        if (!vis[index]) {
            std::cout << "Warning : this file is empty." << std::endl;
            return;
        }
        vis[index] = false;
        for (int i = 0; i < MAX_INDEX_NODE_NUM; i++) {
            if (!vis[i]) {
                current = i;
                break;
            }
        }
    }
};

#endif
