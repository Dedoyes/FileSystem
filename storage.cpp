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

void storageFileTree () {
    std::ofstream os (VDISK_START_FILE, std::ios::binary);
    if (!os) {
        std::cout << "Error : VIRTUAL START Disk can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryOutputArchive fileTreeArchive (os);
    fileTreeArchive (ft);
    os.close ();
}

void storageUserGroup () {
    std::ofstream os (VDISK_START_FILE, std::ios::binary);
    if (!os) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryOutputArchive userArchive (os);
    userArchive (userGroup);
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

void readInodeForest () {
    std::ifstream is (VDISK_START_FILE, std::ios::binary);
    if (!is) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryInputArchive forestArchive (is);
    try {
        forestArchive(forest);
    } catch (const std::exception& e) {
        std::cout << "Deserialization error: " << e.what() << std::endl;
        exit(1);
    }    
    std::cout << "vis size: " << forest.vis.size() << std::endl;
    std::cout << "forest size: " << forest.forest.size() << std::endl;
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

void readFileTree () {
    std::ifstream is (VDISK_START_FILE, std::ios::binary);
    if (!is) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryInputArchive fileTreeArchive (is);
    fileTreeArchive (ft);
    is.close ();
}

void readUserGroup () {
    std::ifstream is (VDISK_START_FILE, std::ios::binary);
    if (!is) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryInputArchive userGroupArchive (is);
    userGroupArchive (userGroup);
    is.close ();
}

void load () {
    readSuperBlock ();
    std::cout << "super load success." << std::endl;
    readFileTree ();
    std::cout << "file tree load success." << std::endl;
    readInodeForest ();
    std::cout << "inode forest load success." << std::endl; 
    readUserGroup ();
    std::cout << "user group load success." << std::endl;
    readDiskIndexNodeCluster ();
    std::cout << "cluster load success" << std::endl;
}

void storage () {
    storageSuperBlock ();
    storageFileTree ();
    storageInodeForest ();
    storageUserGroup ();
    storageDiskIndexNodeCluster ();
}
