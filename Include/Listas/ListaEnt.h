#pragma once
#include "Listas/Lista.h"
#include "Entidades/Entidade.h"

namespace Listas {
	class ListaEnt {
	private:
		// Lista que guarda e controla o ciclo de vida das entidades.
		Lista<Entidades::Entidade> listaEntidades;

	public:
		ListaEnt() {};
		~ListaEnt() {
			limpar();
		}

		// Remove todas as entidades da lista.
		void limpar() {
			listaEntidades.limpar();
		}

		// Adiciona uma entidade na lista principal.
		void adicionar(Entidades::Entidade* pEntidade);

		// Remove e deleta a entidade recebida.
		void remover(Entidades::Entidade* pEntidade);

		// Remove e deleta a entidade pelo indice.
		void remover(int i);

		// Retorna a primeira entidade da lista.
		Entidades::Entidade* getPrimeiro(){ return (listaEntidades.getTamanho() > 0) ? listaEntidades[0] : nullptr; }

		Entidades::Entidade* operator[](int i);

		// Busca uma entidade pelo id.
		Entidades::Entidade* get_Entidade_Por_Id(int id);

		// Retorna a quantidade atual de entidades.
		int getTamanho() const {
			return listaEntidades.getTamanho();
		};

		// Cria um iterador para percorrer as entidades.
		Lista<Entidades::Entidade>::Iterador* criarIterador() {
            return listaEntidades.criarIterador(); 
		};

		// Mantem uma opcao explicita para adicionar ao final.
		void adicionarFinal(Entidades::Entidade* pEntidade) {
			adicionar(pEntidade);
		};

		// Executa todas as entidades da lista.
		void percorrer();

	};
}
