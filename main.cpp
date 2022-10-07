#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <prglib.h>

using namespace std;

using prglib::arvore;

vector<int> rand_vector(int n) {
    static bool _init = true;
    vector<int> v;

    if (_init) {
        _init = false;
        srand(clock());
    }
    while (n-- > 0) {
        v.push_back(rand() % 100000);
    }

    return v;
}
/*
 *
 */
struct Coisa {
    string nome;
    int idade;
};

int main(int argc, char** argv) {
//    vector<int> v = {6,5,3,2,1,0,7,8,9,10,11};
    auto v = rand_vector(100000);
    auto a = prglib::cria_arvore<int>(v);
    auto t = prglib::cria_arvore_esp<Coisa>([](const Coisa &x, const Coisa &y) { return x.nome < y.nome?-1:x.nome>y.nome;});

    t.adiciona(Coisa{"um", 1});
    t.adiciona(Coisa{"dois", 2});
    t.adiciona(Coisa{"tres", 3});
    cout << "len=" << t.tamanho() << endl;
    for (auto it=t.preorder_begin(); it != t.preorder_end(); it++) {
        auto & algo = *it;
        cout << it->nome << ", " << algo.idade << endl;
    }
    return 0;

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

    auto pre = b.obtemIntervalo(10,50);
    std::sort(pre.begin(), pre.end());
    for (auto & x: pre) {
        cout << x << ' ';
    }
    cout << endl;

    auto esq = b.esquerda();
    cout << "Tamanho=" << esq.tamanho() << endl;
    auto pre2 = esq.obtemIntervalo(10,50);
    std::sort(pre2.begin(), pre2.end());
    for (auto & x: pre2) {
        cout << x << ' ';
    }
    cout << endl;
    auto dir = b.direita();
    cout << "Tamanho=" << dir.tamanho() << endl;
    auto pre3 = dir.obtemIntervalo(10,50);
    std::sort(pre3.begin(), pre3.end());
    for (auto & x: pre3) {
        cout << x << ' ';
    }
    cout << endl;

//    for (auto it=a.preorder_begin(); it != a.preorder_end(); it++) {
//        cout << *it << ",";
//    }
//    cout << endl;
    return 0;
}
