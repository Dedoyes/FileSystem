#ifndef __FILE_TREE_HPP
#define __FILE_TREE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "./cereal/include/cereal/archives/binary.hpp"
#include "./cereal/include/cereal/types/vector.hpp"
#include "./general.hpp"
#include "./IndexNode.hpp"

extern DiskIndexNodeCluster cluster;

class fileTree {
public :
    short father[MAX_BLOCK_NUM];
    short deg[MAX_BLOCK_NUM];
    std::vector <short> son[MAX_BLOCK_NUM];
    std::string fileName[MAX_BLOCK_NUM];
    template <class Archive> 
    void serialize (Archive& ar) {
        ar (father, deg, son, fileName);
    }
    void addNode (short fileIndex, std::string name) {
        if (fileIndex < 0 || fileIndex >= MAX_BLOCK_NUM) {
            std::cout << "Warning : file index is illegal." << std::endl;
            return;
        }

        fileName[fileIndex] = name;
    }
    short findIndex (short dirIndex, std::string findName) {
        if (dirIndex < 0 || dirIndex >= MAX_BLOCK_NUM) {
            std::cout << "Warning : dirIndex is illegal." << std::endl;
            exit (1);
        }
        for (auto x : son[dirIndex]) {
            if (fileName[x] == findName) {
                return x;
            }
        }
        std::cout << fileName << "isn't in dir" << std::endl;
        exit (1);
    }
    std::string getFilePath (short fileIndex) {
        std::vector <short> tempVec;
        for (short u = fileIndex; u; u = this->father[u]) {
            tempVec.push_back (u);
        }
        tempVec.push_back (0);
        std::string res = "";
        for (int i = tempVec.size () - 1; i >= 0; i--) {
            res += this->fileName[tempVec[i]];
            res += "/";
        }
        return res;
    }
    fileTree () {
        for (int i = 0; i < MAX_BLOCK_NUM; i++) { 
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
        father[sonId] = fatherId;
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
