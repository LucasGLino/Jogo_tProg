#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Entidades/Personagens/Jogador/Jogador.h"
#include "Fases/Fase_1.h"
#include "Fases/Fase_2.h"
//#include "Core/Menus/Menu.h"
#include "Estados/MenuEstado.h"
#include "Estados/GerenciadorEstado.h"



class Jogo : public Gerenciador_Estado{

	private:
		Gerenciadores::Gerenciador_Grafico* Ger_Graf;

		Entidades::Personagens::Jogador jogador_1;
		Entidades::Personagens::Jogador jogador_2;

		Fases::Fase_1* fase1;
		Fases::Fase_2* fase2;

		//Menu *menu;
		//jogando 0 , Menu 1, Pausado 2, Venceu 3, Perdeu 4
		int estado;

		bool fase_1_ativa;
		bool fase_2_ativa;
		bool acabou;

	public:
		Jogo();
		~Jogo();

		void executar();

		//void setEstado(Estado novoEstado);
		//Estado getEstado() const;
		void set_pJog2_Dois_Jogadores(bool valor);
		bool get_pJog2_Dois_Jogadores();
		void setar_Fase();
		void atualiza_Camera();
		//void EstadoDoJogo();
		void verifica_Fim_De_Jogo();

};