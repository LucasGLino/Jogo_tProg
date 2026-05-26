#pragma once

#include"Personagem.h"


using namespace std;
using namespace sf;

namespace Entidades{
    namespace Personagens{
        class Jogador : public Personagem{
            private:
                int pontos;
                                
                float tempoTotal;

                // int dano_a_tomar;

                float cdDano;
                
                bool pulo;

                bool status;

                sf::Vector2f velAtual;
            public:
                Jogador(RectangleShape b, Vector2f pos, Vector2f tam, int life, int p);

                ~Jogador(){}

                void carregar() override;

                void move(float dt) override;

                int getPontos(){return pontos;}

                void setPular(bool p){this->pulo = p;}

                bool getPular(){return pulo;}

                const int getPontos()const {return pontos;}

                void colisao(Entidade* ent,sf::Vector2f inter);

                void colisao(Entidade* ent,float dt);

                void executar(float dt) override;

                void danificar(float dt);

        };
    }
}