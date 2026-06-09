#pragma once
#include "Entidades/Obstaculos/Obstaculo.h"

namespace Entidades {
	namespace Obstaculos {
		class Plataforma : public Obstaculo
		{
		private:
			//sf::Vector2f tamanho;
			bool ativa;
			bool se_move;

			sf::Vector2f pos_final;

		public:

			Plataforma();
			~Plataforma();

			void seta_Plataforma(float alt, float larg, float origem_x, float origem_y);
			void seta_Movimento(float x_esq,float x_dir, float y_cima, float y_baixo);
			void Executar();
			void obstacular(Entidades::Personagens::Jogador* p, int lado);
			void Salvar();

		};
	}
}
