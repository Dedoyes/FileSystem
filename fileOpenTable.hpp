#ifndef __FILE_OPEN_TABLE_HPP
#define __FILE_OPEN_TABLE_HPP

#include <iostream>
#include <map>
#include <string>

class fileOpenTable {
private :
    std::map <std::string, short> fileIndex;
public :
    fileOpenTable () {
        fileIndex.clear ();
    }
    short getIndex (std::string path) {
        return fileIndex[path];
    }
    void storage (std::string path, short index) {
        fileIndex[path] = index;
    }
    void erase (std::string path) {
        auto it = fileIndex.lower_bound (path);
        if (it == fileIndex.end () || (*it).first != path) {
            std::cout << "Warning : file dosn't exist." << std::endl;
            return;
        }
        fileIndex.erase (it);
    }
    bool count (std::string s) {
        return fileIndex.count (s);
    }
};

#endif
