#include"Ente.h"

using namespace std;
using namespace sf;

namespace Entidades 
{
    
    class Entidade: public Ente{
        protected:
            RectangleShape body;

            Vector2f pos;

            Vector2f size;
        
            Texture textura;
        public:
            Entidade(Vector2f p, RectangleShape corpo, Vector2f tam);
            
            virtual ~Entidade(){}

            RectangleShape getBody(){return body;}
            
            virtual void setPos(Vector2f p) = 0;

            ID getId()const{return id;}

            Vector2f getPos(){return pos;}

            Vector2f getSize(){return size;}
            
            virtual void carregar() = 0;

            virtual void executar(float dt) = 0;
            
         };
}