#pragma once

#include "Entidades/Entidade.h"

namespace Entidades{
    namespace Personagens{
        class Personagem : public Entidade{
            protected:
                // Quantidade de vidas atual do personagem.
                int num_vidas;

                // Marca se o personagem ja saiu de jogo.
                bool eliminado;

                // Dano base usado nas interacoes com outros personagens.
                int dano;
                
            public:
                Personagem(int semente, sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely);
                virtual ~Personagem();

                // Troca as vidas e ajusta o estado de eliminacao.
                void set_Vitalidade(int vida);

                // Retorna a quantidade de vidas atual.
                int get_Vitalidade() const;

                // Aplica dano e elimina quando as vidas acabam.
                virtual void diminuir_Vitalidade(int dano);

                // Diz se o personagem ja foi eliminado.
                bool get_Eliminado() const;

                // Cada personagem decide como se movimenta.
                virtual void mover() = 0;

                // Salvar ainda nao foi implementado para personagem.
                virtual void salvar() = 0;
                
                // Cada personagem decide sua rotina por frame.
                virtual void executar() = 0;
        };
    }
}
