#ifndef __INDEX_NODE_HPP
#define __INDEX_NODE_HPP

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "SuperBlock.hpp"
#include "general.hpp"
#include "inodeTree.hpp"
#include "./cereal/include/cereal/archives/binary.hpp"
#include "./cereal/include/cereal/types/string.hpp"

extern SuperBlock super;

class DiskIndexNode {
private : 
    short ownerId;
    short fileType;
    std::vector <std::string> fileStoragePermission;  // MAX_USER_NUM
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
    inline short getOwnerId () {
        return ownerId;
    }
    inline void changeFileLength (int newLength) {
        fileLength = newLength;
    }
    inline int getFileLength () {
        return fileLength;
    }
    inline short getType () {
        return fileType;
    }
    inline std::string getPermission (short userId) {
        return fileStoragePermission[userId];
    }
    inline int getIndex () {
        return this->fileAddress;
    }
    DiskIndexNode () {
        fileStoragePermission.resize (MAX_USER_NUM);
        this->ownerId = 0;
        this->fileType = 0;
        for (int i = 0; i < MAX_USER_NUM; i++)
            this->fileStoragePermission[i] = "";
        this->fileAddress = 0;
        this->fileLength = 0;
        this->fileConnectSum = 0;
        this->lastChangeTime = Time ();
    }
    void init (short UserId, short type, bool general) {
        if (!super.hasFreeIndexSpace ()) {
            std::cout << "Error : there is no available disk room!" << std::endl;
            exit (1);
        }
        this->fileAddress = super.askFreeIndex ();
        super.occupyIndex (this->fileAddress);
        this->ownerId = UserId;
        this->fileType = type;
        if (!general) {
            for (int i = 0; i < MAX_USER_NUM; i++) 
                this->fileStoragePermission[i] = "";
            this->fileStoragePermission[UserId] = "rwx";
        } else {
            for (int i = 0; i < MAX_USER_NUM; i++) 
                this->fileStoragePermission[i] = "rwx";
        }
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
    std::vector <bool> vis;    //MAX_INDEX_NODE_NUM]
    int current;
    int usedNum;
    std::vector <DiskIndexNode> cluster; // MAX_INDEX_NODE_NUM
public :
    template <class Archive>
    void serialize (Archive& ar) {
        ar (vis, current, usedNum, cluster);
    }
    DiskIndexNodeCluster () {
        vis.resize (MAX_INDEX_NODE_NUM);
        cluster.resize (MAX_INDEX_NODE_NUM);
        for (int i = 0; i < MAX_INDEX_NODE_NUM; i++) 
            this->vis[i] = false;
        current = 0;
        usedNum = 0;
        for (int i = 0; i < MAX_INDEX_NODE_NUM; i++)
            cluster[i] = DiskIndexNode ();
    }
    DiskIndexNode& operator [] (short index) {
        if (index < 0 || index >= MAX_INDEX_NODE_NUM) {
            std::cout << "Error : Subscript was illegal!" << std::endl;
            exit (1);
        }
        if (!vis[index]) {
            std::cout << "Error : this index block was empty" << std::endl;
            exit (1);
        }
        return cluster[index];
    }
    DiskIndexNode& operator [] (int index) {
        if (index < 0 || index >= MAX_INDEX_NODE_NUM) {
            std::cout << "Error : Subscript was illegal!" << std::endl;
            exit (1);
        }
        if (!vis[index]) {
            std::cout << "Error : this index block was empty" << std::endl;
            exit (1);
        }
        return cluster[index];
    }
    void insert (DiskIndexNode node) {
        if (usedNum == MAX_INDEX_NODE_NUM - 1) {
            std::cout << "Warning : The disk index node cluster is full!" << std::endl;
            return;
        }
        if (vis[current]) {
            std::cout << "Warning : This node is occupied!" << std::endl;
            return;
        }
        usedNum++;
        vis[current] = true;
        cluster[current] = node;
        for (int i = 0; i < MAX_INDEX_NODE_NUM; i++) {
            if (!vis[i]) {
                current = i;
                break;
            }
        }
    }
    void erase (int idx) {
        if (idx < 0 || idx >= MAX_INDEX_NODE_NUM) {
            std::cout << "Error : Subscript is illegal!" << std::endl;
            exit (1);
        }
        if (!vis[idx]) {
            std::cout << "Warning : this index block is empty." << std::endl;
            return;
        }
        usedNum--;
        vis[idx] = false;
        for (int i = 0; i < MAX_INDEX_NODE_NUM; i++) {
            if (!vis[i]) {
                current = i;
                break;
            }
        }
    }
};

#endif
