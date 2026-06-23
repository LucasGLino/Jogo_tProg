#pragma once

#include "Entidades/Ente.h"
#include "Entidades/Chao.h"
#include "Listas/ListaEnt.h"
#include "Entidades/Obstaculos/Obstaculo.h"
#include "Entidades/Obstaculos/Plataforma.h"
#include "Entidades/Personagens/Inimigos/Inimigo.h"
#include "Entidades/Personagens/Inimigos/Pirata.h"
#include "Entidades/Personagens/Jogador/Jogador.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"
#include <list>
#include <vector>

namespace Fases {
	class Fase : public Ente
	{
	protected:
		static int base_Id;

		bool ganhou;
		Listas::ListaEnt lista_Entidades;
		Entidades::Chao* chao;
		Entidades::Obstaculos::Plataforma* plataforma;
		Gerenciadores::Gerenciador_colisoes gerenciador_colisoes;
		std::list<int> lista_id_inimigos;

		sf::Texture textura_fundo;
		sf::Sprite fundo;
		bool fundo_carregado;

		sf::Vector2f tam_Piso_Fase;
		sf::Vector2f pos_Piso;
		sf::Vector2f tam_plataforma;

		int num_plataformas_totais;
		int num_piratas;
		int num_restante_piratas;
		int num_max_andares;
		int num_piratas_em_plataformas;

		float zoom_camera;
		float tamanho_da_tela_x;
		float espaco_vazio_x;

		std::vector<int> num_plataformas_por_andar;
		std::vector<sf::Vector2f> posicoes_spawn_usadas;

		virtual void remover_Inimigo_Das_Listas_Auxiliares(Entidades::Personagens::Inimigo* pInimigo);
		virtual void Cria_Inimigos_Especificos() = 0;
		virtual void criar_Entidades_em_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat, float ponta_esq, float ponta_dir) = 0;
		virtual void Cria_Obstaculos_Restantes();
		virtual void executar_Antes_Entidades();
		virtual void executar_Depois_Entidades();
		bool posicao_Spawn_Ja_Usada(float x, float y_referencia);
		void registrar_Posicao_Spawn(float x, float y_referencia);
		float ajustar_X_Spawn(float x, float y_referencia);
		bool pode_Criar_Na_Plataforma(int total_restante, int minimo_no_chao);

		void Cria_Pirata(float x, float y, float patrulha_ate_a, float patrulha_ate_b);
		void Cria_Piratas_Restantes();
		void Cria_Plataforma(float alt, float larg, float origem_x, float origem_y);

	public:
		Fase();
		virtual ~Fase();

		void Setar_Jogadores(Entidades::Personagens::Jogador* p_jogador1, Entidades::Personagens::Jogador* p_jogador2);
		void Setar_Jogadores_Colisoes(Entidades::Personagens::Jogador* p_jogador1, Entidades::Personagens::Jogador* p_jogador2);
		void Setar_Jogadores_Inimigos(Entidades::Personagens::Jogador* p_jogador1, Entidades::Personagens::Jogador* p_jogador2);

		bool get_Ganhou();

		virtual void executar();
		void Cria_Piso();
		void Cria_Inimigos();
		void Cria_Obstaculos();

		void ajustar_Fundo_A_Camera();
		void atualiza_Camera_Fase(Entidades::Personagens::Jogador* p_jogador1, Entidades::Personagens::Jogador* p_jogador2);
		void setar_Camera_Fase();

		void seta_Tamanho_Plataformas(int n_plataformas);
		void seta_Num_Plataformas();
		void Posiciona_plataforma();

		void verifica_Inimigos_Neutralizados();
		bool verifica_Se_Caiu_No_Abismo(Entidades::Entidade* pEntidade);
	};
}
