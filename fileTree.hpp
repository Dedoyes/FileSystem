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
    short inodeAddress[MAX_BLOCK_NUM];
    short father[MAX_BLOCK_NUM];
    short deg[MAX_BLOCK_NUM];
    std::vector <short> son[MAX_BLOCK_NUM];
    std::string fileName[MAX_BLOCK_NUM];
    template <class Archive> 
    void serialize (Archive& ar) {
        ar (inodeAddress, father, deg, son, fileName);
    }
    std::string getFilePath (short fileIndex) {
        std::vector <short> tempVec;
        for (short u = fileIndex; u; u = father[u]) {
            tempVec.push_back (u);
        }
        std::string res = "";
        for (int i = tempVec.size () - 1; i >= 0; i--) {
            res += fileName[i];
            if (i != 0)
                res += "/";
        }
        return res;
    }
    fileTree () {
        for (int i = 0; i < MAX_BLOCK_NUM; i++) { 
            this->inodeAddress[i] = 0;
            this->father[i] = 0;
            this->son[i].clear ();
            this->deg[i] = 0;
            this->fileName[i] = "";
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
