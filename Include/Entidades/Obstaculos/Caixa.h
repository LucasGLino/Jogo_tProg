#pragma once
#include"Obstaculo.h"


namespace Entidades {
	namespace Obstaculos {
		class Caixa : public Obstaculo
		{
		private:
            bool sendo_empurrada;

			bool empurrar_esquerda;

			float distancia_percorrida;

			sf::Clock relogio_empurrao;

		public:

			Caixa();
			~Caixa();

			void executar();
			void seta_Caixa(float origem_x, float origem_y);
			void obstacular(Entidades::Personagens::Jogador* p, int lado);
			void iniciar_Empurrao(int lado);
			void executar_Empurrao();
			void parar_Empurrao();
			void salvar();

		};
	}
}
