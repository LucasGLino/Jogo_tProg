#include "Entidades/Obstaculos/Plataforma.h"

using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;

//const int massa_plataforma(10000);

Plataforma::Plataforma()
{
	chao = false;
	ativa = true;

	subindo = (rand() % 2);

	flutuabilidade = 4.0f;

	tamanho.x = 0;
	tamanho.y = 0;

	densidade_superficial = 1.f;
}

Plataforma::~Plataforma(){

}

// void Plataforma::seta_Plataforma(float alt, float larg, float origem_x, float origem_y)
// {

// 	tamanho.x = larg;
// 	tamanho.y = alt;

// 	//pFigura->setFillColor(sf::Color::Green);
// 	pFigura->setSize(tamanho);
// 	if (!textura.loadFromFile("assets/Plataforma.png")) {
// 		std::cout << "Erro ao carregar textura da plataforma." << std::endl;
// 		pFigura->setFillColor(sf::Color::Green);
// 	}
// 	else {
// 		pFigura->setFillColor(sf::Color::White);
// 		pFigura->setTexture(&textura);
// 	}
// 	this->setar_Pos(origem_x, origem_y);
// }

void Plataforma::seta_Origem(float origem_x, float origem_y){

	origem.x = origem_x;
	origem.y = origem_y;
}

void Plataforma::flutuar(){

	if(pos.y <= (origem.y - flutuabilidade)){
		subindo = false;
	}
	else if(pos.y > (origem.y + flutuabilidade)){
		subindo = true;
	}

	if(subindo){

		pos.y -= velocidade.y + (velocidade.y / 60);
	}
	else{
		
		pos.y -= velocidade.y - (velocidade.y / 60);
	}

	//pos.y -=velocidade.y;
}

void Plataforma::determinar_chao() {
	chao = true;
}

void Plataforma::executar() {

	if(ativa){

		if(!chao){

			executar_Gravidade();
			flutuar();
			setar_Pos(pos.x,pos.y);
		}

		desenhar();
	}
	
}

void Plataforma::obstacular(Jogador* p, int lado) {

	if(lado == cima){
		p->setar_Bateu_A_Cabeca();

	}
	if(lado == baixo){
		
		p->setar_Pode_Pular();
	}
	
}

void Plataforma::salvar(){

}