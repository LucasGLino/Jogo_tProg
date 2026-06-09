#include "Entidades/Obstaculos/Obstaculo.h"

using namespace Entidades;
using namespace Personagens;
using namespace Obstaculos;

/*
Obstaculo::Obstaculo() : Entidade(id_base)
*/
Obstaculo::Obstaculo() : Entidade(id_base, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f))
{
	//agressivo = false;
	danoso = false;
	//setId(semente_id_entidade);

	tamanho.x = 0.f;
	tamanho.y = 0.f;
	
}

Obstaculo::~Obstaculo() {

}

//n�o sei como executar a gravidade aplicada ao obstaculo.
void Obstaculo::executar_Gravidade(){
	pos.y += gravidade;
	pos.y -= gravidade;
}

void Obstaculo::salvar(){
	Salvar();
}

void Obstaculo::executar(){
	Executar();
}

const int Obstaculo::id_base(1000);

