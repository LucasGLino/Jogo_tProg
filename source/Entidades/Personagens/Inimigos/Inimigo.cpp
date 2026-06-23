#include "Entidades/Personagens/Inimigos/Inimigo.h"

using namespace Entidades;
using namespace Personagens;

const int Inimigo::id_base(100);

// Comeca com valores neutros para os inimigos filhos configurarem depois.
Inimigo::Inimigo() : Personagem(id_base, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), 1, 0.f, 0.f), direcao(0)
{
	ponteiro_jogador1 = nullptr;
	ponteiro_jogador2 = nullptr;
	parar = true;
	pontos_de_eliminacao = 0;
	lado_fraco = cima;
	nivel_maldade = -1;

	pos_inicial.x = 0.f;
	pos_inicial.y = 0.f;
	pos_final.x = 0.f;
	pos_final.y = 0.f;
}

// Nao precisa liberar nada alem do que a classe base ja cuida.
Inimigo::~Inimigo()
{
}

// Guarda os jogadores para o inimigo consultar durante a fase.
void Inimigo::setar_Jogador_No_Inimigo(Jogador* pJogador1, Jogador* pJogador2)
{
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

// Vira o inimigo para o lado do jogador escolhido.
void Inimigo::setar_direcao()
{
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

// Salva destino e direcao para movimentos simples.
void Inimigo::andar_ate(float em_x, float em_y)
{
	if (em_x > pos.x) {
		direcao = direita;
	}
	else{
		direcao = esquerda;
	}

	pos_final.x = em_x;
	pos_final.y = em_y;
}

// Dano padrao: jogador ataca no lado fraco, senao recebe dano.
void Inimigo::danificar(int lado, Jogador* pJogador)
{
	if (lado == lado_fraco) {
		pJogador->colidir(static_cast<Personagem*>(this));
	}
	else {
		pJogador->diminuir_Vitalidade(dano);
	}
}

// Inimigos filhos podem sobrescrever quando precisarem reagir.
void Inimigo::colidiu_Obstaculo(int lado)
{
}
