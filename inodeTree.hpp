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
public :
    std::vector <short> blockAddress;
    template <class Archive>
    void serialize (Archive& ar) {
        ar (blockAddress);
    }
    short lastAddress () {
        return blockAddress[blockAddress.size () - 1];
    }
    inodeTree () {
        blockAddress.clear ();
    }
    void assignAddress (short blockId) {
        if (blockId < 0 || blockId >= MAX_INDEX_NODE_NUM) {
            std::cout << "Warning : blockId was illegal!" << std::endl;
            return;
        }
        bool flag = true;
        for (auto x : blockAddress) {
            if (x == blockId) {
                flag = false;
                break;
            }
        } 
        if (!flag) {
            std::cout << "Warning : this file has repeat block address." << std::endl;
            return;
        }
        blockAddress.push_back (blockId);
    }
    void popAddress () {
        if (blockAddress.empty ()) {
            std::cout << "Warning : block address array is empty." << std::endl;
            return;
        }
        blockAddress.pop_back ();
    }
};

class inodeForest {
private :
    bool vis[MAX_INDEX_NODE_NUM];
    inodeTree forest[MAX_INDEX_NODE_NUM];
public :
    template <class Archive>
    void serialize (Archive& ar) {
        ar (vis, forest);
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
    void insert (inodeTree tree, short index) {
        if (index < 0 || index >= MAX_INDEX_NODE_NUM) {
            std::cout << "Warning : Subscipt is not existed." << std::endl;
            return;
        }
        if (vis[index]) {
            std::cout << "Warning : this file isn't empty." << std::endl;
            return;
        }
        vis[index] = true;
        forest[index] = tree;
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
    }
};

#endif
