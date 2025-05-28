#ifndef __INDEX_NODE_HPP
#define __INDEX_NODE_HPP

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "SuperBlock.hpp"
#include "general.hpp"
#include "inodeTree.hpp"

extern SuperBlock super;

class DiskIndexNode {
private : 
    short ownerId;
    short fileType;
    std::string fileStoragePermission[MAX_USER_NUM];
    int fileAddress;                        // Adress of inode Tree in disk
    int fileLength;
    int fileConnectSum;
    Time lastChangeTime;
public : 
    template <class Archive>
    void serialize (Archive& ar) {
        ar (ownerId, fileType, fileStoragePermission, fileAddress,
            fileLength, fileConnectSum, lastChangeTime);
    }
    void init (short UserId) {
        if (super.hasFreeIndexSpace ()) {
            std::cout << "Error : there is no available disk room!" << std::endl;
            exit (1);
        }
        this->fileAddress = super.askFreeIndex ();
        super.occupyIndex (this->fileAddress);
        this->ownerId = UserId;
        this->fileType = REGULAR_FILE;
        for (int i = 0; i < MAX_USER_NUM; i++) 
            this->fileStoragePermission[i] = "";
        fileConnectSum = 0;
        lastChangeTime = Time ();
    }
    DiskIndexNode (short _ownerId, short _fileType, int _fileAddress, int _fileLength, int _fileConnectSum, Time _lastChangeTime) {
        this->ownerId = _ownerId;
        this->fileType = _fileType;
        this->fileAddress = _fileAddress;
        this->fileLength = _fileLength;
        this->fileConnectSum = _fileConnectSum;
        this->lastChangeTime = _lastChangeTime;
        for (int i = 0; i < MAX_USER_NUM; i++)
            this->fileStoragePermission[i] = "";
        this->fileStoragePermission[_ownerId] = "rwx";
    }
    bool changeOwnerId (short newId, short operateUser) {
        if (operateUser == this->ownerId) {
            this->ownerId = newId;
            return true;
        }
        return false;
    }
    bool changeStoragePermission (std::string newPermission, short newId, short operateUser) {
        if (operateUser == this->ownerId) {
            this->fileStoragePermission[newId] = newPermission;
            return true;
        }
        return false;
    }
};

class DiskIndexNodeCluster {
private :
    std::vector <DiskIndexNode> vec;
public :
    inline void push_back (DiskIndexNode diskIndexNode) {
         vec.push_back (diskIndexNode);
    }
    
};

class MemIndexNode {
private : 
    short state;
    int nodeId;
    int logicDeviceId;
    std::vector <int> connectPointer;
public :
};

extern std::vector <MemIndexNode> memIndexVec;

#endif
