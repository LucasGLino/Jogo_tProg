#pragma once
#include "Entidades/Entidade.h"

namespace Entidades {

	namespace Personagens {
		class Capitao;
	}
	namespace Personagens {
		class Jogador;
	}


	class Projetil : public Entidade
	{
		private:
			static const int id_base;
			bool ativo;
			int lado;
			int dano;
			int tempo_de_vida;
			int tempo_ativo;
			bool atingiu_jogador;

			Entidades::Entidade* proprietario;
			//Entidades::Personagens::Capitao* cap;

		//const int direita, cima, esquerda, baixo;

	public:

		Projetil();
		Projetil(float saida_x, float saida_y, int lado);

		~Projetil();


		void setar_Ativo(bool atv);
		void setar_Dano(int dan);
		void setar_Direcao(int direcao);
		void setar_Proprietario(Entidades::Entidade* propriet);

		int get_Dano();
		bool get_Ativo();
		void Atingiu_Jogador(Entidades::Personagens::Jogador* pJogador);

		void executar_Gravidade();
		void executar();
		void salvar();

		void setar_Cor(sf::Color cor);
	};
}
