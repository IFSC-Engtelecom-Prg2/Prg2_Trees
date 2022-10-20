#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <prglib.h>

using namespace std;

int main(int argc, char** argv) {
    vector<int> v = {6,5,3,2,1,0,7,8,9,10,11};
    prglib::arvore<int> a2(v);

    for (auto & x: a2) {
        std::cout << x << std::endl;
    }

    return 0;
}
