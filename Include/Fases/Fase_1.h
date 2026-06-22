#pragma once

#include "Fases/Fase.h"
#include "Entidades/Obstaculos/Plataforma.h"
#include "Entidades/Obstaculos/Caixa.h"
#include "Entidades/Personagens/Inimigos/Esqueleto.h"
#include "Entidades/Projetil.h"

namespace Fases{

	class Fase_1 : public Fase
	{
	private:
		int num_esqueletos;
		int num_piratas;
		int num_restante_piratas;
		int num_restante_esqueletos;
		int num_restante_caixas;

		int i,j;

		float zoom_camera;
		float tamanho_da_tela_x;

		int num_max_andares;
		float espaco_vazio_x;
		int num_max_plataformas;
		int num_caixas;

		std::vector<int> num_plataformas_por_andar;

		std::vector<Entidades::Obstaculos::Caixa*> lista_caixa;
		sf::Texture textura_fundo;
		sf::Sprite fundo;
		bool fundo_carregado;
        
		void ajustar_Fundo_A_Camera();

	public:

		Fase_1();
		~Fase_1();
		
		void Cria_Obstaculos();
		void Cria_Inimigos();
        void Cria_Esqueletos(float x, float y, float patrulha_ate_a, float patrula_ate_b);

		void executar();

		void seta_Tamanho_Plataformas(int n_plataformas);
		void seta_Num_Plataformas();
		void Posiciona_plataforma();
		void Cria_Piso();
		void Cria_Caixas(float pos_caixa_x, float pos_caixa_y);
		void Cria_Caixas_Restantes();


		void atualiza_Camera_Fase(Entidades::Personagens::Jogador* p_jogador1, Entidades::Personagens::Jogador* p_jogador2);
		void setar_Camera_Fase();
		void cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat);
		void cria_Caixas_na_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat);

	};
}
