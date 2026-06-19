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

void Entidades::Obstaculos::Obstaculo::seta_Obstaculo(float alt, float larg, float origem_x, float origem_y, std::string assets)
{
	tamanho.x = larg;
	tamanho.y = alt;

	//pFigura->setFillColor(sf::Color::Green);
	pFigura->setSize(tamanho);
	if (!textura.loadFromFile(assets)) {
		std::cout << "Erro ao carregar textura da plataforma." << std::endl;
		pFigura->setFillColor(sf::Color::Green);
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
	this->setar_Pos(origem_x, origem_y);
}

void Obstaculo::salvar(){
	Salvar();
}

void Obstaculo::executar(){
	Executar();
}

const int Obstaculo::id_base(1000);

