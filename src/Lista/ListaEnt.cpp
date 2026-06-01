#include "../../include/Lista/ListaEnt.h"

void Listas::ListaEnt::add(Entidades::Entidade* pEntidade)
{
	if (pEntidade) {
		pLista.push(pEntidade);
	}
	else {
		cout << "Ponteiro Nulo/add" << endl;
	}
}

void Listas::ListaEnt::remove(Entidades::Entidade* pEntidade)
{
	if (pEntidade) {
		Entidades::Entidade* aux = pLista.pop(pEntidade);
		if(aux != nullptr){
			delete(aux);
		}
		
	}
	else {
		cout << "Ponteiro Nulo/remove" << endl;
	}
}

void Listas::ListaEnt::remove(int i)
{
	if (i >= 0 && i < pLista.size()) {
		Entidades::Entidade* aux = pLista.pop(i);
		if(aux != nullptr){
			delete(aux);
		}
	}
	else {
		cout << "Indice Invalido" << endl;
	}
}

Entidades::Entidade* Listas::ListaEnt::operator[](int i)
{
	if (i >= 0 && i < pLista.size()) {
		return pLista[i];
	}
	else {
		cout << "Indice Invalido" << endl;
		return nullptr;
	}
}
