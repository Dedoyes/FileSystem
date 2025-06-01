#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "general.hpp"
#include "IndexNode.hpp"
#include "fileControlBlock.hpp"
#include "inodeTree.hpp"
#include "fileTree.hpp"
#include "storage.hpp"
#include "utilize.hpp"

SuperBlock super;
FCB fcb;
inodeForest forest;
DiskIndexNodeCluster cluster;
fileTree ft;

int main () {
    FILE* start_disk = fopen (VDISK_START_FILE, "wb");
    if (!start_disk) {
        perror ("Failed to create virtual start disk");
        exit (1);
    }
    ftruncate (fileno (start_disk), 10 * 1024 * 1024);
    fclose (start_disk);
    std::cout << "ok" << std::endl;
    return 0;
}
