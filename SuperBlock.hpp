#ifndef __SUPER_BLOCK_HPP
#define __SUPER_BLOCK_HPP

#include <iostream>
#include <set>
#include <string>
#include "general.hpp"
#include "cereal/include/cereal/archives/binary.hpp"
#include "cereal/include/cereal/types/set.hpp"

class SuperBlock {
private :
    std::set <int> remainIndexAddress;
    std::set <int> remainBlcokAddress;
public :
    template <class Archive>
    void serialize (Archive& ar) {
        ar (remainIndexAddress, remainBlcokAddress);
    }
    SuperBlock () {
        for (int i = 0; i < MAX_INDEX_NODE_NUM; i++)
            remainIndexAddress.insert (i);
        for (int i = 0; i < MAX_BLOCK_NUM; i++) 
            remainBlcokAddress.insert (i);
    }
    inline bool hasFreeIndexSpace () {
        return !this->remainIndexAddress.empty ();
    }
    inline bool hasFreeBlockSpace () {
        return !this->remainBlcokAddress.empty (); 
    }
    inline int askFreeIndex () {
        auto it = this->remainIndexAddress.begin ();
        return *it;
    }
    inline int askFreeBlock () {
        auto it = this->remainBlcokAddress.begin ();
        return *it;
    }
    inline void occupyIndex (int indexAddress) {
        auto it = this->remainIndexAddress.lower_bound (indexAddress);
        if (it == this->remainIndexAddress.end () || (*it) != indexAddress) {
            std::cout << "Error : this index address is not free!" << std::endl;
            return;
        }
        this->remainIndexAddress.erase (indexAddress);
    }
    inline void occupyBlock (int blockAddress) {
        auto it = this->remainBlcokAddress.lower_bound (blockAddress);
        if (it == this->remainBlcokAddress.end () || (*it) != blockAddress) {
            std::cout << "Error : this block address is not free!" << std::endl;
            return;
        }
        remainBlcokAddress.erase (it);
    }
    inline int FreeIndexSum () {
        return (int) this->remainIndexAddress.size ();
    }
    inline int FreeBlockSum () {
        return (int) this->remainBlcokAddress.size ();
    }
};

#endif
