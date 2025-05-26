#ifndef __INDEX_NODE_HPP
#define __INDEX_NODE_HPP
#include "general.hpp"
#include <string>
#include <vector>

class DiskIndexNode {
private : 
    short ownerId;
    short fileType;
    std::string fileStoragePermission[MAX_USER_NUM];
    int fileAddress;
    int fileLength;
    int fileConnectSum;
    Time lastChangeTime;
public : 
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

class MemIndexNode {
private : 
    short state;
    short visitSum;
    int nodeId;
    int logicDeviceId;
    std::vector <int> connectPointer;
};

#endif
