#pragma once

#include "Fases/Fase.h"
#include "Entidades/Obstaculos/Espinho.h"
#include "Entidades/Personagens/Inimigos/Capitao.h"
#include "Entidades/Projetil.h"

namespace Fases{

	class Fase_2 : public Fase
	{
	private:
		int num_capitoes;
		int num_restante_capitoes;
		int num_espinhos;
		int num_restante_espinhos;

		std::vector<Entidades::Personagens::Capitao*> lista_cap;

		void remover_Inimigo_Das_Listas_Auxiliares(Entidades::Personagens::Inimigo* pInimigo);
		void Cria_Inimigos_Especificos();
		void criar_Entidades_em_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat, float ponta_esq, float ponta_dir);
		void Cria_Obstaculos_Restantes();
		void executar_Antes_Entidades();
		void executar_Depois_Entidades();

		void Cria_Capitao(float x, float y);
		Entidades::Projetil* Cria_Projetil();
		void verifica_Projeteis_Destroidos();
		void Cria_Espinhos(float pos_plat_x, float pos_plat_y);
		void Cria_Espinhos_Restantes();
		void cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat);
		void cria_Espinhos_na_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat);

	public:
		Fase_2();
		~Fase_2();
	};
}
