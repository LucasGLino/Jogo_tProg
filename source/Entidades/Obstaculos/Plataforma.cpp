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

		// anula a gravidade para -0.1f
		pos.y -= velocidade.y + (velocidade.y / 60);
	}
	else{
		// limita a gravidade a 0.1f
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