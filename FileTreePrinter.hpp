#ifndef FILE_TREE_PRINTER_H
#define FILE_TREE_PRINTER_H

#include <string>
#include "fileTree.hpp"  // 你的 fileTree 类声明头文件

// 打印函数声明
void printTree(fileTree& ft, short node, const std::string& prefix, bool isLast);

#endif // FILE_TREE_PRINTER_H
