#include <fstream>
#include "IndexNode.hpp"
#include "SuperBlock.hpp"
#include "general.hpp"
#include "fileControlBlock.hpp"
#include "./cereal/include/cereal/archives/binary.hpp"
#include "inodeTree.hpp"

extern SuperBlock super;
extern FCB fcb;
extern inodeForest forest;
extern DiskIndexNodeCluster cluster;

void storageSuperBlock () {
    std::ofstream os (VDISK_START_FILE, std::ios::binary); 
    if (!os) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryOutputArchive superBlockArchive (os);
    superBlockArchive (super);
    os.close ();
}

void storageFCB () {
    std::ofstream os (VDISK_START_FILE, std::ios::binary);
    if (!os) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryOutputArchive fcbArchive (os);
    fcbArchive (fcb);
    os.close ();
}

void storageInodeForest () {
    std::ofstream os (VDISK_START_FILE, std::ios::binary);
    if (!os) {
        std::cout << "Error : VIRTUAL START Disk can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryOutputArchive forestArchive (os);
    forestArchive (forest);
    os.close ();
}

void storageDiskIndexNodeCluster () {
    std::ofstream os (VDISK_START_FILE, std::ios::binary);
    if (!os) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryOutputArchive diskIndexNodeArchive (os);
    diskIndexNodeArchive (cluster);
    os.close ();
}

void readSuperBlock () {
    std::ifstream is (VDISK_START_FILE, std::ios::binary);
    if (!is) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryInputArchive superBlockArchive (is);
    superBlockArchive (super);
    is.close ();
}

void readFCB () {
    std::ifstream is (VDISK_START_FILE, std::ios::binary);
    if (!is) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryInputArchive fcbArchive (is);
    fcbArchive (fcb);
    is.close ();
}

void readInodeForest () {
    std::ifstream is (VDISK_START_FILE, std::ios::binary);
    if (!is) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryInputArchive forestArchive (is);
    forestArchive (forest);
    is.close ();
}

void readDiskIndexNodeCluster () {
    std::ifstream is (VDISK_START_FILE, std::ios::binary);
    if (!is) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryInputArchive clusterArchive (is);
    clusterArchive (cluster);
    is.close ();
}
