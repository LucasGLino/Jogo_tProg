#pragma once

#include "Entidades/Entidade.h"

namespace Entidades{
    namespace Personagens{
        class Personagem : public Entidade{
            protected:
            
                int vitalidade;
                bool eliminado;
                int dano;

                //Vector2f velo;

                //bool esq;

                //const float gravidade;

                const float pulo; // velocidade do pulo
                
            public:
                //Personagem(int semente, RectangleShape b, Vector2f p, Vector2f tam, int life, float velx, float vely,bool e);
                Personagem(int semente, sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely);

                virtual ~Personagem();

                //int getVida();

                void set_Vitalidade(int vida);

                //virtual void diminuir_Vida(int dano);

                int get_Vitalidade();

                //void setar_Vitalidade(int vida);

                virtual void diminuir_Vitalidade(int dano);

                bool get_Eliminado() const;

                virtual void danificar(Personagem* pAtacado);

                //bool getEsq() const { return esq; }

                //void setEsq(bool d) { esq = d; }

                //virtual void colisao(Entidade* ent, sf::Vector2f inter) = 0;

                //Vector2f getVel() {return velo;}

                //void setVel(Vector2f v){velo = v;}

                //virtual void move(float dt) = 0;
                virtual void move(float dt);

                virtual void salvar() = 0;
                
                //virtual void executar(float dt) = 0;
                virtual void executar() = 0;

                /*
                void setPos(Vector2f p);
                */
        };
    }
}
