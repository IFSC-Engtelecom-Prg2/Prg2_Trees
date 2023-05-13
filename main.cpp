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

std::ostream& operator<<(ostream& out, const Ponto & p) {
    out << '{' << p.x << ',' << p.y << '}';
    return out;
}


// compara os módulos dos pontos !
bool comp_pontos(const Ponto & p1, const Ponto & p2) {
    double m1 = modulo_ponto(p1);
    double m2 = modulo_ponto(p2);

    std::cout << "comp_pontos(" << p1 << ", " << p2 << ")" << std::endl;
    return m1 < m2;
}
//using comp = decltype(&comp_pontos);

bool operator<(const Ponto & p1, const Ponto & p2) {
    double m1 = modulo_ponto(p1);
    double m2 = modulo_ponto(p2);
    std::cout << p1 << " < " << p2 << std::endl;
    return m1 < m2;
}

void mostra(prglib::arvore<Ponto> & arv) {
    for (auto & p: arv) {
        std::cout << p << std::endl;
    }
}

int main() {
    // cria uma árvore de pontos
//    prglib::arvore<int> a0 = {7,3,6,1,4,2,10,8};
//    auto v = a0.obtemMaioresQue(8);
//    for (auto & x: v) {
//        std::cout << x << std::endl;
//    }
//    return 0;

    auto arv = prglib::cria_arvore<Ponto>(comp_pontos);
//    prglib::arvore<Ponto> arv;
//     adiciona alguns pontos
    arv.adiciona(Ponto{1.5, 0.9});
    arv.adiciona(Ponto{0.5, 1.9});
    arv.adiciona(Ponto{0.1, 2.9});

    mostra(arv);
    std::cout << std::boolalpha << arv.existe(Ponto{0.3, 1.9}) << std::endl;
    return 0;

    auto obj = arv.procura(Ponto{0.5, 1.9});
    if (obj) {
        auto val = obj.value().get();
        auto p = arv.obtem(Ponto{0.5, 1.9});
        std::cout << val << ", " << (void*)&val << " ... " << (void*)&p << std::endl;
    }
    for (auto & p: arv) {
        std::cout << p.x << "," << p.y << std::endl;
    }

}