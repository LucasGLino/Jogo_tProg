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

		Fases::Fase_1* fase1;
		Fases::Fase_2* fase2;

		Gerenciador_Estado* pGe;

		static Jogo* pInstancia;

		Jogo();

	public:
		
		~Jogo();

		static Jogo* getInstancia();

		void executar();

		// void criar_fase_1();


		// void set_pJog2_Dois_Jogadores(bool valor);
		// bool get_pJog2_Dois_Jogadores();
		// Entidades::Personagens::Jogador* get_Jogador_1();
		// Entidades::Personagens::Jogador* get_Jogador_2();
		// Fases::Fase* get_fase_1();
		// Fases::Fase* get_fase_2();
		// void setar_Fase(Fases::Fase* pFase);
		// void atualiza_Camera(Fases::Fase* pFase);

};
