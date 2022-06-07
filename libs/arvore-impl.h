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
#include <stdexcept>

using std::ostream;
using std::ostringstream;
using std::endl;

#define IF_PTR(p) if (this->p != nullptr)

#define TRY_PROC(p) if (p == nullptr) throw std::runtime_error("árvore vazia"); \
                 else

namespace prglib {

    template <typename T, typename Compare> arvore_basica<T,Compare>::arvore_basica(Compare compare):raiz(nullptr),comp_func(compare) {

    }

    template <typename T, typename Compare> arvore_basica<T,Compare>::~arvore_basica() {

    }

    template <typename T, typename Compare> arvore_basica<T,Compare>::arvore_basica(const arvore_basica<T,Compare>& outra): raiz(nullptr),comp_func(outra.comp_func) {
        *this = outra;
    }

    template <typename T, typename Compare> arvore_basica<T,Compare>::arvore_basica(const nodo_arvore<T,Compare> * ptr, Compare compare): comp_func(compare) {
        nodo_arvore<T,Compare> * p = (nodo_arvore<T,Compare>*)ptr;
        raiz = p;
    }

    template <typename T, typename Compare> arvore_basica<T,Compare>::arvore_basica(istream &inp,Compare compare): comp_func(compare) {
        T data;

        inp >> data;
        if (inp.fail()) throw std::runtime_error("não pode ler da stream");
        raiz = new nodo_arvore<T,Compare>(data,this->comp_func);

        while (inp >> data) raiz->adiciona(data);
    }

    template <typename T, typename Compare> arvore_basica<T,Compare>::arvore_basica(list<T> &dados,Compare compare): comp_func(compare) {
        if (! dados.empty()) {
            auto it = dados.begin();
            raiz = new nodo_arvore<T,Compare>(*it,this->comp_func);
            for (it++; it != dados.end(); it++) raiz->adiciona(*it);
        }
    }

    template <typename T, typename Compare> arvore_basica<T,Compare>& arvore_basica<T,Compare>::operator=(const arvore_basica<T,Compare> & outra) {
        IF_PTR(raiz) delete raiz;
        
        if (!outra.vazia()) {
            auto it = outra.preorder_begin();
            raiz = new nodo_arvore<T,Compare>(it->obtem(),this->comp_func);
            for (; it != outra.preorder_end(); it++) {
                raiz->adiciona(it->obtem());
            }
        } else raiz = nullptr;
    	return *this;
    }

    template <typename T, typename Compare> bool arvore_basica<T,Compare>::existe(const T & dado) const {
        bool status = false;
        if (! vazia()) {
            try {
                raiz->obtem(dado);
                status=true;
            } catch (...) {            
            }
        }
        return status;
    }

    template <typename T, typename Compare> bool arvore_basica<T,Compare>::vazia() const {
        return raiz == nullptr;
    }

    template <typename T, typename Compare> const T& arvore_basica<T,Compare>::obtem() const {
        TRY_PROC(raiz) {
            return raiz->obtem();
        }
    }

    template <typename T, typename Compare> const T& arvore_basica<T,Compare>::obtem(const T &dado) const {
        TRY_PROC(raiz) {
            return raiz->obtem(dado);
        }
    }

    template <typename T, typename Compare> const arvore_basica<T,Compare> arvore_basica<T,Compare>::direita() const {
        IF_PTR(raiz) {
            return arvore_basica(raiz->direita(), comp_func);
        } else {
            return arvore_basica();
        }
    }

    template <typename T, typename Compare> const arvore_basica<T,Compare> arvore_basica<T,Compare>::esquerda() const {
        IF_PTR(raiz) {
            return arvore_basica(raiz->esquerda(), comp_func);
        } else {
            return arvore_basica();
        }
    }

    template <typename T, typename Compare> unsigned int arvore_basica<T,Compare>::altura() const {
        TRY_PROC(raiz) {
            return raiz->altura();
        }
    }

    template <typename T, typename Compare> unsigned int arvore_basica<T,Compare>::tamanho() const {
        TRY_PROC(raiz) {
            return raiz->tamanho();
        }
    }

    template <typename T, typename Compare> int arvore_basica<T,Compare>::fatorB() const {
        TRY_PROC(raiz) {
            return raiz->fatorB();
        }
    }

    template <typename T, typename Compare> const T& arvore_basica<T,Compare>::obtemMaior() const {
        TRY_PROC(raiz) {
            return raiz->obtemMaior();
        }
    }

    template <typename T, typename Compare> const T& arvore_basica<T,Compare>::obtemMenor() const {
        TRY_PROC(raiz) {
            return raiz->obtemMenor();
        }
    }

    template <typename T, typename Compare> void arvore_basica<T,Compare>::listeInOrder(list<T> &result) {
        IF_PTR(raiz) {
            return raiz->listeInOrder(result);
        }
    }

    template <typename T, typename Compare> void arvore_basica<T,Compare>::listePreOrder(list<T> &result) {
        IF_PTR(raiz) {
            return raiz->listePreOrder(result);
        }
    }

    template <typename T, typename Compare> void arvore_basica<T,Compare>::listePostOrder(list<T> &result) {
        IF_PTR(raiz) {
            return raiz->listePostOrder(result);
        }
    }

    template <typename T, typename Compare> void arvore_basica<T,Compare>::listeEmLargura(list<T> &result) {
        IF_PTR(raiz) {
            return raiz->listeEmLargura(result);
        }
    }

    template <typename T, typename Compare> void arvore_basica<T,Compare>::obtemMaioresQue(list<T> &result, const T &algo) const {
        IF_PTR(raiz) {
            return raiz->obtemMaioresQue(result, algo);
        }
    }

    template <typename T, typename Compare> void arvore_basica<T,Compare>::obtemMenoresQue(list<T> &result, const T &algo) const {
        IF_PTR(raiz) {
            return raiz->obtemMenoresQue(result, algo);
        }
    }

    template <typename T, typename Compare> void arvore_basica<T,Compare>::obtemIntervalo(list<T> &result, const T &start, const T &end) const {
            IF_PTR(raiz) {
            return raiz->obtemIntervalo(result, start, end);
        }
    }

    template <typename T, typename Compare> arvore<T,Compare>::arvore(Compare compare): arvore_basica<T,Compare>(compare) {
    }

    template <typename T, typename Compare> arvore<T,Compare>::arvore(const arvore<T,Compare>& outra): arvore_basica<T,Compare>(outra) {
    }

    template <typename T, typename Compare> arvore<T,Compare>::arvore(list<T> &dados, Compare compare): arvore_basica<T,Compare>(dados, compare) {}

    template <typename T, typename Compare> arvore<T,Compare>::arvore(istream &inp, Compare compare): arvore_basica<T,Compare>(inp, compare) {}

    template <typename T, typename Compare> arvore<T,Compare>::~arvore() {
        IF_PTR(raiz) {
            delete this->raiz;
        }
    }

    template <typename T, typename Compare> void arvore<T,Compare>::adiciona(const T &dado) {
        IF_PTR(raiz) {
            this->raiz->adiciona(dado);
        } else {
            this->raiz = new nodo_arvore<T,Compare>(dado,this->comp_func);
        }
    }

    template <typename T, typename Compare> T arvore<T,Compare>::remove(const T &dado) {
        TRY_PROC(this->raiz) {
            if (this->raiz->folha()) {
                auto algo = this->raiz->obtem();
                delete this->raiz;
                this->raiz = nullptr;
                return algo;
            }
            return this->raiz->remove(dado);
        }
    }

    template <typename T, typename Compare> void arvore<T,Compare>::balanceia() {
        TRY_PROC(this->raiz) {
            this->raiz = this->raiz->balanceia();
        }
    }

    template <typename T, typename Compare> void arvore<T,Compare>::balanceia(bool otimo) {
        TRY_PROC(this->raiz) {
            this->raiz = this->raiz->balanceia(otimo);
        }
    }

    template <typename T,typename Compare> nodo_arvore<T,Compare>::~nodo_arvore() {
    }
    
template <typename T,typename Compare> nodo_arvore<T,Compare>::nodo_arvore(Compare &func) : BasicTree(),comp_func(func) {
}

template <typename T,typename Compare> nodo_arvore<T,Compare>::nodo_arvore(const T & dado, Compare &func) : data(dado),comp_func(func),BasicTree((void*)&data) {
}

//template <typename T,typename Compare> nodo_arvore<T,Compare>::nodo_arvore(const nodo_arvore<T,Compare> & outra) : BasicTree(outra) {}

template <typename T,typename Compare> BasicTree * nodo_arvore<T,Compare>::create(void * p_dado) {
    T * o = (T*)p_dado;
    nodo_arvore<T,Compare> * ptr = new nodo_arvore<T,Compare>(*o,this->comp_func);
    return (BasicTree*) ptr;
}

template <typename T,typename Compare> void nodo_arvore<T,Compare>::adiciona(const T & algo) {
    BasicTree::adiciona((void*)&algo);
}

template <typename T,typename Compare> const T& nodo_arvore<T,Compare>::obtem(const T & algo) const {
    T * o = (T*)BasicTree::obtem((void*)&algo);
    return *o;
}

template <typename T,typename Compare> const T& nodo_arvore<T,Compare>::obtem() const {
    return this->data;
}

template <typename T,typename Compare> const nodo_arvore<T,Compare> * nodo_arvore<T,Compare>::esquerda() const {
    return static_cast<const nodo_arvore<T,Compare>*>(this->esq);
}

template <typename T,typename Compare> const nodo_arvore<T,Compare> * nodo_arvore<T,Compare>::direita() const {
    return static_cast<const nodo_arvore<T,Compare>*>(this->dir);
}

template <typename T,typename Compare> void nodo_arvore<T,Compare>::listeEmLargura(list<T> & result) {
    list<void*> l;
    
    BasicTree::listeEmLargura(l);
    copia_lista(l , result);
}

template <typename T,typename Compare> void nodo_arvore<T,Compare>::listeInOrder(list<T> & result) {
    list<void*> l;
    
    BasicTree::listeInOrder(l);
    copia_lista(l , result);
}

template <typename T,typename Compare> void nodo_arvore<T,Compare>::copia_lista(list<void*> l, list<T> & res) {
    for (auto & x: l) {
        res.push_back(*(T*)x);
    }
}

template <typename T,typename Compare> void nodo_arvore<T,Compare>::listePreOrder(list<T> & result) {
    list<void*> l;
    
    BasicTree::listePreOrder(l);
    copia_lista(l , result);
}

template <typename T,typename Compare> void nodo_arvore<T,Compare>::listePostOrder(list<T> & result) {
    list<void*> l;
    
    BasicTree::listePostOrder(l);
    copia_lista(l , result);
}

template <typename T,typename Compare> unsigned int nodo_arvore<T,Compare>::tamanho() const {
    return BasicTree::tamanho();
}

template <typename T,typename Compare> int nodo_arvore<T,Compare>::fatorB()  {
    return BasicTree::fatorB();
}

template <typename T,typename Compare> unsigned int nodo_arvore<T,Compare>::altura()  {
    return BasicTree::altura();
}

template <typename T,typename Compare> nodo_arvore<T,Compare>* nodo_arvore<T,Compare>::balanceia() {
    nodo_arvore<T,Compare> * ptr = (nodo_arvore<T,Compare>*)BasicTree::balanceia();
    return ptr;
}

template <typename T,typename Compare> nodo_arvore<T,Compare>* nodo_arvore<T,Compare>::balanceia(bool otimo) {
    nodo_arvore<T,Compare> * ptr = (nodo_arvore<T,Compare>*)BasicTree::balanceia(otimo);
    return ptr;
}

//template <typename T,typename Compare> void nodo_arvore<T,Compare>::inicia() {
//    BasicTree::inicia();
//}
//
//template <typename T,typename Compare> T& nodo_arvore<T,Compare>::proximo() {
//    T * ptr = (T*)BasicTree::proximo();
//    return *ptr;
//}
//
//template <typename T,typename Compare> bool nodo_arvore<T,Compare>::fim() {
//    return BasicTree::fim();
//}

//template <typename T,typename Compare> void nodo_arvore<T,Compare>::iniciaPeloFim() {
//    BasicTree::rinicia();
//}
//
//template <typename T,typename Compare> T& nodo_arvore<T,Compare>::anterior() {
//    T * ptr = (T*)BasicTree::rproximo();
//    return *ptr;
//}
//
//template <typename T,typename Compare> bool nodo_arvore<T,Compare>::inicio() {
//    return BasicTree::rfim();
//}

template <typename T,typename Compare> T& nodo_arvore<T,Compare>::obtemMenor() const{
    T * ptr = (T*)BasicTree::obtemMenor();
    return *ptr;    
}

template <typename T,typename Compare> T nodo_arvore<T,Compare>::remove(const T & algo) {
//    if (not (esq or dir)) throw -1; // tem apenas raiz
    
    T coisa;
    BasicTree::remove((void*)&algo, (void*)&coisa);
    return coisa;    
}

template <typename T,typename Compare> T& nodo_arvore<T,Compare>::obtemMaior() const{
    T * ptr = (T*)BasicTree::obtemMaior();
    return *ptr;    
}

template <typename T,typename Compare> void nodo_arvore<T,Compare>::obtemMenoresQue(list<T> & result, const T & algo) {
    list<void*> l;
    BasicTree::obtemMenoresQue(l, (void*)&algo);
    copia_lista(l , result);
}

template <typename T,typename Compare> void nodo_arvore<T,Compare>::obtemMaioresQue(list<T> & result, const T & algo) {
    list<void*> l;
    BasicTree::obtemMaioresQue(l, (void*)&algo);
    copia_lista(l , result);
}

template <typename T,typename Compare> void nodo_arvore<T,Compare>::obtemIntervalo(list<T>& result, const T& start, const T& end) {
    list<void*> l;
    BasicTree::obtemIntervalo(l, (void*)&start, (void*)&end);
    copia_lista(l , result);
}

template <typename T,typename Compare> nodo_arvore<T,Compare> * nodo_arvore<T,Compare>::rotacionaL() {
    nodo_arvore<T,Compare> * ptr = (nodo_arvore<T,Compare>*)BasicTree::rotacionaL();
    return ptr;
}

template <typename T,typename Compare> nodo_arvore<T,Compare> * nodo_arvore<T,Compare>::rotacionaR() {
    nodo_arvore<T,Compare> * ptr = (nodo_arvore<T,Compare>*)BasicTree::rotacionaR();
    return ptr;
}

template <typename T,typename Compare> void nodo_arvore<T,Compare>::atribui(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    *o1 = *o2;
}
    // compararação de igualdade
template <typename T,typename Compare> bool nodo_arvore<T,Compare>::ehIgual(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    return comp_func(*o1,*o2) == 0;
}
    
    // comparação de precedência: *p1 < *p2
template <typename T,typename Compare> bool nodo_arvore<T,Compare>::ehMenor(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    return comp_func(*o1,*o2) < 0;
}
    // destroi dado
template <typename T,typename Compare> void nodo_arvore<T,Compare>::destroi(void * p1) {
    T * o1 = (T*)p1;
    delete o1;
}

    template <typename T,typename Compare> void desenha_nodos(const arvore_basica<T,Compare> & arv, ostream & out) {
        auto raiz = arv.obtem();
        auto esq = arv.esquerda();
        auto dir = arv.direita();

        if (esq.vazia() and dir.vazia()) out << raiz << endl;
        else {
            if (!esq.vazia()) {
                out << '"' << raiz << "\" -- \"" << esq.obtem() << '"' << endl;
                if (esq.altura()) desenha_nodos(esq, out);
            }
            if (!dir.vazia()) {
                out << '"' << raiz << "\" -- \"" << dir.obtem() << '"' << endl;
                if (dir.altura()) desenha_nodos(dir, out);
            }
        }

    }

    template <typename T, typename Compare> string desenha_arvore(const arvore_basica<T,Compare> & arv) {
        ostringstream out;

        out << "strict graph {" << endl;
        desenha_nodos(arv, out);
        out << "}" << endl;

        return out.str();
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::preorder_iterator arvore_basica<T,Compare>::preorder_begin() const{
        return preorder_iterator(this->raiz);
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::preorder_iterator arvore_basica<T,Compare>::preorder_end() const {
        return preorder_iterator();
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::inorder_iterator arvore_basica<T,Compare>::inorder_begin() const{
        return inorder_iterator(this->raiz);
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::inorder_iterator arvore_basica<T,Compare>::inorder_end() const {
        return inorder_iterator();
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::preorder_riterator arvore_basica<T,Compare>::preorder_rbegin() const {
        return preorder_riterator(this->raiz);
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::preorder_riterator arvore_basica<T,Compare>::preorder_rend() const {
        return preorder_riterator();
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::inorder_riterator arvore_basica<T,Compare>::inorder_rbegin() const{
        return inorder_riterator(this->raiz);
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::inorder_riterator arvore_basica<T,Compare>::inorder_rend() const {
        return inorder_riterator();
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_iterator::preorder_iterator() {

    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_iterator::preorder_iterator(const arvore_basica::preorder_iterator &it) {
        p = it.p;
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_iterator::preorder_iterator(const nodo_arvore<T,Compare> * raiz) {
        p.push(raiz);
    }

    template<typename T, typename Compare>
    bool arvore_basica<T,Compare>::preorder_iterator::operator==(const arvore_basica::preorder_iterator &it) const {
        return p == it.p;
    }

    template<typename T, typename Compare>
    bool arvore_basica<T,Compare>::preorder_iterator::operator!=(const arvore_basica::preorder_iterator &it) const {
        return p != it.p;
    }

    template<typename T, typename Compare>
    const T &arvore_basica<T,Compare>::preorder_iterator::operator*() const {
        if (p.empty()) throw std::runtime_error("fim da iteração"); // a meu critério ???
        auto ptr = p.top();
        return ptr->obtem();
    }

    template <typename T, typename Compare> const nodo_arvore<T,Compare>* arvore_basica<T,Compare>::preorder_iterator::operator->() const {
        if (p.empty()) throw std::runtime_error("fim da iteração");
        auto ptr = p.top();
        return ptr;
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::preorder_iterator &arvore_basica<T,Compare>::preorder_iterator::operator++() {
        if (! p.empty()) {
            auto ptr = p.top();
            p.pop();
            if (ptr->direita() != nullptr) p.push(ptr->direita());
            if (ptr->esquerda() != nullptr) p.push(ptr->esquerda());
        }
        return *this;
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::preorder_iterator &arvore_basica<T,Compare>::preorder_iterator::operator++(int) {
        return ++(*this);
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_riterator::preorder_riterator() {

    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_riterator::preorder_riterator(const arvore_basica::preorder_riterator &it):preorder_iterator(it) {
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_riterator::preorder_riterator(const nodo_arvore<T,Compare> * raiz): preorder_iterator(raiz) {
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::preorder_riterator &arvore_basica<T,Compare>::preorder_riterator::operator++() {
        auto & p = this->p;

        if (! p.empty()) {
            auto ptr = p.top();
            p.pop();
            if (ptr->esquerda() != nullptr) p.push(ptr->esquerda());
            if (ptr->direita() != nullptr) p.push(ptr->direita());
        }
        return *this;
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::preorder_riterator &arvore_basica<T,Compare>::preorder_riterator::operator++(int) {
        return ++(*this);
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_iterator::inorder_iterator(): arvore_basica<T,Compare>::preorder_iterator() {

    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_iterator::inorder_iterator(const arvore_basica::inorder_iterator &it): arvore_basica<T,Compare>::preorder_iterator(it) {
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_iterator::inorder_iterator(const nodo_arvore<T,Compare> * raiz) {
        for (auto ptr = raiz; ptr != nullptr; ptr=ptr->esquerda()) {
            this->p.push(ptr);
        }
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::inorder_iterator &arvore_basica<T,Compare>::inorder_iterator::operator++() {
        if (! this->p.empty()) {
            const nodo_arvore<T,Compare> * ptr = this->p.top();
            this->p.pop();
            for (ptr = ptr->direita(); ptr != nullptr; ptr=ptr->esquerda()) {
                this->p.push(ptr);
            }
        }
        return *this;
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::inorder_iterator &arvore_basica<T,Compare>::inorder_iterator::operator++(int) {
        return ++(*this);
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_riterator::inorder_riterator(): arvore_basica<T,Compare>::preorder_iterator() {

    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_riterator::inorder_riterator(const arvore_basica::inorder_riterator &it): arvore_basica<T,Compare>::preorder_iterator(it) {
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_riterator::inorder_riterator(const nodo_arvore<T,Compare> * raiz) {
        for (auto ptr = raiz; ptr != nullptr; ptr=ptr->direita()) {
            this->p.push(ptr);
        }
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::inorder_riterator &arvore_basica<T,Compare>::inorder_riterator::operator++() {
        if (! this->p.empty()) {
            auto ptr = this->p.top();
            this->p.pop();
            for (ptr = ptr->esquerda(); ptr != nullptr; ptr=ptr->direita()) {
                this->p.push(ptr);
            }
        }
        return *this;
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::inorder_riterator &arvore_basica<T,Compare>::inorder_riterator::operator++(int) {
        return ++(*this);
    }

};

#endif	/* ARVORE_IMPL_H */

