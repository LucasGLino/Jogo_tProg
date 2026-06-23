#pragma once
#include "Entidades/Obstaculos/Obstaculo.h"
#include "Entidades/Personagens/Jogador/Jogador.h"


namespace Entidades {
	namespace Obstaculos {
		class Espinho : public Obstaculo
		{
		private:
			// Define o dano direto e se o espinho tambem causa tetano.
			bool enferrujado;

			int danosidade;

			// Controla o dano extra de tetano depois que o jogador encosta no espinho.
			int dano_tetano;

			sf::Clock relogio_tetano;

			bool tetano_ativo;

			float intervalo_tetano;

			int max_danos_tetano;

			int contador_dano;

			Entidades::Personagens::Jogador* pJogador_tetano;

			// Aplica o dano do tetano enquanto o efeito estiver ativo.
			void aplicar_Dano_Tetano();

		public:

			Espinho();
			virtual ~Espinho();

			void executar();
			void obstacular(Entidades::Personagens::Jogador* pJogador, int lado);
			void salvar();

		};
	}
}
