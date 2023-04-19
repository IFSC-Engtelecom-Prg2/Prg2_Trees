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

std::ostream& operator<<(ostream& out, const Ponto & p) {
    out << '{' << p.x << ',' << p.y << '}';
    return out;
}
int main() {
    // cria uma árvore de pontos
    auto arv = prglib::cria_arvore<Ponto>(comp_pontos);

    // adiciona alguns pontos
    arv.adiciona(Ponto{1.5, 0.9});
    arv.adiciona(Ponto{0.5, 1.9});
    arv.adiciona(Ponto{0.1, 2.9});

    for (auto it=arv.bfs_begin(); it != arv.bfs_end(); it++) {
        std::cout << *it << ";";
    }
    std::cout << std::endl;

    auto obj = arv.procura(Ponto{0.5, 1.9});
    if (obj) {
        auto & val = obj->get();
        auto & p = arv.obtem(Ponto{0.5, 1.9});
        std::cout << val << ", " << (void*)&val << " ... " << (void*)&p << std::endl;
    }
    for (auto & p: arv) {
        std::cout << p.x << "," << p.y << std::endl;
    }

}