#pragma once
#include "Entidades/Personagens/Inimigos/Inimigo.h"
#include "Entidades/Projetil.h"
#include <vector>

namespace Entidades {
	namespace Personagens {

		class Capitao : public Inimigo
		{

			// Forca usada como dano do projetil disparado.
			short int forca;

			// Controla quando a fase deve criar um projetil.
			bool disparou;

			// Temporizador simples entre disparos.
			int recarga;
			int espera;

			// Define se o jogador esta dentro da area de tiro.
			bool pode_disparar;
			
			// Area onde o capitao enxerga o jogador.
			sf::Vector2f visao;

			// Velocidade aplicada no projetil.
			sf::Vector2f velocidade_proj;

			// Projeteis disparados e ainda acompanhados pelo capitao.
			std::vector<Entidades::Projetil*> disparos;

			public:
				Capitao();
				virtual ~Capitao();
				
				// Diz se o capitao disparou neste frame.
				bool get_Disparou() const;

				// Configura e guarda um projetil novo.
				void incluir_Projetil(Projetil* projet);

				// Remove o projetil da lista do capitao.
				void remover_Projetil(Projetil* projet);

				// Da acesso aos projeteis para a fase limpar os inativos.
				std::vector<Entidades::Projetil*>* get_Vetor_De_Projetis();

				// Atualiza gravidade, tiro e movimento.
				void executar();

				// Salvar ainda nao foi implementado para capitao.
				void salvar();

				// Trata dano entre capitao e jogador.
				void danificar(int lado, Entidades::Personagens::Jogador* pJogador);

				// Procura jogador na visao e decide se deve disparar.
				void mover();

				// Muda a direcao ao encostar em obstaculo.
				void colidiu_Obstaculo(int lado);

				// Define quantos pontos o capitao vale.
				void setar_Pontos_Por_Eliminacao(int pontos);

		};
	}
}
