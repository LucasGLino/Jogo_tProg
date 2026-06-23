#include "Entidades/Obstaculos/Caixa.h"

using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;

// Comeca parada e pronta para receber empurrao.
Caixa::Caixa(): sendo_empurrada(false), empurrao_para_esquerda(false), distancia_percorrida(0.f)
{
	densidade_superficial = 0.02f;
	velocidade.x = 1.f;
	velocidade.y = 1.f;
	relogio_empurrao.restart();
}

// Nao precisa liberar nada alem do que a classe base ja cuida.
Caixa::~Caixa()
{
}

// Desenha, aplica gravidade e executa empurrao se estiver ativo.
void Caixa::executar()
{
	desenhar();
	executar_Gravidade();

	if(sendo_empurrada){
		executar_Empurrao();
	}

	setar_Pos(pos.x, pos.y);
}

// Usa a configuracao padrao de obstaculo para montar a caixa.
void Caixa::seta_Caixa(float origem_x, float origem_y)
{
	seta_Obstaculo(64.f, 64.f, origem_x, origem_y, "Assets/Imagens/Caixa.png");
}

// So empurra quando o jogador bate dos lados.
void Caixa::obstacular(Jogador* p, int lado)
{
	if(lado == esquerda || lado == direita){
		iniciar_Empurrao(lado);
	}
}

// Comeca o empurrao se a recarga ja passou.
void Caixa::iniciar_Empurrao(int lado)
{
	const float tempo_recarga = 0.35f;

	if(!sendo_empurrada && relogio_empurrao.getElapsedTime().asSeconds() >= tempo_recarga){
		sendo_empurrada = true;
		empurrao_para_esquerda = (lado == esquerda);
		distancia_percorrida = 0.f;
	}
}

// Move a caixa ate atingir a distancia maxima.
void Caixa::executar_Empurrao()
{
	const float distancia_maxima = 24.f;
	const float velocidade_empurrao = 1.5f;

	if(empurrao_para_esquerda){
		pos.x -= velocidade_empurrao;
	}
	else{
		pos.x += velocidade_empurrao;
	}

	distancia_percorrida += velocidade_empurrao;

	if(distancia_percorrida >= distancia_maxima){
		parar_Empurrao();
	}
}

// Encerra o empurrao e reinicia a recarga.
void Caixa::parar_Empurrao()
{
	sendo_empurrada = false;
	distancia_percorrida = 0.f;
	relogio_empurrao.restart();
}

// Salvar ainda nao foi implementado para caixa.
void Caixa::salvar()
{
}
