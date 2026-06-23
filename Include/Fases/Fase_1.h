#pragma once

#include "Fases/Fase.h"

namespace Fases{

	class Fase_1 : public Fase
	{
	public:
		Fase_1();
		virtual ~Fase_1();

	private:
		// Quantidades usadas para distribuir esqueletos e caixas na fase.
		int num_esqueletos;
		int num_restante_esqueletos;
		int num_esqueletos_em_plataformas;
		int num_caixas;
		int num_restante_caixas;

		// Criacao especifica da primeira fase.
		void Cria_Inimigos_Especificos();
		void criar_Entidades_em_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat, float ponta_esq, float ponta_dir);
		void Cria_Obstaculos_Restantes();

		// Criadores auxiliares usados pelo fluxo de montagem da fase.
		void Cria_Esqueletos(float x, float y, float patrulha_ate_a, float patrulha_ate_b);
		void Cria_Caixas(float pos_caixa_x, float pos_caixa_y);
		void Cria_Caixas_Restantes();
		void cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat);
		void cria_Caixas_na_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat);
	};
}
