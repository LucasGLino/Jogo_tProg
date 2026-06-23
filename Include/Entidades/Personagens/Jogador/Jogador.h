#pragma once

#include "Entidades/Personagens/Personagem.h"

namespace Entidades{
	namespace Personagens {

		class Jogador : public Personagem
		{
			private:
				// Pontuacao acumulada pelo jogador.
				int pontos;

				// Id base separado dos outros personagens.
				static const int id_base;

				// Diz se este objeto representa o segundo jogador.
				bool segundo_jogador;

				// Controlam o estado do pulo.
				bool estado_pulando;
				bool no_ar;
				bool acelerando;
				
				// Forca inicial usada no pulo.
				float forca_de_impulso;

				// Carrega a imagem padrao do jogador.
				void setar_Figura();

			public:
				Jogador(sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely);
				virtual ~Jogador();

				// Marca este objeto como jogador 2 quando o jogo tem dois jogadores.
				void setar_Dois_Jogadores(bool jogador_dois);

				// Retorna se este jogador e o segundo jogador.
				bool get_Dois_Jogadores() const;

				// Comeca o pulo quando o jogador esta no chao.
				void executando_Pulo();

				// Cancela o impulso quando bate a cabeca.
				void setar_Bateu_A_Cabeca();

				// Libera um novo pulo ao encostar no chao ou plataforma.
				void setar_Pode_Pular();

				// Retorna a pontuacao atual.
				int get_Pontuacao() const;

				// Aplica dano e elimina o jogador se as vidas acabarem.
				void diminuir_Vitalidade(int dano);

				// Ataca outro personagem e usa o impulso do pulo.
				void colidir(Personagem* pAtacado);

				// Soma pontos ganhos por eliminar inimigos.
				void aumentar_Pontuacao(int pontos_a_adicionar);

				// Le teclado e altera a posicao.
				void mover();

				// Atualiza fisica, movimento e desenho.
				void executar();

				// Salvar ainda nao foi implementado para jogador.
				void salvar();

		};
	}
}
