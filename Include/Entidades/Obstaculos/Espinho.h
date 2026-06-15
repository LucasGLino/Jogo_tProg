#pragma once
#include "Entidades/Obstaculos/Obstaculo.h"

namespace Entidades {
	namespace Obstaculos {
		class Espinho : public Obstaculo
		{
		private:
			//sf::Vector2f tamanho;
			bool ativa;

            bool tetano;

			sf::Vector2f pos_final;

		public:

			Espinho();
			~Espinho();

			void Executar();
			void obstacular(Entidades::Personagens::Jogador* p, int lado);
			void Salvar();

		};
	}
}
