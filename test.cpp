#include <bits/stdc++.h>
#include <cstdio>
#include <fstream>
#include "./cereal/include/cereal/archives/binary.hpp"
#include "./cereal/include/cereal/types/string.hpp"
#define LL long long 
#define mod %

using namespace std;

struct User {
    int id;
    string name;
    template <class Archive>
    void serialize (Archive& ar) {
        ar (id, name);
    }
};

int main () { 
    User u = {10, "hello"};
    ofstream os ("user.dat", ios::binary);
    if (!os) {
        cerr << "Error opening file for writing" << endl;
        return 1;
    }
    cereal::BinaryOutputArchive out_archive (os);
    out_archive (u);
    os.close ();
    ifstream is ("user.dat", ios::binary);
    if (!is) {
        cerr << "Error opening file for reading" << endl;
        return 1;
    }
    User t;
    cereal::BinaryInputArchive in_archive (is);
    in_archive (t);
    cout << "information : ";
    cout << "id : " << t.id << ", t.name = " << t.name << endl;
    is.close ();
    return 0;
}
