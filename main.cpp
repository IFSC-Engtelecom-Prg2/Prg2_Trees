#include <iostream>
#include <fstream>
#include <prglib.h>

using namespace std;

using prglib::arvore;

/*
 *
 */
struct Algo {
    int num;
    string nome;
};

int comp_algo(const Algo & a1, const Algo & a2) {
   return prglib::default_compare(a1.num, a2.num);
}

int main(int argc, char** argv) {
    ifstream inp("tree.txt");
//    arvore<int> a(inp), b; // cria a árvore e acrescenta a ela os valores contidos no arquivo
    list<Algo> la = {{1,"um"}, {5, "cinco"}, {-1, "neg"}};
    auto a = prglib::cria_arvore_esp<Algo>(comp_algo, la);
    auto b = prglib::cria_arvore_esp<Algo>(comp_algo);

    /*
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

//    a.remove(7);
    cout << "Altura: " << a.altura() << endl;
    a.balanceia();
    cout << "Altura: " << a.altura() << endl;

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
    list<int> l;
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
     */
}
