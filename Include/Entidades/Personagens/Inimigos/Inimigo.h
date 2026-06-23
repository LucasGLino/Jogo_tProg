#pragma once
#include "Entidades/Personagens/Personagem.h"
#include "Entidades/Personagens/Jogador/Jogador.h"

namespace Entidades {
	namespace Personagens {

		class Inimigo : public Personagem
		{
			protected:
				// Varia alguns atributos dos inimigos filhos.
				int nivel_maldade;

				// Id base dos inimigos.
				static const int id_base;

				// Jogadores usados para perseguicao, ataque e direcao.
				Jogador* ponteiro_jogador1;
				Jogador* ponteiro_jogador2;

				// Pausa ou libera o movimento do inimigo.
				bool parar;

				// Pontos dados ao jogador quando o inimigo morre.
				int pontos_de_eliminacao;

				// Direcao atual e lado fraco usado em colisao.
				int direcao;
				int lado_fraco;

				// Posicoes base usadas por movimento e patrulha.
				sf::Vector2f pos_inicial;
				sf::Vector2f pos_final;

			public:
				Inimigo();
				virtual ~Inimigo();

				// Guarda os jogadores que o inimigo pode usar como alvo.
				void setar_Jogador_No_Inimigo(Entidades::Personagens::Jogador* pJogador1, Entidades::Personagens::Jogador* pJogador2);

				// Ajusta a direcao olhando para o jogador alvo.
				void setar_direcao();

				// Define um ponto de destino simples.
				virtual void andar_ate(float em_x, float em_y);

				// Cada inimigo filho executa sua propria rotina.
				virtual void executar() = 0;

				// Salvar ainda nao foi implementado para inimigo.
				virtual void salvar() = 0;

				// Cada inimigo filho decide como se move.
				virtual void mover() = 0;

				// Trata o dano causado ou recebido na colisao com jogador.
				virtual void danificar(int lado, Entidades::Personagens::Jogador* pJogador);

				// Responde a colisao lateral com obstaculo.
				virtual void colidiu_Obstaculo(int lado);

				// Define a pontuacao que o inimigo vale.
				virtual void setar_Pontos_Por_Eliminacao(int pontos) = 0;

		};
	}
}
