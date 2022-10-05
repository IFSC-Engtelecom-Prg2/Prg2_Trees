/* 
 * File:   arvore.h
 * Author: msobral
 *
 * Created on 12 de Agosto de 2016, 13:12
 */

#ifndef ARVORE_H
#define	ARVORE_H

#include <libs/BasicTree.h>
#include <list>
#include <istream>
#include <string>
#include <iterator>
#include <stack>
#include <queue>
#include <memory>
#include "nodo_arvore.h"

using std::string;
using std::istream;
using std::list;
using std::forward_iterator_tag;
using std::stack;
using std::queue;

namespace prglib {
    
    template <typename T,typename Compare> class nodo_arvore;

    // Uma função default para comparação de valores ordenáveis, usada pela árvore
    // Resultados:
    // -1: se x1 < x2
    // 1: se x1 > x2
    // 0: se x1 == x2
    template <typename T> int default_compare(const T & x1, const T & x2) {
        return x1<x2?-1:x1!=x2;
    }

    // Uma arvore de pesquisa binária com operações que não modificam sua estrutura
    // Esta classe implementa as funcionalidades básicas, que não alteram a árvore
    // Isso possibilita que seus objetos compartilhem nodos (com limitações)
    // A função de comparação para o tipo dos dados armazenados deve ser definida
    // como uma função binária, com resultados: 0 se dados iguais, -1 se arg1 < arg2,
    // 1 se arg1 > arg2
    template <typename T, typename Compare> class arvore_basica {
    public:
        arvore_basica(Compare compare);
        arvore_basica(const arvore_basica<T,Compare> & outra);
        template <typename Container> arvore_basica(Container & dados, Compare compare);
        arvore_basica(istream & inp, Compare compare);

        ~arvore_basica();

        arvore_basica& operator=(const arvore_basica<T,Compare> & outra);

        // testa se dado existe na árvore
        bool existe(const T & dado) const;

        // retorna o valor da raiz. Se árvore vazia dispara exceção
        const T & obtem() const;

        // retorna valor da árvore equivalente a dado
        // se árvore vazia dispara exceção
        const T & obtem(const T & dado) const;
        
        bool vazia() const;

        // iteradores PRE-ORDER e IN-ORDER
        class preorder_iterator;
        class inorder_iterator;
        class preorder_riterator;
        class inorder_riterator;

        // iteradores default: inorder
        inorder_iterator begin() const { return inorder_begin(); }
        inorder_iterator end() const { return inorder_end(); }

        // iteradores diretos ...
        preorder_iterator preorder_begin() const;
        preorder_iterator preorder_end() const;
        inorder_iterator inorder_begin()const;
        inorder_iterator inorder_end() const;
        // iteradores reversos ...
        preorder_riterator preorder_rbegin()const;
        preorder_riterator preorder_rend() const;
        inorder_riterator inorder_rbegin()const ;
        inorder_riterator inorder_rend() const;

        // Versão alternativa: enumera os dados in-order, pre-order, post-order e breadth-first
        // copiando-os para uma lista
        template <typename Container> void listeInOrder(Container & result);
        template <typename Container> void listePreOrder(Container & result);
        template <typename Container> void listePostOrder(Container & result);
        template <typename Container> void listeEmLargura(Container & result);

        // retorna a quantidade de dados na árvore
        unsigned int tamanho() const;

        // retorna a subárvore esquerda
        // Ela compartilha os nodos desta árvore
        // Se o ramo esquerdo desta árvore for destruído,
        // a árvore retornada fica inválida ... se for usada depois disso,
        // um erro de acesso à memória ocorrerá
        const arvore_basica<T,Compare> esquerda() const;

        // retorna a subárvore direita
        // mesmas restrições que "esquerda()"
        const arvore_basica<T,Compare> direita() const;

        // retorna o menor dado
        const T & obtemMenor() const;

        // retorna o maior dado
        const T & obtemMaior() const;

        // copia na lista "result" os dados menores que "algo"
        void obtemMenoresQue(list<T> & result, const T & algo) const;

        // copia na lista "result" os dados maiores que "algo"
        void obtemMaioresQue(list<T> & result, const T & algo) const;

        // obtém todos valores entre "start" e "end" (inclusive)
        void obtemIntervalo(list<T> & result, const T & start, const T & end) const;

        // retorna a altura da folha mais distante da raiz
        unsigned int altura() const;

        // retorna o fator de balanceamento
        int fatorB() const;

    protected:
        nodo_arvore<T,Compare>* raiz;
        Compare comp_func;
        bool _owner;

        arvore_basica(nodo_arvore<T,Compare> * ptr, Compare compare);
    public:
        class preorder_iterator: public forward_iterator_tag {
        public:
            preorder_iterator();
            preorder_iterator(const preorder_iterator & it);
            preorder_iterator(const nodo_arvore<T,Compare> * raiz);
            ~preorder_iterator() {}

            bool operator==(const preorder_iterator & it) const;
            bool operator!=(const preorder_iterator & it) const;
            const nodo_arvore<T,Compare>* operator->() const;
            const T& operator*() const;
            virtual preorder_iterator& operator++();
            virtual preorder_iterator& operator++(int);
        protected:
            stack<const nodo_arvore<T,Compare>*> p;
        };

        class inorder_iterator: public preorder_iterator {
        public:
            inorder_iterator();
            inorder_iterator(const inorder_iterator & it);
            inorder_iterator(const nodo_arvore<T,Compare> * raiz);
            ~inorder_iterator() {}

            virtual inorder_iterator& operator++();
            inorder_iterator& operator++(int);
        };

        class preorder_riterator: public preorder_iterator {
        public:
            preorder_riterator();
            preorder_riterator(const preorder_riterator & it);
            preorder_riterator(const nodo_arvore<T,Compare> * raiz);
            ~preorder_riterator() {}

            virtual preorder_riterator& operator++();
            preorder_riterator& operator++(int);
        };

        class inorder_riterator: public preorder_iterator {
        public:
            inorder_riterator();
            inorder_riterator(const inorder_riterator & it);
            inorder_riterator(const nodo_arvore<T,Compare> * raiz);
            ~inorder_riterator() {}

            virtual inorder_riterator& operator++();
            inorder_riterator& operator++(int);
        };
    };

    // Uma árvore de pesquisa binária que pode ser modificada
    // Esta árvore estende arvore_basica com operações que modificam sua estrutura
    template <typename T, typename Compare> class arvore : public arvore_basica<T,Compare> {
    public:
        arvore(Compare compare);
        arvore(const arvore<T,Compare> & outra);
        template <typename Container> arvore(Container & dados, Compare compare);
        arvore(istream & inp, Compare compare);
        ~arvore();

        void adiciona(const T & dado);
        T remove(const T & dado);

        // balanceia a árvore
        void balanceia();

        // balanceia a árvore repetidamente, até que a altura não mais se reduza
        void balanceia(bool otimo);

    };


// gera uma descrição de um diagrama DOT para a árvore
// O resultado deve ser gravado em arquivo para se gerar o diagrama
// com o programa "dot" ou "dotty"
template <typename T, typename Compare> string desenha_arvore(const arvore_basica<T,Compare> & arv);


    // cria uma árvore com um comparador especializado, que deve ser o primeiro parâmetro
    template <typename T, typename Compare, typename... Args> decltype(auto) cria_arvore_esp(Compare func, Args&... args) {
        return arvore<T,Compare>(args..., func);
    }

    // cria uma árvore com o comparador predefinido
    template <typename T, typename... Args> decltype(auto) cria_arvore(Args&... args) {
        return cria_arvore_esp<T>(default_compare<T>, args...);
    }

} // fim do namespace

#include <libs/arvore-impl.h>

#endif	/* ARVORE_H */

