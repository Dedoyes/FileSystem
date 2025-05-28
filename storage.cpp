#include <fstream>
#include "IndexNode.hpp"
#include "SuperBlock.hpp"
#include "general.hpp"
#include "fileControlBlock.hpp"
#include "./cereal/include/cereal/archives/binary.hpp"

extern SuperBlock super;
extern FCB fcb;

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

void storageDiskIndexNode (DiskIndexNode diskIndexNode) {
    std::ofstream os (VDISK_START_FILE, std::ios::binary);
    if (!os) {
        std::cout << "Error : VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryOutputArchive diskIndexNodeArchive (os);
    diskIndexNodeArchive (diskIndexNode);
    os.close ();
}
