#pragma once
#include<iostream>

using namespace std;

namespace Listas {
    template <class TL>
    class Lista {
    private:
        template <class TE>
        class Elemento {
        private:
            Elemento<TE>* pProx;
            Elemento<TE>* pAnt;
            TE* pInfo;

        public:
            Elemento() : pProx(nullptr), pAnt(nullptr), pInfo(nullptr) {}
            ~Elemento() {
                pProx = nullptr;
                pAnt = nullptr;
                pInfo = nullptr;
            }

            void incluir(TE* p) {
                this->pInfo = p;
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

            TE* getInfo() const { 
                return pInfo; 
            }
        };
        
        Elemento<TL>* pPrimeiro;

        Elemento<TL>* pUltimo;

        int tamanho;

    public:
        class Iterator {
        private:
            Elemento<TL>* index;

            
        public:
            Iterator(Elemento<TL>* first) : index(first){}

            void first() {
                index = pPrimeiro;
            }
            
            void next() {
                if(index) {
                    index = index->getProximo();
                }
            }

            bool isDone() {
                return (index == nullptr);
            }

            TL* current() {
                return index ? index->getInfo() : nullptr;
            }
        };

        Lista();

        ~Lista();

        void clear();

        TL* operator[](int i);

        void push(TL* pInfo);

        Iterator* CreateIterator();

        TL* pop(TL* pInfo);

        TL* pop(int i);

        int size() const;

        TL* begin();
    };

    template<class TL>
    Lista<TL>::Lista() : pPrimeiro(nullptr), pUltimo(nullptr), tamanho(0) {}

    template<class TL>
    Lista<TL>::~Lista() {
        clear();
    }

    template<class TL>
    void Lista<TL>::clear() {
        Elemento<TL>* current = pPrimeiro;
        while (current != nullptr) {
            Elemento<TL>* next = current->getProximo();
            delete current->getInfo();
            delete current;
            current = next;
        }
        pPrimeiro = nullptr;
        pUltimo = nullptr;
        tamanho = 0;
    }

    template<class TL>
    TL* Lista<TL>::operator[](int index) {
        if (index < 0 || index >= tamanho) {
            return nullptr;
        }

        Elemento<TL>* current = pPrimeiro;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->getProximo();
        }
        return current ? current->getInfo() : nullptr;
    }

    template<class TL>
    void Lista<TL>::push(TL* pInfo) {
        if (pInfo == nullptr) {
            cout << "Ponteiro Nulo/lista" << endl;
            return;
        }

        Elemento<TL>* pNo = new Elemento<TL>();
        pNo->incluir(pInfo);

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
    typename Lista<TL>::Iterator* Lista<TL>::CreateIterator() {
        return new Iterator(pPrimeiro);
    }

    template<class TL>
    TL* Lista<TL>::pop(TL* pInfo) {
        Elemento<TL>* current = pPrimeiro;
        Elemento<TL>* prev = nullptr;
        
        while (current != nullptr) {
            if (current->getInfo() == pInfo) {
                
                if (current == pPrimeiro) {

                    pPrimeiro = current->getProximo();

                    if (pPrimeiro) pPrimeiro->setAnterior(nullptr);

                } else if (current == pUltimo) {

                    pUltimo = prev;

                    if (pUltimo) pUltimo->setProximo(nullptr);

                } else {
                    prev->setProximo(current->getProximo());

                    current->getProximo()->setAnterior(prev);
                }
                
                TL* info = current->getInfo();
                delete current;
                tamanho--;
                return info;
            }
            prev = current;
            current = current->getProximo();
        }
        return nullptr;
    }

    template<class TL>
    TL* Lista<TL>::pop(int index) {
        if (index < 0 || index >= tamanho) {
            return nullptr;
        }

        Elemento<TL>* current = pPrimeiro;
        
        Elemento<TL>* prev = nullptr;

        for (int i = 0; i < index; i++) {
            prev = current;
            current = current->getProximo();
        }

        if (current == pPrimeiro) {

            pPrimeiro = current->getProximo();

            if (pPrimeiro) pPrimeiro->setAnterior(nullptr);

        } else if (current == pUltimo) {

            pUltimo = prev;

            if (pUltimo) pUltimo->setProximo(nullptr);

        } else {
            prev->setProximo(current->getProximo());

            current->getProximo()->setAnterior(prev);
        }

        TL* info = current->getInfo();

        delete current;
        
        tamanho--;

        return info;
    }

    template<class TL>
    int Lista<TL>::size() const {
        return tamanho;
    }

    template<class TL>
    TL* Lista<TL>::begin() { 
        return pPrimeiro ? pPrimeiro->getInfo() : nullptr; 
    }
}