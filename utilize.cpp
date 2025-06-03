#include <iostream>
#include <set>
#include <string>
#include "general.hpp"
#include "utilize.hpp"

void write_block (int block_number, const void* data) {
    if (block_number < 0 || block_number >= MAX_BLOCK_NUM) {
        std::cout << "Error : Block index is illegal!" << std::endl;
        exit (1);
    }
    FILE* disk = fopen (VDISK_FILE, "r+b");
    if (!disk) {
        perror ("Failed to open virtual disk!");
        exit (1);
    }
    fseek (disk, block_number * BLOCK_SIZE, SEEK_SET);
    fwrite (data, 1, BLOCK_SIZE, disk);
    fclose (disk);
}

void read_block (int block_number, void* buffer) {
    FILE* disk = fopen (VDISK_FILE, "rb");
    if (!disk) {
        perror ("Failed to open virtual disk!");
        exit (1);
    }
    fseek (disk, block_number * BLOCK_SIZE, SEEK_SET);
    fread (buffer, 1, BLOCK_SIZE, disk);
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

