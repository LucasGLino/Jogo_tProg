#pragma once

#include "Fases/Fase.h"
#include "Entidades/Obstaculos/Plataforma.h"
//#include "Entidades/Obstaculos/Espinhos.h"
#include "Entidades/Personagens/Inimigos/Capitao.h"
#include "Entidades/Projetil.h"

namespace Fases{

	class Fase_2 : public Fase
	{
	private:
		int num_capitoes;
		int num_piratas;
		int num_restante_piratas;
		int num_restante_capitoes;
		//int num_restante_espinhos;

		int i,j;

		float zoom_camera;
		float tamanho_da_tela_x;

		int num_max_andares;
		float espaco_vazio_x;
		int num_max_plataformas;
		//int num_espinhos;

		std::vector<int> num_plataformas_por_andar;

		std::vector<Entidades::Personagens::Capitao*> lista_cap;
		//std::vector<Entidades::Obstaculos::Espinhos*> lista_espinhos;
		sf::Texture textura_fundo;
		sf::Sprite fundo;
		bool fundo_carregado;

		void remover_Inimigo_Das_Listas_Auxiliares(Entidades::Personagens::Inimigo* pInimigo);
		void ajustar_Fundo_A_Camera();

	public:

		Fase_2();
		~Fase_2();
		
		void Cria_Obstaculos();
		void Cria_Inimigos();
		void Cria_Capitao(float x, float y);

		void executar();
		Entidades::Projetil* Cria_Projetil();
		void verifica_Projeteis_Destroidos();

		void seta_Tamanho_Plataformas(int n_plataformas);
		void seta_Num_Plataformas();
		void Cria_Plataforma();
		void Cria_Piso();
		//void Cria_Espinhos(float pos_plat_x, float pos_embaixo_plat_y, float tam_plat_x);


		void atualiza_Camera_Fase(Entidades::Personagens::Jogador* p_jogador1, Entidades::Personagens::Jogador* p_jogador2);
		void setar_Camera_Fase();
		void cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat);
		//void cria_Espinhos_na_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat);

	};
}
