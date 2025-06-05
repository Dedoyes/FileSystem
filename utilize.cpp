#include <iostream>
#include <set>
#include <string>
// #include <termios.h>
#include "general.hpp"
#include "utilize.hpp"
#include "unistd.h"

void write_block (int block_number, int offset, const void* data) {
    if (block_number < 0 || block_number >= MAX_BLOCK_NUM) {
        std::cout << "Error : Block index is illegal!" << std::endl;
        exit (1);
    }
    FILE* disk = fopen (VDISK_FILE, "r+b");
    if (!disk) {
        perror ("Failed to open virtual disk!");
        exit (1);
    }
    fseek (disk, block_number * BLOCK_SIZE + offset, SEEK_SET);
    fwrite (data, 1, BLOCK_SIZE, disk);
    fclose (disk);
}

void read_block (int block_number, int offset, void* buffer, int len) {
    FILE* disk = fopen (VDISK_FILE, "rb");
    if (!disk) {
        perror ("Failed to open virtual disk!");
        exit (1);
    }
    fseek (disk, block_number * BLOCK_SIZE + offset, SEEK_SET);
    fread (buffer, 1, len, disk);
    fclose (disk);
}

template <typename T>
size_t estimate_set_memory (const std::set <T> &s) {
    size_t node_size = sizeof (T) + 3 * sizeof (void*);
    size_t padding = (8 - (node_size % 8)) % 8;
    node_size += padding;
    return s.size () * node_size;
}

std::string reguPermission (std::string s) {
    std::string res = "";
    for (int i = 0; i < s.size (); i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] - 'A' + 'a';
    bool hasRead = false, hasWrite = false, hasExecute = false;
    for (int i = 0; i < s.size (); i++) {
        if (s[i] == 'r') hasRead = true;
        if (s[i] == 'w') hasWrite = true;
        if (s[i] == 'x') hasExecute = true;
    }
    if (hasRead) res += "r";
    if (hasWrite) res += "w";
    if (hasExecute) res += "x";
    return res;
}

bool hasRead (std::string s) {
    for (int i = 0; i < s.size (); i++)
        if (s[i] == 'r')
            return true;
    return false;
}

bool hasWrite (std::string s) {
    for (int i = 0; i < s.size (); i++)
        if (s[i] == 'w')
            return true;
    return false;
}

bool hasExecute (std::string s) {
    for (int i = 0; i < s.size (); i++)
        if (s[i] == 'x')
            return true;
    return false;
}

// char linux_getch() {
//     struct termios oldt, newt;
//     char ch;

//     // 获取当前终端设置
//     tcgetattr(STDIN_FILENO, &oldt);
//     newt = oldt;

//     // 设置为原始模式（禁用缓冲和回显）
//     newt.c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);

//     // 读取一个字符
//     read(STDIN_FILENO, &ch, 1);

//     // 恢复终端设置
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

//     return ch;
// }

// void my_getline(std::string& content) {
//     content.clear();  // 清空原始内容
//     char ch;

//     while (true) {
//         ch = linux_getch();  // 获取单个字符，不回显

//         if (ch == '\n' || ch == '\r') { // Enter 键
//             content += '\n';
//             std::cout << '\n';
//             break; // 与 Windows 不同：此处应结束输入
//         }
//         else if (ch == 127 || ch == 8) { // Backspace（Linux常为127）
//             if (!content.empty()) {
//                 content.pop_back();
//                 std::cout << "\b \b";
//             }
//         } 
//         else if (ch == 27) { // ESC 键
//             return;
//         } 
//         else if (ch >= 32 && ch <= 126) { // 可打印字符
//             content += ch;
//             std::cout << ch;
//         }
//     }
// }

