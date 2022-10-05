#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <prglib.h>

using namespace std;

using prglib::arvore;

/*
 *
 */
int main(int argc, char** argv) {
    vector<int> v = {6,5,3,2,1,0,7,8,9,10,11};
    auto a = prglib::cria_arvore<int>(v);

    cout << "Valor da raiz: " << a.obtem() << endl;
    cout << "Valor: " << a.obtem(5) << endl;

    cout << "antes: ";
    for (auto it=a.preorder_begin(); it != a.preorder_end(); it++) {
        cout << *it << ",";
    }
    cout << endl;
    cout << "Altura: " << a.altura() << endl;
    a.balanceia();
    cout << "Altura: " << a.altura() << endl;
    cout << "depois: ";
    for (auto it=a.preorder_begin(); it != a.preorder_end(); it++) {
        cout << *it << ",";
    }
    cout << endl;
    return 0;
}
