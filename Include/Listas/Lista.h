#pragma once
#include<iostream>

//using namespace std;

namespace Listas {
    template <class TL>
    class Lista {
    private:
        template <class TE>
        class Elemento {
        private:
            Elemento<TE>* pProx;
            Elemento<TE>* pAnt;
            //TE* pInfo;
            TE* pInformacao;

        public:
            //Elemento() : pProx(nullptr), pAnt(nullptr), pInfo(nullptr) {}
            Elemento() : pProx(nullptr), pAnt(nullptr), pInformacao(nullptr) {}
            ~Elemento() {
                pProx = nullptr;
                pAnt = nullptr;
                //pInfo = nullptr;
                pInformacao = nullptr;
            }

            void incluir(TE* p) {
                //this->pInfo = p;
                this->pInformacao = p;
            }

            void setProximo(Elemento<TE>* pE) {
                this->pProx = pE;
            }

            void setAnterior(Elemento<TE>* pE) {
                this->pAnt = pE;
            }

            Elemento<TE>* getProximo() const {
                return pProx;
            }
            
            Elemento<TE>* getAnterior() const {
                return pAnt;
            }

            //TE* getInfo() const { 
            TE* getInformacao() const { 
                //return pInfo; 
                return pInformacao; 
            }
        };
        
        Elemento<TL>* pPrimeiro;

        Elemento<TL>* pUltimo;

        int tamanho;

    public:
        //class Iterator {
        class Iterador {
        private:
            //Elemento<TL>* index;
            Elemento<TL>* indice;
            Elemento<TL>* pPrimeiroLista;

            
        public:
            //Iterator(Elemento<TL>* first) : index(first){}
            Iterador(Elemento<TL>* primeiro) : indice(primeiro), pPrimeiroLista(primeiro){}

            //void first() {
            void primeiro() {
                indice = pPrimeiroLista;
            }
            
            //void next() {
            void proximo() {
                if(indice) {
                    indice = indice->getProximo();
                }
            }

            //bool isDone() {
            bool terminou() {
                return (indice == nullptr);
            }

            //TL* current() {
            TL* atual() {
                //return indice ? indice->getInfo() : nullptr;
                return indice ? indice->getInformacao() : nullptr;
            }
        };

        Lista();

        ~Lista();

        //void clear();
        void limpar();

        TL* operator[](int i);

        //void push(TL* pInfo);
        void adicionar(TL* pInformacao);

        //Iterator* CreateIterator();
        Iterador* criarIterador();

        //TL* pop(TL* pInfo);
        TL* remover(TL* pInformacao);

        //TL* pop(int i);
        TL* remover(int i);

        //int size() const;
        int getTamanho() const;

        //TL* begin();
        TL* getInicio();
    };

    template<class TL>
    Lista<TL>::Lista() : pPrimeiro(nullptr), pUltimo(nullptr), tamanho(0) {}

    template<class TL>
    Lista<TL>::~Lista() {
        limpar();
    }

    template<class TL>
    //void Lista<TL>::clear() {
    void Lista<TL>::limpar() {
        //Elemento<TL>* current = pPrimeiro;
        Elemento<TL>* atual = pPrimeiro;
        while (atual != nullptr) {
            //Elemento<TL>* next = current->getProximo();
            Elemento<TL>* proximo = atual->getProximo();
            //delete current->getInfo();
            //delete atual->getInfo();
            delete atual->getInformacao();
            //delete current;
            delete atual;
            //current = next;
            atual = proximo;
        }
        pPrimeiro = nullptr;
        pUltimo = nullptr;
        tamanho = 0;
    }

    template<class TL>
    //TL* Lista<TL>::operator[](int index) {
    TL* Lista<TL>::operator[](int indice) {
        //if (index < 0 || index >= tamanho) {
        if (indice < 0 || indice >= tamanho) {
            return nullptr;
        }

        //Elemento<TL>* current = pPrimeiro;
        Elemento<TL>* atual = pPrimeiro;
        //for (int i = 0; i < index && atual != nullptr; i++) {
        for (int i = 0; i < indice && atual != nullptr; i++) {
            //current = current->getProximo();
            atual = atual->getProximo();
        }
        //return current ? current->getInfo() : nullptr;
        return atual ? atual->getInformacao() : nullptr;
    }

    template<class TL>
    //void Lista<TL>::push(TL* pInfo) {
    void Lista<TL>::adicionar(TL* pInformacao) {
        //if (pInfo == nullptr) {
        if (pInformacao == nullptr) {
            std::cout << "Ponteiro Nulo/lista" << std::endl;
            return;
        }

        Elemento<TL>* pNo = new Elemento<TL>();
        //pNo->incluir(pInfo);
        pNo->incluir(pInformacao);

        if (pPrimeiro == nullptr) {

            pPrimeiro = pNo;

            pUltimo = pNo;
        } else {
            pNo->setAnterior(pUltimo); 

            pUltimo->setProximo(pNo); 

            pUltimo = pNo;                
        }
        tamanho++;
    }

    template<class TL>
    //typename Lista<TL>::Iterator* Lista<TL>::CreateIterator() {
    typename Lista<TL>::Iterador* Lista<TL>::criarIterador() {
        //return new Iterator(pPrimeiro);
        return new Iterador(pPrimeiro);
    }

    template<class TL>
    //TL* Lista<TL>::pop(TL* pInfo) {
    TL* Lista<TL>::remover(TL* pInformacao) {
        //Elemento<TL>* current = pPrimeiro;
        Elemento<TL>* atual = pPrimeiro;
        //Elemento<TL>* prev = nullptr;
        Elemento<TL>* anterior = nullptr;
        
        while (atual != nullptr) {
            //if (atual->getInfo() == pInfo) {
            if (atual->getInformacao() == pInformacao) {
                
                if (atual == pPrimeiro) {

                    pPrimeiro = atual->getProximo();

                    if (pPrimeiro) pPrimeiro->setAnterior(nullptr);
                    else pUltimo = nullptr;

                } else if (atual == pUltimo) {

                    pUltimo = anterior;

                    if (pUltimo) pUltimo->setProximo(nullptr);

                } else {
                    anterior->setProximo(atual->getProximo());

                    atual->getProximo()->setAnterior(anterior);
                }
                
                //TL* info = atual->getInfo();
                TL* informacao = atual->getInformacao();
                delete atual;
                tamanho--;
                //return info;
                return informacao;
            }
            anterior = atual;
            atual = atual->getProximo();
        }
        return nullptr;
    }

    template<class TL>
    //TL* Lista<TL>::pop(int index) {
    TL* Lista<TL>::remover(int indice) {
        //if (index < 0 || index >= tamanho) {
        if (indice < 0 || indice >= tamanho) {
            return nullptr;
        }

        //Elemento<TL>* current = pPrimeiro;
        Elemento<TL>* atual = pPrimeiro;
        
        //Elemento<TL>* prev = nullptr;
        Elemento<TL>* anterior = nullptr;

        //for (int i = 0; i < index; i++) {
        for (int i = 0; i < indice; i++) {
            anterior = atual;
            atual = atual->getProximo();
        }

        if (atual == pPrimeiro) {

            pPrimeiro = atual->getProximo();

            if (pPrimeiro) pPrimeiro->setAnterior(nullptr);
            else pUltimo = nullptr;

        } else if (atual == pUltimo) {

            pUltimo = anterior;

            if (pUltimo) pUltimo->setProximo(nullptr);

        } else {
            anterior->setProximo(atual->getProximo());

            atual->getProximo()->setAnterior(anterior);
        }

        //TL* info = atual->getInfo();
        TL* informacao = atual->getInformacao();

        delete atual;
        
        tamanho--;

        //return info;
        return informacao;
    }

    template<class TL>
    //int Lista<TL>::size() const {
    int Lista<TL>::getTamanho() const {
        return tamanho;
    }

    template<class TL>
    //TL* Lista<TL>::begin() { 
    TL* Lista<TL>::getInicio() { 
        //return pPrimeiro ? pPrimeiro->getInfo() : nullptr; 
        return pPrimeiro ? pPrimeiro->getInformacao() : nullptr; 
    }
}
