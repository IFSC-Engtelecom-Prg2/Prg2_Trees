#include <iostream>
#include <fstream>
#include <prglib.h>

using namespace std;

using prglib::arvore;

/*
 *
 */
int main(int argc, char** argv) {
    ifstream inp("../tree.txt");
    auto a = new arvore<int>(inp);

    cout << "Valor da raiz: " << a->obtem() << endl;
    cout << "Valor: " << a->obtem(5) << endl;

    for (auto it = a->inorder_rbegin(); it != a->inorder_rend(); it++) {
        cout << *it << endl;
    }
    list<int> l;
    a->listeInOrder(l);

    cout << "Dados ordenados: ";
    for (auto & x: l) {
        cout << x << ", ";
    }
    cout << endl;

    auto diagrama = desenha_arvore(a);

    ofstream diag("tree.dot");
    diag << diagrama;
    diag.close();

    return 0;
}
