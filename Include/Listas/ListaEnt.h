#pragma once
#include"Lista.h"
#include"../Entidades/Entidade.h"
//using namespace std;

namespace Listas {
	class ListaEnt {
	private:
		Lista<Entidades::Entidade> listaEntidades;
	public:
		ListaEnt() {};
		~ListaEnt() {
			limpar();
		}
		void limpar() {
			//pLista.clear();
			listaEntidades.limpar();
		}
		//void add(Entidades::Entidade* pEntidade);
		void adicionar(Entidades::Entidade* pEntidade);
		
		//void remove(Entidades::Entidade* pEntidade);
		void remover(Entidades::Entidade* pEntidade);

		//void remove(int i);
		void remover(int i);

		Entidades::Entidade* getPrimeiro(){ return (listaEntidades.getTamanho() > 0) ? listaEntidades[0] : nullptr;;}

		Entidades::Entidade* operator[](int i);

		Entidades::Entidade* get_Entidade_Por_Id(int id);

		//int size() const {
		int getTamanho() const {
			//return pLista.size();
			return listaEntidades.getTamanho();
		};

		//Lista<Entidades::Entidade>::Iterator* CreateIterator() {
		Lista<Entidades::Entidade>::Iterador* criarIterador() {
            //return pLista.CreateIterator(); 
            return listaEntidades.criarIterador(); 
		};

		//void push_back(Entidades::Entidade* pEntidade) {
		void adicionarFinal(Entidades::Entidade* pEntidade) {
			//add(pEntidade);
			adicionar(pEntidade);
		};

		void percorrer();

	};
}
