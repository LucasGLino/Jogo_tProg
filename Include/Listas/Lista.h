#pragma once
#include <iostream>

namespace Listas {
    template <class TL>
    class Lista {
    private:
        // No interno da lista duplamente encadeada.
        template <class TE>
        class Elemento {
        private:
            Elemento<TE>* pProx;
            Elemento<TE>* pAnt;
            TE* pInformacao;

        public:
            Elemento() : pProx(nullptr), pAnt(nullptr), pInformacao(nullptr) {}
            ~Elemento() {
                pProx = nullptr;
                pAnt = nullptr;
                pInformacao = nullptr;
            }

            void incluir(TE* p) {
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

            TE* getInformacao() const { 
                return pInformacao; 
            }
        };
        
        Elemento<TL>* pPrimeiro;

        Elemento<TL>* pUltimo;

        int tamanho;

    public:
        // Iterador simples para percorrer a lista sem expor os nos internos.
        class Iterador {
        private:
            Elemento<TL>* indice;
            Elemento<TL>* pPrimeiroLista;

            
        public:
            Iterador(Elemento<TL>* primeiro) : indice(primeiro), pPrimeiroLista(primeiro){}

            void primeiro() {
                indice = pPrimeiroLista;
            }
            
            void proximo() {
                if(indice) {
                    indice = indice->getProximo();
                }
            }

            bool terminou() {
                return (indice == nullptr);
            }

            TL* atual() {
                return indice ? indice->getInformacao() : nullptr;
            }
        };

        Lista();

        ~Lista();

        void limpar();

        TL* operator[](int i);

        void incluir(TL* pInformacao);

        Iterador* criarIterador();

        TL* remover(TL* pInformacao);

        TL* remover(int i);

        int getTamanho() const;

        TL* getInicio();
    };

    template<class TL>
    Lista<TL>::Lista() : pPrimeiro(nullptr), pUltimo(nullptr), tamanho(0) {}

    template<class TL>
    Lista<TL>::~Lista() {
        limpar();
    }

    // Remove todos os nos e tambem deleta os objetos guardados.
    template<class TL>
    void Lista<TL>::limpar() {
        Elemento<TL>* atual = pPrimeiro;
        while (atual != nullptr) {
            Elemento<TL>* proximo = atual->getProximo();
            delete atual->getInformacao();
            delete atual;
            atual = proximo;
        }
        pPrimeiro = nullptr;
        pUltimo = nullptr;
        tamanho = 0;
    }

    // Retorna o item na posicao informada, sem remover da lista.
    template<class TL>
    TL* Lista<TL>::operator[](int indice) {
        if (indice < 0 || indice >= tamanho) {
            return nullptr;
        }

        Elemento<TL>* atual = pPrimeiro;
        for (int i = 0; i < indice && atual != nullptr; i++) {
            atual = atual->getProximo();
        }
        return atual ? atual->getInformacao() : nullptr;
    }

    // Insere um ponteiro no fim da lista.
    template<class TL>
    void Lista<TL>::incluir(TL* pInformacao) {
        if (pInformacao == nullptr) {
            std::cout << "Ponteiro Nulo/lista" << std::endl;
            return;
        }

        Elemento<TL>* pNo = new Elemento<TL>();
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

    // Cria um iterador apontando para o inicio da lista.
    template<class TL>
    typename Lista<TL>::Iterador* Lista<TL>::criarIterador() {
        return new Iterador(pPrimeiro);
    }

    // Remove um item pelo ponteiro e devolve esse ponteiro sem deleta-lo.
    template<class TL>
    TL* Lista<TL>::remover(TL* pInformacao) {
        Elemento<TL>* atual = pPrimeiro;
        Elemento<TL>* anterior = nullptr;
        
        while (atual != nullptr) {
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
                
                TL* informacao = atual->getInformacao();
                delete atual;
                tamanho--;
                return informacao;
            }
            anterior = atual;
            atual = atual->getProximo();
        }
        return nullptr;
    }

    // Remove um item pelo indice e devolve esse ponteiro sem deleta-lo.
    template<class TL>
    TL* Lista<TL>::remover(int indice) {
        if (indice < 0 || indice >= tamanho) {
            return nullptr;
        }

        Elemento<TL>* atual = pPrimeiro;
        
        Elemento<TL>* anterior = nullptr;

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

        TL* informacao = atual->getInformacao();

        delete atual;
        
        tamanho--;

        return informacao;
    }

    template<class TL>
    int Lista<TL>::getTamanho() const {
        return tamanho;
    }

    template<class TL>
    TL* Lista<TL>::getInicio() { 
        return pPrimeiro ? pPrimeiro->getInformacao() : nullptr; 
    }
}
