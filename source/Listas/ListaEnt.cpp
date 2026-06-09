#include "Listas/ListaEnt.h"

using namespace std;
using namespace Listas;
using namespace Entidades;

//void Listas::ListaEnt::add(Entidades::Entidade* pEntidade)
void ListaEnt::adicionar(Entidade* pEntidade)
{
	if (pEntidade) {
		//pLista.push(pEntidade);
		listaEntidades.adicionar(pEntidade);
	}
	else {
		cout << "Ponteiro Nulo/adicionar" << endl;
	}
}

//void Listas::ListaEnt::remove(Entidades::Entidade* pEntidade)
void ListaEnt::remover(Entidade* pEntidade)
{
	if (pEntidade) {
		//Entidades::Entidade* aux = pLista.pop(pEntidade);
		Entidade* auxiliar = listaEntidades.remover(pEntidade);
		if(auxiliar != nullptr){
			delete(auxiliar);
		}
		
	}
	else {
		cout << "Ponteiro Nulo/remover" << endl;
	}
}

//void Listas::ListaEnt::remove(int i)
void ListaEnt::remover(int i)
{
	//if (i >= 0 && i < pLista.size()) {
	if (i >= 0 && i < listaEntidades.getTamanho()) {
		//Entidades::Entidade* aux = pLista.pop(i);
		Entidade* auxiliar = listaEntidades.remover(i);
		if(auxiliar != nullptr){
			delete(auxiliar);
		}
	}
	else {
		cout << "Indice Invalido" << endl;
	}
}

Entidade* ListaEnt::operator[](int i)
{
	//if (i >= 0 && i < pLista.size()) {
	if (i >= 0 && i < listaEntidades.getTamanho()) {
		return listaEntidades[i];
	}
	else {
		cout << "Indice Invalido" << endl;
		return nullptr;
	}
}

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
