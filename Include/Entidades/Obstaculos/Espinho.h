#pragma once
#include "Entidades/Obstaculos/Obstaculo.h"
#include"Entidades/Personagens/Jogador/Jogador.h"


namespace Entidades {
	namespace Obstaculos {
		class Espinho : public Obstaculo
		{
		private:
			//sf::Vector2f tamanho;

            bool enferrujado;

			int danosidade;

			int dano_tetano;

			sf::Clock clock;

			bool Jog_tetano;

			float intervalo_tetano;

			int max_danos_tetano;

			int contador_dano;

			Entidades::Personagens::Jogador* pJog;

			sf::Vector2f pos_final;

		public:

			Espinho();
			~Espinho();

			void executar();
			void obstacular(Entidades::Personagens::Jogador* pJogador, int lado);
			void Tetano_Danar();
			void salvar();

		};
	}
}
