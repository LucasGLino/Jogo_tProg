#pragma once
#include "Entidades/Entidade.h"

namespace Entidades {

	namespace Personagens {
		class Jogador;
	}


	class Projetil : public Entidade
	{
		private:
			// Identificador base usado pelos projeteis.
			static const int id_base;

			// Controla se o projetil deve mover, colidir e ser desenhado.
			bool ativo;

			// Guarda direcao e dano definidos pelo capitao no disparo.
			int lado;
			int dano;

			// Aplica o ajuste vertical proprio do projetil durante o voo.
			void executar_Empuxo();

	public:

		Projetil();
		virtual ~Projetil();


		// Define o estado usado pelo gerenciador de colisoes.
		void setar_Ativo(bool atv);

		// Configura os dados recebidos do capitao ao disparar.
		void setar_Dano(int dan);
		void setar_Direcao(int direcao);

		// Informa se o projetil ainda participa do jogo.
		bool get_Ativo();

		// Aplica dano ao jogador atingido.
		void Atingiu_Jogador(Entidades::Personagens::Jogador* pJogador);

		// Move e desenha o projetil quando estiver ativo.
		void executar();

		// Salvar ainda nao foi implementado para projetil.
		void salvar();
	};
}
