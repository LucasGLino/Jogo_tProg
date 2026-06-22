#pragma once

#include "Fases/Fase.h"
#include "Entidades/Obstaculos/Caixa.h"
#include "Entidades/Personagens/Inimigos/Esqueleto.h"

namespace Fases{

	class Fase_1 : public Fase
	{
	private:
		int num_esqueletos;
		int num_restante_esqueletos;
		int num_caixas;
		int num_restante_caixas;

		void Cria_Inimigos_Especificos();
		void criar_Entidades_em_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat, float ponta_esq, float ponta_dir);
		void Cria_Obstaculos_Restantes();

		void Cria_Esqueletos(float x, float y, float patrulha_ate_a, float patrula_ate_b);
		void Cria_Caixas(float pos_caixa_x, float pos_caixa_y);
		void Cria_Caixas_Restantes();
		void cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat);
		void cria_Caixas_na_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat);

	public:
		Fase_1();
		~Fase_1();
	};
}
