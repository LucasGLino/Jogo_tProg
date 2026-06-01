#pragma once

#include"Entidade.h"

using namespace std;
using namespace sf;

namespace Entidades{
    namespace Personagens{
        class Personagem : public Entidade{
            protected:
                int vida;

                Vector2f velo;

                bool esq;

                const float pulo; // velocidade do pulo
                
            public:
                Personagem(RectangleShape b, Vector2f p, Vector2f tam, int life, float velx, float vely,bool eo);
                
                virtual ~Personagem(){}

                int getVida(){return vida;}

                void setVida(int life){vida = life;}

                bool getEsq() const { return esq; }

                void setEsq(bool d) { esq = d; }

                virtual void colisao(Entidade* ent, sf::Vector2f inter) = 0;

                Vector2f getVel() {return velo;}

                void setVel(Vector2f v){velo = v;}

                virtual void move(float dt) = 0;

                virtual void carregar() = 0;
                
                virtual void executar(float dt) = 0;

        };
    }
}