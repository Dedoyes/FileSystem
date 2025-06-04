#ifndef __STORAGE_HPP
#define __STORAGE_HPP
#include "SuperBlock.hpp"
#include "inodeTree.hpp"
#include "IndexNode.hpp"
#include "fileTree.hpp"
#include "user.hpp"

class AllData {
public :
    SuperBlock super;
    inodeForest forest;
    DiskIndexNodeCluster cluster;
    fileTree ft;
    UserCluster userGroup;
    AllData (SuperBlock& _super, inodeForest& _forest, DiskIndexNodeCluster& _cluster, 
             fileTree& _ft, UserCluster& _userGroup) {
        this->super = _super;
        this->forest = _forest;
        this->cluster = _cluster;
        this->ft = _ft;
        this->userGroup = _userGroup;
    }
    template <class Archive>
    void serialize (Archive& ar) {
        ar (super, forest, cluster, ft, userGroup);
    }
};

void storageAlldata (AllData &allData);
void loadAlldata (AllData &allData);

void storageSuperBlock (void);
void readSuperBlock (void);

void storageInodeForest (void); 
void readInodeForest (void);

void storageDiskIndexNodeCluster (void);
void readDiskIndexNodeCLuster (void);

void storageFileTree (void); 
void readFileTree (void);

void storageUserGroup (void);
void readUserGroup (void);

void load (void);

void storage (void);

#endif
