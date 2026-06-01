#pragma once
#include"Lista.h"
#include"../Entidades/Entidade.h"
using namespace std;

namespace Listas {
	class ListaEnt {
	private:
		Lista<Entidades::Entidade> pLista;
	public:
		ListaEnt() {};
		~ListaEnt() {
			limpar();
		}
		void limpar() {
			pLista.clear();
		}
		void add(Entidades::Entidade* pEntidade);
		
		void remove(Entidades::Entidade* pEntidade);

		void remove(int i);

		Entidades::Entidade* getPrimeiro(){ return (pLista.size() > 0) ? pLista[0] : nullptr;;}

		Entidades::Entidade* operator[](int i);

		int size() const {
			return pLista.size();
		};

		Lista<Entidades::Entidade>::Iterator* CreateIterator() {
            return pLista.CreateIterator(); 
		};

		void push_back(Entidades::Entidade* pEntidade) {
			add(pEntidade);
		};

	};
}