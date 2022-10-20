//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <list>
#include "verifica.h"
#include "gtest/gtest.h"

using namespace std;

class TesteOrdenada: public ::testing::Test {
protected:
    virtual void SetUp() {
        srand(clock());
    }

    void escreva_lista(list<int> & l, const string & sep, ostream & out) {
        if (l.empty()) return;
        int n = l.size();
        auto it=l.begin();
        for (; n > 1; it++, n--) out << *it << sep;
        out << *it;
    }

};

/*::testing::AssertionResult AssertSubstitui(const char* texto_expr,
                                               const char* sub_expr,
                                               const char* outra_expr,
                                               const char* correto_expr,
                                               const string & texto,
                                               const string & sub,
                                               const string & outra,
                                               const string & correto) {
    string res = substitui(texto, sub, outra);
    if (res == correto) return ::testing::AssertionSuccess();

    return ::testing::AssertionFailure() << "texto=" << texto << ", " << sub_expr << "=" << sub << ", " << outra_expr << "=" << outra << ": "
                                         << " resultado deveria ser: " << correto
                                         << ", mas sua função retornou: " << res;
}
*/

TEST_F(TesteOrdenada, Vazia) {
    list<int> l;

    try {
        if (not ordenada(l)) {
            FAIL() <<"lista vazia deve ser considerada ordenada";
            return;
        }
    } catch (...) {
        FAIL() <<"falha fatal ao verificar lista";
    }
}

TEST_F(TesteOrdenada, Simples) {
    list<int> l;
    l.push_back(119);

    try {
        if (not ordenada(l)) {
            FAIL() <<"lista com apenas um número deve ser considerada ordenada";
            return;
        }
    } catch (...) {
        FAIL() <<"falha fatal ao verificar lista";
    }

}

TEST_F(TesteOrdenada, Ordenada)        {
    list<int> l;
    int n = 10 + rand() % 20;
    while (n > 0) {
        l.push_back(rand() % 100);
        n--;
    }
    l.sort();
    try {
        if (not ordenada(l)) {
            ostringstream os;

            escreva_lista(l, ",", os);
            FAIL() <<"resultado deve ser true para lista ordenada com valores: "+os.str();
            return;
        }
    } catch (...) {
        FAIL() <<"falha fatal ao verificar lista";
    }
}

TEST_F(TesteOrdenada, Desordenada) {
    list<int> l;
    int n = 10 + rand() % 20;
    while (n > 0) {
        l.push_back(rand() % 100);
        n--;
    }

    try {
        if (ordenada(l)) {
            ostringstream os;

            escreva_lista(l, ",", os);
            FAIL() <<"resultado deve ser false para lista desordenada com valores: "+os.str();
            return;
        }
    } catch (...) {
        FAIL() <<"falha fatal ao verificar lista";
    }
}

TEST_F(TesteOrdenada, Preservar) {
    list<int> l;
    int n = 10 + rand() % 20;
    while (n > 0) {
        l.push_back(rand() % 100);
        n--;
    }

    try {
        list<int> aux = l;
        ordenada(l);
        if (not (l == aux)) {
            FAIL() <<"lista não pode ser modificada pela função";
            return;
        }
    } catch (...) {
        FAIL() <<"falha fatal ao verificar lista";
    }
}