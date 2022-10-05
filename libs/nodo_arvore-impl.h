//
// Created by msobral on 30/09/2022.
//

#ifndef PRG2_TREES_NODO_ARVORE_IMPL_H
#define PRG2_TREES_NODO_ARVORE_IMPL_H

#include <queue>
#include <algorithm>

namespace prglib {
    template <typename T,typename Compare> nodo_arvore<T,Compare>::~nodo_arvore() {
    }

    template <typename T,typename Compare> nodo_arvore<T,Compare>::nodo_arvore(Compare &func): comp_func(func)  {
    }

    template <typename T,typename Compare> nodo_arvore<T,Compare>::nodo_arvore(const T & dado, Compare &func) : data(dado),comp_func(func) {
    }

    template <typename T,typename Compare> void nodo_arvore<T,Compare>::adiciona(const T & algo) {
        auto p_nodo = this;

        while (true) {
            auto comp = comp_func(algo, p_nodo->data);
            if (comp == 0) {
                p_nodo->data = algo;
                break;
            }
            if (comp < 0) {
                if (!p_nodo->esq) {
                    p_nodo->esq = std::make_unique<nodo_arvore<T,Compare>>(algo, comp_func);
                    break;
                } else {
                    p_nodo = p_nodo->esq.get();
                }
            } else {
                if (!p_nodo->dir) {
                    p_nodo->dir = std::make_unique<nodo_arvore<T,Compare>>(algo, comp_func);
                    break;
                } else {
                    p_nodo = p_nodo->dir.get();
                }
            }
        }
    }

    template <typename T,typename Compare> const T& nodo_arvore<T,Compare>::obtem(const T & algo) const {
        auto p_nodo = this;

        while (p_nodo) {
            auto comp = comp_func(algo, p_nodo->data);
            if (comp == 0) {
                return p_nodo->data;
                break;
            }
            if (comp < 0) {
                p_nodo = p_nodo->esq.get();
            } else {
                p_nodo = p_nodo->dir.get();
            }
        }
        throw std::invalid_argument("valor não existe");
    }

    template <typename T,typename Compare> const T& nodo_arvore<T,Compare>::obtem() const {
        return this->data;
    }

    template <typename T,typename Compare> const nodo_arvore<T,Compare> * nodo_arvore<T,Compare>::esquerda() const {
        return static_cast<const nodo_arvore<T,Compare>*>(this->esq.get());
    }

    template <typename T,typename Compare> const nodo_arvore<T,Compare> * nodo_arvore<T,Compare>::direita() const {
        return static_cast<const nodo_arvore<T,Compare>*>(this->dir.get());
    }

    template <typename T,typename Compare> template <typename Container> void nodo_arvore<T,Compare>::listeEmLargura(Container & result) {
        std::queue<nodo_arvore<T,Compare>*> q;

        q.push(this);
        while (! q.empty()) {
            auto p_nodo = q.front();
            q.pop();
            result.push_back(p_nodo->data);
            if (p_nodo->esq) {
                q.push(p_nodo->esq.get());
            }
            if (p_nodo->dir) {
                q.push(p_nodo->dir.get());
            }
        }
    }

    template <typename T,typename Compare> template <typename Container> void nodo_arvore<T,Compare>::listeInOrder(Container & result) {
        if (esq) esq->listeInOrder(result);
        result.push_back(esq->data);
        if (dir) dir->listeInOrder(result);
    }

    template <typename T,typename Compare> template <typename Container> void nodo_arvore<T,Compare>::listePreOrder(Container & result) {
        result.push_back(esq->data);
        if (esq) esq->listeInOrder(result);
        if (dir) dir->listeInOrder(result);
    }

    template <typename T,typename Compare> template <typename Container> void nodo_arvore<T,Compare>::listePostOrder(Container & result) {
        if (esq) esq->listeInOrder(result);
        if (dir) dir->listeInOrder(result);
        result.push_back(esq->data);
    }

    template <typename T,typename Compare> unsigned int nodo_arvore<T,Compare>::tamanho() const {
        int ne=0, nd=0;

        if (esq) ne = esq->tamanho();
        if (dir) nd = dir->tamanho();
        return 1 + nd + ne;
    }

    template <typename T,typename Compare> int nodo_arvore<T,Compare>::fatorB()  {
        int he=0, hd=0;

        if (esq) he = 1 + esq->altura();
        if (dir) he = 1 + dir->altura();

        return he - hd;
    }

    template <typename T,typename Compare> unsigned int nodo_arvore<T,Compare>::altura()  {
        int he=0, hd=0;

        if (esq) he = 1 + esq->altura();
        if (dir) he = 1 + dir->altura();

        return std::max(he, hd);
    }

    template <typename T,typename Compare> nodo_arvore<T,Compare>* nodo_arvore<T,Compare>::balanceia() {
        if (not (esq or dir)) return this;
        if (esq) {
            auto p_esq = esq.release();
            esq.reset(p_esq->balanceia());
        }
        if (dir) {
            auto p_dir = dir.release();
            dir.reset(p_dir->balanceia());
        }

        int fb = fatorB();
        auto ptr = this;
        while (fb < -1) {
            if (ptr->dir->fatorB() > 0) {
                ptr->dir = ptr->dir->rotacionaL();
            }
            auto nodo = ptr->rotacionaR();
            ptr = nodo.release();
            fb = ptr->fatorB();
        }
        while (fb > 1) {
            if (ptr->esq->fatorB() < 0) {
                ptr->esq = ptr->esq->rotacionaR();
            }
            auto nodo = ptr->rotacionaL();
            ptr = nodo.release();
            fb = ptr->fatorB();
        }
        ptr->h = -1;
        return ptr;
    }

    template <typename T,typename Compare> nodo_arvore<T,Compare>* nodo_arvore<T,Compare>::balanceia(bool otimo) {
        int h;
        auto ptr = this;

        do {
            h = ptr->altura();
            ptr = ptr->balanceia();
        } while (h > ptr->altura() && otimo);
        return ptr;
    }

    template <typename T,typename Compare> const T& nodo_arvore<T,Compare>::obtemMenor() const{
        auto p_nodo = this;

        while (p_nodo->esq) p_nodo = p_nodo->esq.get();
        return p_nodo->data;
    }

    template <typename T,typename Compare> T nodo_arvore<T,Compare>::remove(const T & algo) {
        throw std::runtime_error("not implemented");
    }

    template <typename T,typename Compare> const T& nodo_arvore<T,Compare>::obtemMaior() const{
        auto p_nodo = this;

        while (p_nodo->dir) p_nodo = p_nodo->dir.get();
        return p_nodo->data;
    }

    template <typename T,typename Compare> void nodo_arvore<T,Compare>::obtemMenoresQue(list<T> & result, const T & algo) {
        if (data <= algo) {
            result.push_back(data);
            if (esq) esq->listePreOrder(result);
            if (dir) dir->obtemMenoresQue(result, algo);
        } else {
            if (esq) esq->obtemMenoresQue(result, algo);
        }
    }

    template <typename T,typename Compare> void nodo_arvore<T,Compare>::obtemMaioresQue(list<T> & result, const T & algo) {
        if (data >= algo) {
            result.push_back(data);
            if (dir) dir->listePreOrder(result);
            if (esq) esq->obtemMaioresQue(result, algo);
        } else {
            if (dir) dir->obtemMaioresQue(result, algo);
        }
    }

    template <typename T,typename Compare> void nodo_arvore<T,Compare>::obtemIntervalo(list<T>& result, const T& start, const T& end) {
        if (data < start) {
            if (dir) dir->obtemIntervalo(result, start, end);
        } else if (data > end) {
            if (esq) esq->obtemIntervalo(result, start, end);
        } else {
            result.push_back(data);
            if (dir) dir->obtemIntervalo(result, start, end);
            if (esq) esq->obtemIntervalo(result, start, end);
        }
    }

    template <typename T,typename Compare> std::unique_ptr<nodo_arvore<T,Compare>> nodo_arvore<T,Compare>::rotacionaL() {
        auto p3 = this;
//        auto & p2 = p3->esq;
//        auto & c = p2->dir;
        auto p2 = p3->esq;
        auto c = p2->dir;

        p3->esq = c;
        p2->dir = p3;

        return p2;
    }

    template <typename T,typename Compare> std::unique_ptr<nodo_arvore<T,Compare>> nodo_arvore<T,Compare>::rotacionaR() {
        auto p1 = this;
        auto p2 = p1->dir;
        auto b = p2->esq;

        p1->dir = b;
        //if (b) b->pai = p1;
        p2->esq = p1;
        //p1->pai = p2;
        //p2->pai = nullptr; // nova raiz
        return p2;
    }
}
#endif //PRG2_TREES_NODO_ARVORE_IMPL_H
