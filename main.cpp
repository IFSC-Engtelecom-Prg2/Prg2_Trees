#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <prglib.h>

using namespace std;

using prglib::arvore;

vector<int> rand_vector(int n) {
    vector<int> v;

    while (n-- > 0) {
        v.push_back(rand() % 100000);
    }

    return v;
}
/*
 *
 */
int main(int argc, char** argv) {
//    vector<int> v = {6,5,3,2,1,0,7,8,9,10,11};
    auto v = rand_vector(1000);
    auto a = prglib::cria_arvore<int>(v);

    cout << "Valor da raiz: " << a.obtem() << endl;
    if (a.existe(5)) {
        cout << "Valor: " << a.obtem(5) << endl;
    }
    cout << "antes: " << a.tamanho() << " elementos" << endl;
    auto b = std::move(a);
//    for (auto it=a.preorder_begin(); it != a.preorder_end(); it++) {
//        cout << *it << ",";
//    }
//    cout << endl;
//    cout << "Altura: " << a.altura() << endl;
//    a.balanceia();
//    cout << "Altura: " << a.altura() << endl;
    cout << "depois: " << a.tamanho() << " elementos" << endl;
    cout << "depois: " << b.tamanho() << " elementos" << endl;

    cout << "Maior=" << b.obtemMaior() << endl;
    auto menor = b.obtemMenor();
    cout << "Menor=" << menor << endl;
    b.remove(menor);
    cout << boolalpha << b.existe(menor) << endl;

//    for (auto it=a.preorder_begin(); it != a.preorder_end(); it++) {
//        cout << *it << ",";
//    }
//    cout << endl;
    return 0;
}
