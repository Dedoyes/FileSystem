#ifndef __UTILIZE_H
#define __UTILIZE_H

#include <string>

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

inline bool hasRead (std::string s) {
    for (int i = 0; i < s.size (); i++)
        if (s[i] == 'r')
            return true;
    return false;
}

inline bool hasWrite (std::string s) {
    for (int i = 0; i < s.size (); i++)
        if (s[i] == 'w')
            return true;
    return false;
}

inline bool hasExecute (std::string s) {
    for (int i = 0; i < s.size (); i++)
        if (s[i] == 'x')
            return true;
    return false;
}


#endif
