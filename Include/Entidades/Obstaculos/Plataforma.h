#pragma once

#include "Entidades/Obstaculos/Obstaculo.h"

namespace Entidades {
	namespace Obstaculos {
		class Plataforma : public Obstaculo
		{
		private:
			// Ponto central da oscilacao vertical.
			sf::Vector2f origem;

			// Controla se a plataforma esta subindo ou descendo.
			bool subindo;

			// Distancia maxima que ela oscila para cima e para baixo.
			float flutuabilidade;

			// Aplica a oscilacao vertical.
			void flutuar();

		public:
			Plataforma();
			virtual ~Plataforma();

			// Guarda a origem usada na flutuacao.
			void seta_Origem(float origem_x, float origem_y);

			// Atualiza a flutuacao e desenha a plataforma.
			void executar();

			// Reage a colisao com o jogador.
			void obstacular(Entidades::Personagens::Jogador* p, int lado);

			// Salvar ainda nao foi implementado para plataforma.
			void salvar();
		};
	}
}
