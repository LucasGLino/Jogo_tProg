#include "Entidades/Obstaculos/Plataforma.h"

#include <cstdlib>

using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;

// Comeca com os dados usados na flutuacao da plataforma.
Plataforma::Plataforma()
{
	subindo = (rand() % 2);
	flutuabilidade = 4.0f;
	densidade_superficial = 1.f;
}

// Nao precisa liberar nada alem do que a classe base ja cuida.
Plataforma::~Plataforma()
{
}

// Salva o ponto central da oscilacao.
void Plataforma::seta_Origem(float origem_x, float origem_y)
{
	origem.x = origem_x;
	origem.y = origem_y;
}

// Move a plataforma levemente para cima e para baixo.
void Plataforma::flutuar()
{
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
}

// Atualiza a posicao flutuante e desenha a plataforma.
void Plataforma::executar()
{
	executar_Gravidade();
	flutuar();
	setar_Pos(pos.x, pos.y);
	desenhar();
}

// Ajusta o estado de pulo do jogador conforme o lado da colisao.
void Plataforma::obstacular(Jogador* p, int lado)
{
	if(lado == cima){
		p->setar_Bateu_A_Cabeca();
	}
	if(lado == baixo){
		p->setar_Pode_Pular();
	}
}

// Salvar ainda nao foi implementado para plataforma.
void Plataforma::salvar()
{
}
