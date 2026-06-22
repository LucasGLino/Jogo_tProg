#include "Entidades/Personagens/Inimigos/Inimigo.h"

using namespace Entidades;
using namespace Personagens;


/*
Inimigo::Inimigo() : Personagem(id_base), direcao(0){
*/
Inimigo::Inimigo() : Personagem(id_base, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), 1, 0.f, 0.f), direcao(0){


	ponteiro_jogador1 = nullptr;
	ponteiro_jogador2 = nullptr;

	parar = true;

	pontos_de_eliminacao = 0;

	lado_fraco = cima;

	nivel_maldade = -1;
	//dano = -1;

	pos_inicial.x = 0;
	pos_inicial.y = 0;

	pos_final.x = 0;
	pos_final.y = 0;
}

Inimigo::~Inimigo() {
	
}

void Inimigo::andar_ate(float em_x, float em_y){

	if (em_x > pos.x) 
	{
		direcao = direita;
	}
	else{
		direcao = esquerda;
	}

	pos_final.x = em_x;
	pos_final.y = em_y;
}

/*
void Inimigo::Executar() {

	
}

void Inimigo::salvar() {
	Salvar();
}
*/

void Inimigo::setar_direcao() {

	if (ponteiro_jogador2 == nullptr) {

		if (ponteiro_jogador1->get_X() > pos.x) {
			direcao = direita;
		}
		else {
			direcao = esquerda;
		}
	}
	else {

		if (ponteiro_jogador1->get_X() > ponteiro_jogador2->get_X()) {

			if (ponteiro_jogador1->get_X() > pos.x) {
				direcao = direita;
			}
			else {
				direcao = esquerda;
			}
		}
		else {

			if (ponteiro_jogador2->get_X() > pos.x) {
				direcao = direita;
			}
			else {
				direcao = esquerda;
			}
		}
	}
}


void Inimigo::setar_Jogador_No_Inimigo(Jogador* pJogador1, Jogador* pJogador2) {

	if(pJogador1 == nullptr && pJogador2 == nullptr){
		std::cout << "Erro: ponteiros de jogador nulos ao setar no inimigo." << std::endl;
	}
	else {
		if (pJogador2 == nullptr) {
			ponteiro_jogador1 = pJogador1;
		}
		else if (pJogador1 == nullptr) {
			ponteiro_jogador2 = pJogador2;
		}
		else {
			ponteiro_jogador1 = pJogador1;
			ponteiro_jogador2 = pJogador2;
		}
	}
}

void Inimigo::danificar(int lado, Jogador* pJogador) {

	if (lado == lado_fraco) {
		pJogador->colidir(static_cast<Personagem*>(this));
	}
	else {
		pJogador->diminuir_Vitalidade(dano);
	}
}

void Inimigo::colidiu_Obstaculo(int lado) {
}

//sem uso por hora.
/*
void Inimigo::dar_Pontuacao_a_Jogadores() {

	if(!ponteiro_jogador1->get_Eliminado()){
		ponteiro_jogador1->aumentar_Pontuacao(pontos_de_eliminacao);
	}
	if(!ponteiro_jogador2->get_Eliminado()){
		ponteiro_jogador2->aumentar_Pontuacao(pontos_de_eliminacao);
	}
	
}*/

const int Inimigo::id_base(100);
