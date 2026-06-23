#pragma once

#include "Entidades/Personagens/Personagem.h"



namespace Entidades{
	namespace Personagens {


		class Jogador : public Personagem
		{
			private:
				int pontos;
				static const int id_base;

				bool segundo_jogador;
				

				bool estado_pulando;
				bool no_ar;

				bool acelerando;
				
				float forca_de_impulso;

			private:
				void setar_Figura();

			public:
				Jogador(sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely);
				~Jogador();

				void setar_Dois_Jogadores(bool jogador_dois);
				bool get_Dois_Jogadores();
				void executando_Pulo();

				void setar_Bateu_A_Cabeca();
				void setar_Pode_Pular();

				int get_Pontuacao() const;

				void diminuir_Vitalidade(int dano);
				void colidir(Personagem* pAtacado);

				int get_Vida();
				int get_Pontos();

				void aumentar_Pontuacao(int pontos_a_adicionar);

				void mover();

				void executar();
				void salvar();

		};
	}
}
