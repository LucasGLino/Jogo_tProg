#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Entidades/Personagens/Jogador/Jogador.h"
#include "Fases/Fase_1.h"
#include "Fases/Fase_2.h"
#include "Estados/MenuEstado.h"
#include "Estados/GerenciadorEstado.h"



class Jogo{

	private:
		Gerenciadores::Gerenciador_Grafico* Ger_Graf;

		Entidades::Personagens::Jogador* jogador_1;
		Entidades::Personagens::Jogador* jogador_2;

		Fases::Fase* pFase;

		Gerenciador_Estado* pGe;

		static Jogo* pInstancia;

		Jogo();

	public:
		
		~Jogo();

		static Jogo* getInstancia();

		void executar();

		void criar_fase_1();

		void criar_fase_2();

		void cria_jogador_1();

		void cria_jogador_2();

		Entidades::Personagens::Jogador* get_Jog_1();

		Entidades::Personagens::Jogador* get_Jog_2();

		Gerenciadores::Gerenciador_Grafico* get_pGG();

		void set_pJog2_Dois_Jogadores(bool valor);

		bool get_pJog2_Dois_Jogadores();

		void setar_Fase();

		void atualiza_Camera();

		void verifica_Fim_De_Jogo();
};