//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <fstream>
#include <list>
#include <string_view>
#include "prglib.h"
#include "gtest/gtest.h"

using namespace std;

class TesteArvore: public ::testing::Test {
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

const std::string DataFile("../tests/portugues.txt");

TEST_F(TesteArvore, CriarVazia) {
    auto a = prglib::cria_arvore<int>();
    ASSERT_TRUE(a.vazia());
}

TEST_F(TesteArvore, CriarFolha) {
    auto a = prglib::cria_arvore<int>();
    a.adiciona(7);
    ASSERT_EQ(a.obtem(), 7);
}

TEST_F(TesteArvore, CriarComContainer) {
    std::vector<int> v = {7,3,1,4,2,5,13,9,8,11,12,15};
    auto a = prglib::cria_arvore<int>(v);
    ASSERT_EQ(a.obtem(), 7);
}

TEST_F(TesteArvore, Menor) {
    std::ifstream arq(DataFile);
    auto a = prglib::cria_arvore<std::string>(arq);
    ASSERT_EQ(a.obtemMenor(), "AC");
}

TEST_F(TesteArvore, Maior) {
    std::ifstream arq(DataFile);
    auto a = prglib::cria_arvore<std::string>(arq);
    ASSERT_EQ(a.obtemMaior(), "zurrou");
}

TEST_F(TesteArvore, Obtem) {
    std::ifstream arq(DataFile);
    auto a = prglib::cria_arvore<std::string>(arq);
    ASSERT_EQ(a.obtem("praia"), "praia");
    ASSERT_ANY_THROW(a.obtem("askxnasj"));
}

TEST_F(TesteArvore, ListePreOrder) {
    std::vector<int> v = {5,3,1,2,7,6,8};
    auto a = prglib::cria_arvore<int>(v);
    auto pre = a.listePreOrder();

    ASSERT_EQ(v, pre);
}

TEST_F(TesteArvore, ListeInOrder) {
    std::vector<int> v = {5,3,1,2,7,6,8};
    auto a = prglib::cria_arvore<int>(v);
    auto pre = a.listeInOrder();
    std::sort(v.begin(), v.end());
    ASSERT_EQ(v, pre);
}

TEST_F(TesteArvore, ListePostOrder) {
    std::vector<int> v = {5,3,1,2,7,6,8};
    std::vector<int> r = { 2, 1, 3, 6, 8, 7, 5 };
    auto a = prglib::cria_arvore<int>(v);
    auto pre = a.listePostOrder();

    ASSERT_EQ(r, pre);
}

TEST_F(TesteArvore, ListeEmLargura) {
    std::vector<int> v = {5,3,1,2,7,6,8};
    std::vector<int> r = { 5, 3, 7, 1, 6, 8, 2 };
    auto a = prglib::cria_arvore<int>(v);
    auto pre = a.listeEmLargura();

    ASSERT_EQ(r, pre);
}

TEST_F(TesteArvore, IteradorPreOrder) {
    std::vector<int> v = {5,3,1,2,7,6,8};
    std::vector<int> r;

    auto a = prglib::cria_arvore<int>(v);
    std::copy(a.preorder_begin(), a.preorder_end(), std::back_inserter(r));

    ASSERT_EQ(v, r);
}

TEST_F(TesteArvore, IteradorInOrder) {
    std::vector<int> v = {5,3,1,2,7,6,8};
    std::vector<int> r;

    auto a = prglib::cria_arvore<int>(v);
    std::copy(a.inorder_begin(), a.inorder_end(), std::back_inserter(r));
    std::sort(v.begin(), v.end());

    ASSERT_EQ(v, r);
}

TEST_F(TesteArvore, MenoresQue) {
    std::vector<int> v = {5,3,1,2,7,6,8,12,15,11,9,0,4};

    auto a = prglib::cria_arvore<int>(v);
    auto res = a.obtemMenoresQue(7);
    auto ok = std::all_of(res.begin(), res.end(), [](auto & x) { return x < 8;});
    ASSERT_TRUE(ok);
}

TEST_F(TesteArvore, MaioresQue) {
    std::vector<int> v = {5,3,1,2,7,6,8,12,15,11,9,0,4};

    auto a = prglib::cria_arvore<int>(v);
    auto res = a.obtemMaioresQue(7);
    auto ok = std::all_of(res.begin(), res.end(), [](auto & x) { return x > 6;});
    ASSERT_TRUE(ok);
}

TEST_F(TesteArvore, ObtemIntervalo) {
    std::vector<int> v = {5,3,1,2,7,6,8,12,15,11,9,0,4};

    auto a = prglib::cria_arvore<int>(v);
    auto res = a.obtemIntervalo(6,10);
    auto ok = std::all_of(res.begin(), res.end(), [](auto & x) { return x >= 6 && x <= 10;});
    ASSERT_TRUE(ok);
}

TEST_F(TesteArvore, Remove) {
    std::vector<int> v = {5,3,1,2,7,6,8,12,15,11,9,0,4};

    auto a = prglib::cria_arvore<int>(v);
    auto res = a.remove(7);
    ASSERT_EQ(res, 7);
    ASSERT_ANY_THROW(a.remove(7));
}

TEST_F(TesteArvore, Existe) {
    std::vector<int> v = {5,3,1,2,7,6,8,12,15,11,9,0,4};

    auto a = prglib::cria_arvore<int>(v);
    ASSERT_TRUE(a.existe(15));
    ASSERT_FALSE(a.existe(99));
}

TEST_F(TesteArvore, Adiciona) {
    std::vector<int> v = {5,3,1,2,7,6,8,12,15,11,9,0,4};

    auto a = prglib::cria_arvore<int>(v);
    a.adiciona(23);
    ASSERT_TRUE(a.existe(23));
}

TEST_F(TesteArvore, CriarComparacaoEspecial) {
    std::vector<int> v = {-5,-3,1,2,-7,6,8,12,-15,11,9,0,4};
    std::vector<int> esperado = { -5, -3, 1, 0, 2, 4, -7, 6, 8, 12, 11, 9, -15 };
    auto comp = [](const auto & x, const auto & y) { return abs(x)<abs(y)?-1:abs(x)!=abs(y);};

    auto a = prglib::cria_arvore_esp<int>(comp, v);
    auto obtido = a.listePreOrder();

    ASSERT_EQ(esperado, obtido);
}

TEST_F(TesteArvore, CriarArvoreGrande) {
    std::ifstream arq(DataFile);
    auto a = prglib::cria_arvore<std::string>(arq);
    ASSERT_EQ(a.tamanho(), 245366);
}

TEST_F(TesteArvore, BalanceiaSimples) {
    std::ifstream arq(DataFile);
    auto a = prglib::cria_arvore<std::string>(arq);
    a.balanceia();
    ASSERT_EQ(a.altura(), 23);
}

TEST_F(TesteArvore, BalanceiaOtimo) {
    std::ifstream arq(DataFile);
    auto a = prglib::cria_arvore<std::string>(arq);
    a.balanceia(true);
    ASSERT_EQ(a.altura(), 21);
}
