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
#include  "FileTreePrinter.h"

SuperBlock super;
FCB fcb;
inodeForest forest;
DiskIndexNodeCluster cluster;
fileTree ft;

// int main () {
//     FILE* start_disk = fopen (VDISK_START_FILE, "wb");
//     if (!start_disk) {
//         perror ("Failed to create virtual start disk");
//         exit (1);
//     }
//     ftruncate (fileno (start_disk), 10 * 1024 * 1024);
//     fclose (start_disk);
//     std::cout << "ok" << std::endl;
//     return 0;
// }

// void printTree(fileTree& ft, short node, const std::string& prefix, bool isLast) {
//     std::cout << prefix
//               << (isLast ? "+-- " : "|-- ")
//               << "Node " << node << " (degree: " << ft.deg[node] << ")"
//               << std::endl;

//     std::string newPrefix = prefix + (isLast ? "    " : "|   ");
//     for (size_t i = 0; i < ft.son[node].size(); ++i) {
//         bool isLastChild = (i == ft.son[node].size() - 1);
//         printTree(ft, ft.son[node][i], newPrefix, isLastChild);
//     }
// }


int main() {
    fileTree ft;

    // 构建一个简单的树
    ft.connect(0, 1);
    ft.connect(0, 2);
    ft.connect(1, 3);
    ft.connect(1, 4);
    ft.connect(2, 5);

    std::cout << "FileTree Structure:" << std::endl;
    printTree(ft, 0, "", true);

    // 演示 cut
    std::cout << "Cut edge (1 -> 4)" << std::endl;
    ft.cut(1, 4);

    std::cout << "FileTree Structure after cut:" << std::endl;
    printTree(ft, 0, "", true);

    return 0;
}