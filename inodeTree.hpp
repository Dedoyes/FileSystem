#ifndef __INODE_TREE_H
#define __INODE_TREE_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "general.hpp"
#include "./cereal/include/cereal/archives/binary.hpp"
#include "./cereal/include/cereal/types/map.hpp"

int main () { 
    User u;
    ofstream os ("user.dat", ios::binary);
    if (!os) {
        cerr << "Error opening file for writing" << endl;
        return 1;
    }
    cereal::BinaryOutputArchive out_archive (os);
    out_archive (u);
    os.close ();


    ifstream is ("user.dat", ios::binary);
    if (!is) {
        cerr << "Error opening file for reading" << endl;
        return 1;
    }
    User r;
    cereal::BinaryInputArchive in_archive (is);
    in_archive (r);
    for (int i = 0; i < 10; i++) { 
        cout << "i = " << i << endl;
        for (auto x : r.vec[i]) 
            cout << "x = " << x << endl;
    }
    is.close ();
    return 0;
}


class inodeTree {
private :
    std::map <short, std::vector <short> > blockAddress;
public :
    template <class Archive>
    void serialize (Archive& ar) {
        ar (blockAddress);
    }
    void assignAddress (short fileId, short blockId) {
        bool flag = true;
        for (auto x : blockAddress[fileId]) {
            if (x == blockId) {
                flag = false;
                break;
            }
        } 
        if (!flag) {
            std::cout << "Error : this file has repeat block address!" << std::endl;
            return;
        }
        blockAddress[fileId].push_back (blockId);
    }
    void popAddress (short fileId) {
        if (blockAddress[fileId].empty ()) {
            std::cout << "Error : this file has no block" << std::endl;
            return;
        }
        blockAddress[fileId].pop_back ();
    }
};

extern std::vector <inodeTree> inodeVec;

#endif
