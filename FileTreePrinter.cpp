// //
// // Created by 26742 on 2025/5/27.
// //
// /*
//  * 实现打印文件树
//  * */
// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <string>
#include <iostream>
#include "FileTreePrinter.h"

void printTree(fileTree& ft, short node, const std::string& prefix, bool isLast) {
    std::cout << prefix
              << (isLast ? "+-- " : "|-- ")
              << "Node " << node
              << std::endl;

    std::string newPrefix = prefix + (isLast ? "    " : "|   ");
    for (size_t i = 0; i < ft.son[node].size(); ++i) {
        bool isLastChild = (i == ft.son[node].size() - 1);
        printTree(ft, ft.son[node][i], newPrefix, isLastChild);
    }
}


// const int MAX = 1000; // 最大节点数

// // 辅助函数：递归打印目录树
// void printTree(int node,
//                const std::vector<int> tree[],
//                const std::unordered_map<int, std::string>& fileNameMap,
//                const std::string& prefix,
//                bool isTail) {
//     std::cout << prefix
//               << (isTail ? "└── " : "├── ")
//               << fileNameMap.at(node)
//               << std::endl;

//     std::string newPrefix = prefix + (isTail ? "    " : "│   ");

//     for (size_t i = 0; i < tree[node].size(); ++i) {
//         bool isLastChild = (i == tree[node].size() - 1);
//         printTree(tree[node][i], tree, fileNameMap, newPrefix, isLastChild);
//     }
// }

// // 主函数接口
// void printDirectoryTree(int root,
//                         const std::vector<int> tree[],
//                         const std::unordered_map<int, std::string>& fileNameMap) {
//     std::cout << fileNameMap.at(root) << std::endl;

//     for (size_t i = 0; i < tree[root].size(); ++i) {
//         bool isLast = (i == tree[root].size() - 1);
//         printTree(tree[root][i], tree, fileNameMap, "", isLast);
//     }
// }
// int main() {
//     const int MAXNODES = 10;
//     std::vector<int> tree[MAXNODES];
//     std::unordered_map<int, std::string> fileNameMap;

//     // 构建测试数据
//     fileNameMap[1] = "test.txt";
//     fileNameMap[2] = "folderA";
//     fileNameMap[3] = "folderB";
//     fileNameMap[4] = "fileA.txt";
//     fileNameMap[5] = "fileB.txt";
//     fileNameMap[6] = "fileC.txt";

//     // 构建目录结构
//     tree[1] = {2, 3};       // test.txt -> folderA, folderB
//     tree[2] = {4, 5};       // folderA -> fileA.txt, fileB.txt
//     tree[3] = {6};          // folderB -> fileC.txt
//     tree[4] = {};           // fileA.txt 没有子项
//     tree[5] = {};
//     tree[6] = {};

//     // 打印目录树
//     printDirectoryTree(1, tree, fileNameMap);

//     return 0;
// }
