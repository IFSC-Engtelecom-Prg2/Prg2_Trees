/* 
 * File:   arvore-impl.h
 * Author: sobral
 *
 * Created on 8 de Outubro de 2016, 19:37
 */

#ifndef ARVORE_IMPL_H
#define	ARVORE_IMPL_H

#include <sstream>
#include <ostream>

using std::ostream;
using std::ostringstream;
using std::endl;

#define IF_PTR(p) if (this->p.use_count() > 0)

#define TRY_PROC(p) if (p.use_count() == 0) throw -1; \
                 else

namespace prglib {

    template <typename T> arvore_basica<T>::arvore_basica() {

    }

    template <typename T> arvore_basica<T>::arvore_basica(const arvore_basica<T>& outra) {
        raiz = outra.raiz;
    }

    template <typename T> arvore<T>::arvore(const arvore<T>& outra) {
        TRY_PROC(outra.raiz) {
            this->raiz.reset(new nodo_arvore<T>(outra.raiz));
        }
    }

    template <typename T> arvore_basica<T>::arvore_basica(nodo_arvore<T> * ptr) {
        if (ptr != nullptr) raiz.reset(ptr);
    }

    template <typename T> arvore<T>::~arvore() {
    }

    template <typename T> void arvore<T>::adiciona(const T &dado) {
        IF_PTR(raiz) {
            this->raiz->adiciona(dado);
        } else {
            this->raiz.reset(new nodo_arvore<T>(dado));
        }
    }

    template <typename T> const T& arvore_basica<T>::obtem() const {
        TRY_PROC(raiz) {
            return raiz->obtem();
        }
    }

    template <typename T> const T& arvore_basica<T>::obtem(const T &dado) const {
        TRY_PROC(raiz) {
            return raiz->obtem(dado);
        }
    }

    template <typename T> T arvore<T>::remove(const T &dado) {
        TRY_PROC(this->raiz) {
            return this->raiz->remove(dado);
        }
    }

    template <typename T> unsigned int arvore_basica<T>::altura() const {
        TRY_PROC(raiz) {
            return raiz->altura();
        }
    }

    template <typename T> unsigned int arvore_basica<T>::tamanho() const {
        TRY_PROC(raiz) {
            return raiz->tamanho();
        }
    }

    template <typename T> void arvore<T>::balanceia() {
        TRY_PROC(this->raiz) {
            this->raiz = this->raiz->balanceia();
        }
    }

    template <typename T> void arvore<T>::balanceia(bool otimo) {
        TRY_PROC(this->raiz) {
            this->raiz = this->raiz->balanceia(otimo);
        }
    }

    template <typename T> const arvore_basica<T> arvore_basica<T>::direita() const {
        IF_PTR(raiz) {
            return arvore_basica(raiz->direita());
        } else {
            return arvore_basica();
        }
    }

    template <typename T> const arvore_basica<T> arvore_basica<T>::esquerda() const {
        IF_PTR(raiz) {
            return arvore_basica(raiz->esquerda());
        } else {
            return arvore_basica();
        }
    }

    template <typename T> nodo_arvore<T>::~nodo_arvore() {
}
    
template <typename T> nodo_arvore<T>::nodo_arvore() : BasicTree() {    
}

template <typename T> nodo_arvore<T>::nodo_arvore(const T & dado) : data(dado),BasicTree((void*)&data) {    
}

template <typename T> nodo_arvore<T>::nodo_arvore(list<T> &dados): BasicTree((void*)&data) {
    if (dados.vazia()) throw -1;
    dados.inicia();
    data = dados.proximo();
    while (! dados.fim()) adiciona(dados.proximo());
}

template <typename T> nodo_arvore<T>::nodo_arvore(istream &inp): BasicTree((void*)&data) {
    inp >> data;
    if (inp.fail()) throw -1;

    T algo;
    while (inp >> algo) adiciona(algo);
}
//template <typename T> nodo_arvore<T>::nodo_arvore(const nodo_arvore<T> & outra) : BasicTree(outra) {}

template <typename T> BasicTree * nodo_arvore<T>::create(void * p_dado) {
    T * o = (T*)p_dado;
    nodo_arvore<T> * ptr = new nodo_arvore<T>(*o);
    return (BasicTree*) ptr;
}

template <typename T> void nodo_arvore<T>::adiciona(const T & algo) {
    BasicTree::adiciona((void*)&algo);
}

template <typename T> const T& nodo_arvore<T>::obtem(const T & algo) const {
    T * o = (T*)BasicTree::obtem((void*)&algo);
    return *o;
}

template <typename T> const T& nodo_arvore<T>::obtem() const {
    return this->data;
}

template <typename T> nodo_arvore<T> * nodo_arvore<T>::esquerda() {
    return static_cast<nodo_arvore<T>*>(this->esq);
}

template <typename T> nodo_arvore<T> * nodo_arvore<T>::direita() {
    return static_cast<nodo_arvore<T>*>(this->dir);
}

template <typename T> void nodo_arvore<T>::listeEmLargura(list<T> & result) {
    list<void*> l;
    
    BasicTree::listeEmLargura(l);
    copia_lista(l , result);
}

template <typename T> void nodo_arvore<T>::listeInOrder(list<T> & result) {
    list<void*> l;
    
    BasicTree::listeInOrder(l);
    copia_lista(l , result);
}

template <typename T> void nodo_arvore<T>::copia_lista(list<void*> l, list<T> & res) {
    for (auto & x: l) {
        res.push_back(*(T*)x);
    }
}

template <typename T> void nodo_arvore<T>::listePreOrder(list<T> & result) {
    list<void*> l;
    
    BasicTree::listePreOrder(l);
    copia_lista(l , result);
}

template <typename T> void nodo_arvore<T>::listePostOrder(list<T> & result) {
    list<void*> l;
    
    BasicTree::listePostOrder(l);
    copia_lista(l , result);
}

template <typename T> unsigned int nodo_arvore<T>::tamanho() const {
    return BasicTree::tamanho();
}

template <typename T> int nodo_arvore<T>::fatorB()  {
    return BasicTree::fatorB();
}

template <typename T> unsigned int nodo_arvore<T>::altura()  {
    return BasicTree::altura();
}

template <typename T> nodo_arvore<T>* nodo_arvore<T>::balanceia() {
    nodo_arvore<T> * ptr = (nodo_arvore<T>*)BasicTree::balanceia();
    return ptr;
}

template <typename T> nodo_arvore<T>* nodo_arvore<T>::balanceia(bool otimo) {
    nodo_arvore<T> * ptr = (nodo_arvore<T>*)BasicTree::balanceia(otimo);
    return ptr;
}

//template <typename T> void nodo_arvore<T>::inicia() {
//    BasicTree::inicia();
//}
//
//template <typename T> T& nodo_arvore<T>::proximo() {
//    T * ptr = (T*)BasicTree::proximo();
//    return *ptr;
//}
//
//template <typename T> bool nodo_arvore<T>::fim() {
//    return BasicTree::fim();
//}

//template <typename T> void nodo_arvore<T>::iniciaPeloFim() {
//    BasicTree::rinicia();
//}
//
//template <typename T> T& nodo_arvore<T>::anterior() {
//    T * ptr = (T*)BasicTree::rproximo();
//    return *ptr;
//}
//
//template <typename T> bool nodo_arvore<T>::inicio() {
//    return BasicTree::rfim();
//}

template <typename T> T& nodo_arvore<T>::obtemMenor() const{
    T * ptr = (T*)BasicTree::obtemMenor();
    return *ptr;    
}

template <typename T> T nodo_arvore<T>::remove(const T & algo) {
    if (not (esq or dir)) throw -1; // tem apenas raiz
    
    T coisa;
    BasicTree::remove((void*)&algo, (void*)&coisa);
    return coisa;    
}

template <typename T> T& nodo_arvore<T>::obtemMaior() const{
    T * ptr = (T*)BasicTree::obtemMaior();
    return *ptr;    
}

template <typename T> void nodo_arvore<T>::obtemMenoresQue(list<T> & result, const T & algo) {
    list<void*> l;
    BasicTree::obtemMenoresQue(l, (void*)&algo);
    copia_lista(l , result);
}

template <typename T> void nodo_arvore<T>::obtemMaioresQue(list<T> & result, const T & algo) {
    list<void*> l;
    BasicTree::obtemMaioresQue(l, (void*)&algo);
    copia_lista(l , result);
}

template <typename T> void nodo_arvore<T>::obtemIntervalo(list<T>& result, const T& start, const T& end) {
    list<void*> l;
    BasicTree::obtemIntervalo(l, (void*)&start, (void*)&end);
    copia_lista(l , result);
}

template <typename T> nodo_arvore<T> * nodo_arvore<T>::rotacionaL() {
    nodo_arvore<T> * ptr = (nodo_arvore<T>*)BasicTree::rotacionaL();
    return ptr;
}

template <typename T> nodo_arvore<T> * nodo_arvore<T>::rotacionaR() {
    nodo_arvore<T> * ptr = (nodo_arvore<T>*)BasicTree::rotacionaR();
    return ptr;
}

template <typename T> void nodo_arvore<T>::atribui(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    *o1 = *o2;
}
    // compararação de igualdade
template <typename T> bool nodo_arvore<T>::ehIgual(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    return *o1 == *o2;
}
    
    // comparação de precedência: *p1 < *p2
template <typename T> bool nodo_arvore<T>::ehMenor(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    return *o1 < *o2;
}
    // destroi dado
template <typename T> void nodo_arvore<T>::destroi(void * p1) {
    T * o1 = (T*)p1;
    delete o1;
}

    template <typename T> void desenha_nodos(nodo_arvore<T> * arv, ostream & out) {
        auto raiz = arv->obtem();
        auto esq = arv->esquerda();
        auto dir = arv->direita();

        if (! esq and ! dir) out << raiz << endl;
        else {
            if (esq) {
                out << raiz << " -- " << esq->obtem() << endl;
                if (esq->altura()) desenha_nodos(esq, out);
            }
            if (dir) {
                out << raiz << " -- " << dir->obtem() << endl;
                if (dir->altura()) desenha_nodos(dir, out);
            }
        }

    }

    template <typename T> string desenha_nodo_arvore(nodo_arvore<T> * arv) {
        ostringstream out;

        out << "strict graph {" << endl;
        desenha_nodos(arv, out);
        out << "}" << endl;

        return out.str();
    }

    template<typename T> typename nodo_arvore<T>::preorder_iterator nodo_arvore<T>::preorder_begin() {
        return preorder_iterator(this);
    }

    template<typename T> typename nodo_arvore<T>::preorder_iterator nodo_arvore<T>::preorder_end() const {
        return preorder_iterator();
    }

    template<typename T> typename nodo_arvore<T>::inorder_iterator nodo_arvore<T>::inorder_begin() {
        return inorder_iterator(this);
    }

    template<typename T> typename nodo_arvore<T>::inorder_iterator nodo_arvore<T>::inorder_end() const {
        return inorder_iterator();
    }

    template<typename T> typename nodo_arvore<T>::preorder_riterator nodo_arvore<T>::preorder_rbegin() {
        return preorder_riterator(this);
    }

    template<typename T> typename nodo_arvore<T>::preorder_riterator nodo_arvore<T>::preorder_rend() const {
        return preorder_riterator();
    }

    template<typename T> typename nodo_arvore<T>::inorder_riterator nodo_arvore<T>::inorder_rbegin() {
        return inorder_riterator(this);
    }

    template<typename T> typename nodo_arvore<T>::inorder_riterator nodo_arvore<T>::inorder_rend() const {
        return inorder_riterator();
    }

    template<typename T>
    nodo_arvore<T>::preorder_iterator::preorder_iterator() {

    }

    template<typename T>
    nodo_arvore<T>::preorder_iterator::preorder_iterator(const nodo_arvore::preorder_iterator &it) {
        p = it.p;
    }

    template<typename T>
    nodo_arvore<T>::preorder_iterator::preorder_iterator(nodo_arvore<T> *raiz) {
        p.push(raiz);
    }

    template<typename T>
    bool nodo_arvore<T>::preorder_iterator::operator==(const nodo_arvore::preorder_iterator &it) const {
        return p == it.p;
    }

    template<typename T>
    bool nodo_arvore<T>::preorder_iterator::operator!=(const nodo_arvore::preorder_iterator &it) const {
        return p != it.p;
    }

    template<typename T>
    const T &nodo_arvore<T>::preorder_iterator::operator*() const {
        if (p.empty()) throw -1; // a meu critério ???
        auto ptr = p.top();
        return ptr->obtem();
    }

    template<typename T>
    typename nodo_arvore<T>::preorder_iterator &nodo_arvore<T>::preorder_iterator::operator++() {
        if (! p.empty()) {
            auto ptr = p.top();
            p.pop();
            if (ptr->direita() != nullptr) p.push(ptr->direita());
            if (ptr->esquerda() != nullptr) p.push(ptr->esquerda());
        }
        return *this;
    }

    template<typename T>
    typename nodo_arvore<T>::preorder_iterator &nodo_arvore<T>::preorder_iterator::operator++(int) {
        return ++(*this);
    }

    template<typename T>
    nodo_arvore<T>::preorder_riterator::preorder_riterator() {

    }

    template<typename T>
    nodo_arvore<T>::preorder_riterator::preorder_riterator(const nodo_arvore::preorder_riterator &it):preorder_iterator(it) {
    }

    template<typename T>
    nodo_arvore<T>::preorder_riterator::preorder_riterator(nodo_arvore<T> *raiz): preorder_iterator(raiz) {
    }

    template<typename T>
    typename nodo_arvore<T>::preorder_riterator &nodo_arvore<T>::preorder_riterator::operator++() {
        auto & p = this->p;

        if (! p.empty()) {
            auto ptr = p.top();
            p.pop();
            if (ptr->esquerda() != nullptr) p.push(ptr->esquerda());
            if (ptr->direita() != nullptr) p.push(ptr->direita());
        }
        return *this;
    }

    template<typename T>
    typename nodo_arvore<T>::preorder_riterator &nodo_arvore<T>::preorder_riterator::operator++(int) {
        return ++(*this);
    }

    template<typename T>
    nodo_arvore<T>::inorder_iterator::inorder_iterator(): nodo_arvore<T>::preorder_iterator() {

    }

    template<typename T>
    nodo_arvore<T>::inorder_iterator::inorder_iterator(const nodo_arvore::inorder_iterator &it): nodo_arvore<T>::preorder_iterator(it) {
    }

    template<typename T>
    nodo_arvore<T>::inorder_iterator::inorder_iterator(nodo_arvore<T> *raiz) {
        for (auto ptr = raiz; ptr != nullptr; ptr=ptr->esquerda()) {
            this->p.push(ptr);
        }
    }

    template<typename T>
    typename nodo_arvore<T>::inorder_iterator &nodo_arvore<T>::inorder_iterator::operator++() {
        if (! this->p.empty()) {
            auto ptr = this->p.top();
            this->p.pop();
            for (ptr = ptr->direita(); ptr != nullptr; ptr=ptr->esquerda()) {
                this->p.push(ptr);
            }
        }
        return *this;
    }

    template<typename T>
    typename nodo_arvore<T>::inorder_iterator &nodo_arvore<T>::inorder_iterator::operator++(int) {
        return ++(*this);
    }

    template<typename T>
    nodo_arvore<T>::inorder_riterator::inorder_riterator(): nodo_arvore<T>::preorder_iterator() {

    }

    template<typename T>
    nodo_arvore<T>::inorder_riterator::inorder_riterator(const nodo_arvore::inorder_riterator &it): nodo_arvore<T>::preorder_iterator(it) {
    }

    template<typename T>
    nodo_arvore<T>::inorder_riterator::inorder_riterator(nodo_arvore<T> *raiz) {
        for (auto ptr = raiz; ptr != nullptr; ptr=ptr->direita()) {
            this->p.push(ptr);
        }
    }

    template<typename T>
    typename nodo_arvore<T>::inorder_riterator &nodo_arvore<T>::inorder_riterator::operator++() {
        if (! this->p.empty()) {
            auto ptr = this->p.top();
            this->p.pop();
            for (ptr = ptr->esquerda(); ptr != nullptr; ptr=ptr->direita()) {
                this->p.push(ptr);
            }
        }
        return *this;
    }

    template<typename T>
    typename nodo_arvore<T>::inorder_riterator &nodo_arvore<T>::inorder_riterator::operator++(int) {
        return ++(*this);
    }

};

#endif	/* ARVORE_IMPL_H */

