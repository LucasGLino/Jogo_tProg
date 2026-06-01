#include"Entidade.h"

namespace Entidades {

    namespace Obstaculos{

        class Obstaculo : public Entidade {
        protected:

            bool danoso;
            
            int dano;

        public:
            Obstaculo(RectangleShape b, Vector2f pos,Vector2f tam, bool d) : Entidade(i, pos, b,tam), danoso(d)
            {
                
            }
            ~Obstaculo() {}

            bool getDanoso() { return dano; }

            void setDanoso(bool d) { this->dano = d; }
            
            int getDano() { return dano; }

            void setDano(int d);

            virtual void carregar() = 0;

            virtual void executar(float dt) = 0;

        };
    }
}