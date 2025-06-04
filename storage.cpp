#include <fstream>
#include "fileTree.hpp"
#include "storage.hpp"
#include "IndexNode.hpp"
#include "SuperBlock.hpp"
#include "general.hpp"
#include "./cereal/include/cereal/archives/binary.hpp"
#include "inodeTree.hpp"
#include "user.hpp"

extern SuperBlock super;
extern inodeForest forest;
extern DiskIndexNodeCluster cluster;
extern fileTree ft;
extern UserCluster userGroup; 

void storageAlldata (AllData &allData) {
    std::ofstream os (VDISK_START_FILE, std::ios::binary);
    if (!os) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryOutputArchive AllDataArchive (os);
    AllDataArchive (allData);
    os.close ();
}

void readAllData (AllData &allData) {
    std::ifstream is (VDISK_START_FILE, std::ios::binary);
    if (!is) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryInputArchive AllDataArchive (is);
    AllDataArchive (allData);
    is.close ();
} 

void storage () {
    AllData alldata = AllData (super, forest, cluster, ft, userGroup);
    storageAlldata (alldata);
}

void load () {
    AllData allData = AllData (super, forest, cluster, ft, userGroup);
    readAllData (allData);
    super = allData.super;
    forest = allData.forest;
    cluster = allData.cluster;
    ft = allData.ft;
    userGroup = allData.userGroup;
}


