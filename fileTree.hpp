#ifndef __FILE_TREE_HPP
#define __FILE_TREE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "./cereal/include/cereal/archives/binary.hpp"
#include "./cereal/include/cereal/types/vector.hpp"
#include "./general.hpp"

class fileTree {
public : 
    short deg[MAX_BLOCK_NUM];
    std::vector <short> son[MAX_BLOCK_NUM];
    template <class Archive> 
    void serialize (Archive& ar) {
        ar (deg, son);
    }
    fileTree () {
        for (int i = 0; i < MAX_BLOCK_NUM; i++) { 
            this->son[i].clear ();
            this->deg[i] = 0;
        }
    }
    void connect (short fatherId, short sonId) {
        if (fatherId < 0 || fatherId >= MAX_BLOCK_NUM || sonId < 0 || sonId >= MAX_BLOCK_NUM) {
            std::cout << "Error : Subsciprt is illegal!" << std::endl;
            exit (1);
        }
        for (auto x : son[fatherId]) {
            if (x == sonId) {
                std::cout << "Warning : " << sonId << " was son of " << fatherId << "." << std::endl;
                return;
            }
        }
        deg[fatherId]++;
        deg[sonId]++;
        son[fatherId].push_back (sonId);
    }
    void cut (short fatherId, short sonId) {
        if (fatherId < 0 || fatherId >= MAX_BLOCK_NUM || sonId < 0 || sonId >= MAX_BLOCK_NUM) {
            std::cout << "Error : Subsciprt is illegal!" << std::endl;
            exit (1);
        }
        for (int i = 0; i < son[fatherId].size (); i++) {
            auto v = son[fatherId][i];
            if (v == sonId) {
                std::swap (son[fatherId][i], son[fatherId][son[fatherId].size () - 1]);
                son[fatherId].pop_back ();
                deg[sonId]--;
                deg[fatherId]--;
                return;
            }
        }
        std::cout << "Warning : Do not find " << sonId << "." << std::endl;
    }
};

#endif
