#pragma once

#include "Entidades/Ente.h"
#include "Listas/ListaEnt.h"
#include "Entidades/Obstaculos/Obstaculo.h"
#include "Entidades/Obstaculos/Plataforma.h"
#include "Entidades/Personagens/Inimigos/Inimigo.h"
#include "Entidades/Personagens/Inimigos/Pirata.h"
#include "Entidades/Personagens/Jogador/Jogador.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"
#include <list>

namespace Fases {
	class Fase : public Ente
	{
		protected:
			static int base_Id;

			//tem como a lista_Entidades passar parametros a classe que n�o necess�riamente entidades?
			bool ganhou;
			bool perdeu;
			Listas::ListaEnt lista_Entidades;
			Entidades::Obstaculos::Plataforma* piso;
			Entidades::Obstaculos::Plataforma* plataforma;
			Gerenciadores::Gerenciador_colisoes gerenciador_colisoes;
			std::list<int> lista_id_inimigos;

			sf::Texture textura_fundo;
			sf::Sprite fundo;
			

			sf::Vector2f tam_Piso_Fase;
			sf::Vector2f pos_Piso;

			int num_plataformas_totais;
			int num_inimigos;

			bool fundo_carregado;

			sf::Vector2f tam_plataforma;

			sf::Vector2f pos_original;

			virtual void remover_Inimigo_Das_Listas_Auxiliares(Entidades::Personagens::Inimigo* pInimigo);

			void Cria_Pirata(float x, float y, float patrulha_ate_a, float patrulha_ate_b);

			void Cria_Plataforma(float alt, float larg, float origem_x, float origem_y);


		public:
			Fase();
			virtual ~Fase();

			void Setar_Jogadores(Entidades::Personagens::Jogador* p_jogador1, Entidades::Personagens::Jogador* p_jogador2);
			void Setar_Jogadores_Colisoes(Entidades::Personagens::Jogador* p_jogador1, Entidades::Personagens::Jogador* p_jogador2);
			void Setar_Jogadores_Inimigos(Entidades::Personagens::Jogador* p_jogador1, Entidades::Personagens::Jogador* p_jogador2);


			bool get_Ganhou();

			virtual void executar();
			virtual void Cria_Piso() = 0;
			virtual void Cria_Inimigos() = 0;	
			virtual void Cria_Obstaculos() = 0;

			void ajustar_Fundo_A_Camera();

			void atualiza_Camera_Fase(Entidades::Personagens::Jogador* p_jogador1, Entidades::Personagens::Jogador* p_jogador2);
			virtual void setar_Camera_Fase() = 0;

			void criar_cenario();
			void verifica_Inimigos_Neutralizados();

			bool verifica_Se_Caiu_No_Abismo(Entidades::Entidade* pEntidade);

	};
}
