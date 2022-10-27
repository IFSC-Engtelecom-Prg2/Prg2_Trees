#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <prglib.h>

struct Ponto {
    double x,y;
};

// função que calcula o módulo ao quadrado de um ponto
double modulo_ponto(const Ponto & p) {
    return p.x*p.x + p.y*p.y;
}

// compara os módulos dos pontos !
int comp_pontos(const Ponto & p1, const Ponto & p2) {
    double m1 = modulo_ponto(p1);
    double m2 = modulo_ponto(p2);

    if (m1 < m2) {
        return -1;
    }
    return m1 > m2;
}

int main() {
    // cria uma árvore de pontos
    auto arv = prglib::cria_arvore<Ponto>(comp_pontos);

    // adiciona alguns pontos
    arv.adiciona(Ponto{1.5, 0.9});
    arv.adiciona(Ponto{0.5, 1.9});
    arv.adiciona(Ponto{0.1, 2.9});

    for (auto & p: arv) {
        std::cout << p.x << "," << p.y << std::endl;
    }

}