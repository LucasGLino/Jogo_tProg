#pragma once

#include "Fases/Fase.h"
#include <vector>

namespace Entidades {
	class Projetil;

	namespace Personagens {
		class Capitao;
	}
}

namespace Fases{

	class Fase_2 : public Fase
	{
		private:
			// Quantidades usadas para distribuir capitaes e espinhos na fase.
			int num_capitoes;
			int num_restante_capitoes;
			int num_capitoes_em_plataformas;
			int num_espinhos;
			int num_restante_espinhos;

			// Lista auxiliar para controlar os capitaes e seus projeteis.
			std::vector<Entidades::Personagens::Capitao*> lista_cap;

		private:
			// Criacao e execucao especificas da segunda fase.
			void remover_Inimigo_Das_Listas_Auxiliares(Entidades::Personagens::Inimigo* pInimigo);
			void Cria_Inimigos_Especificos();
			void criar_Entidades_em_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat, float ponta_esq, float ponta_dir);
			void Cria_Obstaculos_Restantes();
			void executar_Antes_Entidades();
			void executar_Depois_Entidades();

			// Criadores e auxiliares usados pelo fluxo da fase 2.
			void Cria_Capitao(float x, float y);
			Entidades::Projetil* Cria_Projetil();
			void verifica_Projeteis_Destroidos();
			void Cria_Espinhos(float pos_plat_x, float pos_plat_y);
			void Cria_Espinhos_Restantes();
			void cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat);
			void cria_Espinhos_na_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat);

		public:
			Fase_2();
			virtual ~Fase_2();
	};
}
