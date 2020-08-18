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

    // iteração da árvore: obtém os valores em ordem crescente (in-order)
    // note que foi necessário referenciar o ponteiro "a" para
    // poder usar esta forma de iteração
    for (auto & x: *a) {
        cout << x << ",";
    }
    cout << endl;

    // Aqui é um exemplo de iteração usando explicitamente o iterador
    // O tipo de iteração é o mesmo que o exemplo anterior: ordem crescente
    for (auto it = a->inorder_begin(); it != a->inorder_end(); it++) {
        cout << *it << ",";
    }
    cout << endl;

    // Esta é uma terceira forma de iterar a árvore. Os dados são copiados
    // para uma lista
    list<int> l;
    a->listeInOrder(l);

    cout << "Dados ordenados: ";
    for (auto & x: l) {
        cout << x << ", ";
    }
    cout << endl;

    // Apenas para fins de visualização, a função abaixo desenha uma árvore
    // Ela gera um diagrama no format "dot", que pode então ser gravado em arquivo
    // e visualizado com o programa "dotty"
    auto diagrama = desenha_arvore(a);

    ofstream diag("tree.dot");
    diag << diagrama;
    diag.close();

    return 0;
}
