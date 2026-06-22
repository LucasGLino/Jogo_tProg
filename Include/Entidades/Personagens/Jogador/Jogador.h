#pragma once

#include "Entidades/Personagens/Personagem.h"



namespace Entidades{
	namespace Personagens {


		class Jogador : public Personagem
		{
			private:
				int pontos;
				static const int id_base;

				bool segundo_jogador;
				

				bool estado_pulando;
				bool no_ar;
				bool estado_caindo;

				bool acelerando;
				
				float forca_de_impulso;
				//float gravidade;
				//float altura_de_pulo;


				//sf::Clock tempo;

			private:
				void setar_Figura();

			public:
				//Jogador();
				//Jogador(int semente, sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely);
				Jogador(sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely);
				~Jogador();

				void setar_Dois_Jogadores(bool jogador_dois);
				bool get_Dois_Jogadores();
				void executando_Pulo();

				void setar_No_Ar(bool no_meio_do_ar);
				void setar_Caindo(bool caindo);
				void setar_Bateu_A_Cabeca();
				void setar_Pode_Pular();

				bool get_Eliminado() const;
				int get_Pontuacao() const;

				void diminuir_Vitalidade(int dano);
				void colidir(Personagem* pAtacado);

				void aumentar_Pontuacao(int pontos_a_adicionar);

				void executar();
				void salvar();

		};
	}
}


//using namespace std;
//using namespace sf;

/*
namespace Entidades{
    namespace Personagens{
        class Jogador : public Personagem{
            private:
                int pontos;
                                
                float tempoTotal;

                // int dano_a_tomar;

                float cdDano;
                
                //bool pulo;
                bool podePular;

                bool status;

                sf::Vector2f velAtual;
            public:
                //Jogador(RectangleShape b, Vector2f pos, Vector2f tam, int life, int p);
                Jogador(int semente, sf::Vector2f pos, sf::Vector2f tam, int life, int p);

                ~Jogador();

                void salvar() override;

                void move(float dt) override;

                int getPontos();

                void setPular(bool p);

                bool getPular();

                const int getPontos()const;

                void colisao(Entidade* ent,sf::Vector2f inter);

                void colisao(Entidade* ent,float dt);

                void executar(float dt) override;

                void danificar(float dt);

        };
    }
}

*/
