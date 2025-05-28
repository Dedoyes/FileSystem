#include <fstream>
#include "IndexNode.hpp"
#include "SuperBlock.hpp"
#include "general.hpp"
#include "./cereal/include/cereal/archives/binary.hpp"

extern SuperBlock super;

void storageSuperBlock () {
    std::ofstream os (VDISK_START_FILE, std::ios::binary); 
    if (!os) {
        std::cout << "VIRTUAL START DISK can not be opened!" << std::endl;
        exit (1);
    }
    cereal::BinaryOutputArchive superBlockArchive (os);
    superBlockArchive (super);
    os.close ();
}
