#pragma once
#include "Entidades/Personagens/Personagem.h"
#include "Entidades/Personagens/Jogador/Jogador.h"

namespace Entidades {
	namespace Personagens {

		class Inimigo : public Personagem
		{
			protected:
				int nivel_maldade;
				static const int id_base;
				Jogador* ponteiro_jogador1;
				Jogador* ponteiro_jogador2;
				bool perseguir;

				bool parar;

				int pontos_de_eliminacao;

				int direcao;
				int lado_fraco;


				//int dano

				sf::Vector2f pos_inicial;
				sf::Vector2f pos_final;

			public:
				Inimigo();
				~Inimigo();

				void setar_Jogador_No_Inimigo(Entidades::Personagens::Jogador* pJogador1, Entidades::Personagens::Jogador* pJogador2);
				void setar_direcao();

				virtual void andar_ate(float em_x, float em_y);
				//virtual void salvar();
				virtual void executar() = 0;
				virtual void salvar() = 0;

				//virtual void Executar();
				virtual void danificar(int lado, Entidades::Personagens::Jogador* pJogador);

				virtual void setar_Pontos_Por_Eliminacao(int pontos) = 0;

				//sem utilidade por hora.
				//virtual void dar_Pontuacao_a_Jogadores();

		};
	}
}
