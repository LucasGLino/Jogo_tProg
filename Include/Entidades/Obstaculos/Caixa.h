#pragma once

#include "Entidades/Obstaculos/Obstaculo.h"

namespace Entidades {
	namespace Obstaculos {
		class Caixa : public Obstaculo
		{
		private:
			// Controla se a caixa esta sendo empurrada agora.
			bool sendo_empurrada;

			// Diz se o empurrao atual vai para a esquerda.
			bool empurrao_para_esquerda;

			// Limita o quanto a caixa anda em cada empurrao.
			float distancia_percorrida;

			// Evita empurroes seguidos sem pausa.
			sf::Clock relogio_empurrao;

			// Comeca um empurrao lateral.
			void iniciar_Empurrao(int lado);

			// Move a caixa durante o empurrao.
			void executar_Empurrao();

			// Finaliza o empurrao atual.
			void parar_Empurrao();

		public:
			Caixa();
			virtual ~Caixa();

			// Atualiza gravidade, empurrao e desenho.
			void executar();

			// Configura tamanho, textura, posicao e massa da caixa.
			void seta_Caixa(float origem_x, float origem_y);

			// Inicia empurrao quando o jogador encosta de lado.
			void obstacular(Entidades::Personagens::Jogador* p, int lado);

			// Salvar ainda nao foi implementado para caixa.
			void salvar();
		};
	}
}
