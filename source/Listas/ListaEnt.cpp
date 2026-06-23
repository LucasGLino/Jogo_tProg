#include "Listas/ListaEnt.h"

using namespace Listas;
using namespace Entidades;

// Adiciona entidade se o ponteiro for valido.
void ListaEnt::adicionar(Entidade* pEntidade)
{
	if (pEntidade) {
		listaEntidades.incluir(pEntidade);
	}
	else {
		std::cout << "Ponteiro Nulo/adicionar" << std::endl;
	}
}

// Remove a entidade da lista e deleta o objeto removido.
void ListaEnt::remover(Entidade* pEntidade)
{
	if (pEntidade) {
		Entidade* auxiliar = listaEntidades.remover(pEntidade);
		if(auxiliar != nullptr){
			delete(auxiliar);
		}
		
	}
	else {
		std::cout << "Ponteiro Nulo/remover" << std::endl;
	}
}

// Remove a entidade pelo indice e deleta o objeto removido.
void ListaEnt::remover(int i)
{
	if (i >= 0 && i < listaEntidades.getTamanho()) {
		Entidade* auxiliar = listaEntidades.remover(i);
		if(auxiliar != nullptr){
			delete(auxiliar);
		}
	}
	else {
		std::cout << "Indice Invalido" << std::endl;
	}
}

// Acessa uma entidade pelo indice sem remover.
Entidade* ListaEnt::operator[](int i)
{
	if (i >= 0 && i < listaEntidades.getTamanho()) {
		return listaEntidades[i];
	}
	else {
		std::cout << "Indice Invalido" << std::endl;
		return nullptr;
	}
}

// Percorre a lista ate encontrar a entidade com o id informado.
Entidade* ListaEnt::get_Entidade_Por_Id(int id)
{
	Lista<Entidade>::Iterador* iterador = criarIterador();
	Entidade* pEntidade_Encontrada = nullptr;

	for (iterador->primeiro(); !iterador->terminou(); iterador->proximo()) {
		Entidade* pEntidade = iterador->atual();

		if (pEntidade != nullptr && pEntidade->getId() == id) {
			pEntidade_Encontrada = pEntidade;
			break;
		}
	}

	delete iterador;
	return pEntidade_Encontrada;
}

// Chama executar em todas as entidades registradas.
void ListaEnt::percorrer()
{
	Lista<Entidade>::Iterador* iterador = criarIterador();

	for (iterador->primeiro(); !iterador->terminou(); iterador->proximo()) {
		Entidade* pEntidade = iterador->atual();

		if (pEntidade != nullptr) {
			pEntidade->executar();
		}
	}

	delete iterador;
}
