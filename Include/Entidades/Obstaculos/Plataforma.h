#pragma once
#include "Entidades/Obstaculos/Obstaculo.h"

namespace Entidades {
	namespace Obstaculos {
		class Plataforma : public Obstaculo
		{
		private:

			bool ativa;
			sf::Vector2f origem;

			bool subindo;

			//define se é chão ou não
			bool chao;

			//define quantos pixeis ele ocila para cima e para baixo ao flutuar.
			float flutuabilidade;

		public:

			Plataforma();
			~Plataforma();

			void seta_Origem(float origem_x, float origem_y);

			// void seta_Plataforma(float alt, float larg, float origem_x, float origem_y);
			void determinar_chao();
			void flutuar();
			void executar();
			void obstacular(Entidades::Personagens::Jogador* p, int lado);
			void salvar();

		};
	}
}
