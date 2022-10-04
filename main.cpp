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
    vector<int> v = {5,3,2,4,8,6,9};
    list<int> l;
    auto a = prglib::cria_arvore<int>(v);
    auto b = prglib::cria_arvore<int>();

    cout << "Valor da raiz: " << a.obtem() << endl;
    cout << "Valor: " << a.obtem(5) << endl;

    a.adiciona(16);
    a.adiciona(17);
    a.adiciona(18);
    a.adiciona(19);

   if (a.existe(18)) {
      cout << 18 << " existe" << endl;
   }
   if (! a.existe(14)) {
      cout << 14 << " não existe" << endl;
   }

//    a.remove(5);
//    cout << "Altura: " << a.altura() << endl;
    a.balanceia();
    cout << "Altura: " << a.altura() << endl;

    // copia a árvore
    b = a;
    
    // iteração da árvore: obtém os valores em ordem crescente (in-order)
    // note que foi necessário referenciar o ponteiro "a" para
    // poder usar esta forma de iteração
    for (auto & x: b) {
        cout << x << ",";
    }
    cout << endl;

    // Aqui é um exemplo de iteração usando explicitamente o iterador
    // O tipo de iteração é o mesmo que o exemplo anterior: ordem crescente
    for (auto it = a.inorder_begin(); it != a.inorder_end(); it++) {
        cout << *it << ",";
    }
    cout << endl;

    // Esta é uma terceira forma de iterar a árvore. Os dados são copiados
    // para uma lista
    l.clear();
    a.listeInOrder(l);

    cout << "Dados ordenados: ";
    for (auto & x: l) {
        cout << x << ", ";
    }
    cout << endl;

    cout << a.obtemMaior() << ", " << a.obtemMenor() << endl;

    // Apenas para fins de visualização, a função abaixo desenha uma árvore
    // Ela gera um diagrama no format "dot", que pode então ser gravado em arquivo
    // e visualizado com o programa "dotty"
    auto diagrama = desenha_arvore(a);

    ofstream diag("tree.dot");
    diag << diagrama;
    diag.close();

    return 0;
}
