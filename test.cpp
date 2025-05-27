#include <bits/stdc++.h>
#include <cstdio>
#include <fstream>
#include "./cereal/include/cereal/archives/binary.hpp"
#include "./cereal/include/cereal/types/string.hpp"
#include "./cereal/include/cereal/types/vector.hpp"
#include "general.hpp"
#define LL long long 
#define mod %

using namespace std;

struct User {
    vector <int> vec[10];
    template <class Archive>
    void serialize (Archive& ar) {
        ar (vec);
    }
};

int main () { 
    User u;
    for (int i = 1; i <= 3; i++)
        u.vec[i].push_back (i); 
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
    User r;
    cereal::BinaryInputArchive in_archive (is);
    in_archive (r);
    for (int i = 0; i < 10; i++) { 
        cout << "i = " << i << endl;
        for (auto x : r.vec[i]) 
            cout << "x = " << x << endl;
    }
    is.close ();
    return 0;
}
