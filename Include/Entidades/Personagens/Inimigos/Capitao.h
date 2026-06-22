#pragma once
#include "Entidades/Personagens/Inimigos/Inimigo.h"
#include "Entidades/Projetil.h"
#include <vector>

namespace Entidades {
	namespace Personagens {

		class Capitao : public Inimigo
		{

			short int forca;
			bool disparou;
			int recarga;
			int espera;
			bool pode_disparar;
			bool parar;
			

			sf::Vector2f visao;

			sf::Vector2f velocidade_proj;


			std::vector<Entidades::Projetil*> disparos;

			int dano_do_balote;

			public:
				Capitao();
				~Capitao();
				
				const bool get_Disparou();

				void incluir_Projetil(Projetil* projet);
				void remover_Projetil(Projetil* projet);

				std::vector<Entidades::Projetil*>* get_Vetor_De_Projetis();
				void imprime_Projeteis_Ids_Ativos_e_Pos();

				void executar();
				void salvar();
				void danificar(int lado, Entidades::Personagens::Jogador* pJogador);
				void mover();
				void colidiu_Obstaculo(int lado);
				void setar_Pontos_Por_Eliminacao(int pontos);

		};
	}
}
