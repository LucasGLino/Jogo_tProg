#pragma once

#include "Entidades/Ente.h"

//using namespace std;
//using namespace sf;

namespace Entidades 
{
    
    class Entidade: public Ente{
        protected:
            //sf::RectangleShape body;
            sf::Vector2f tamanho;
            sf::Texture textura;


            sf::Vector2f pos;
            sf::Vector2f aceleracao;
            sf::Vector2f velocidade;
            sf::Vector2f centro_glob;

            float gravidade;

            const int direita, cima, esquerda, baixo;

        public:
            Entidade(int semente, sf::Vector2f p, sf::Vector2f tam);
            
            virtual ~Entidade();

            float get_Gravidade() const;
            void setar_Gravidade(float grav);
            virtual void executar_Gravidade();

            sf::Vector2f get_Centro();

            sf::Vector2f get_Tamanho();
            float get_Largura();
            float get_Altura();

            float get_Comprimento_A();
            float get_Comprimento_L();

            sf::Vector2f getPos();
            float get_X() const;
            float get_Y() const;

            void setar_Pos(float pos_x, float pos_y);
            void setar_Pos(sf::Vector2f p);
            //virtual void setPos(sf::Vector2f p) = 0;

            void setar_velocidade(float vel_x, float vel_y);
            void setar_aceleracao(float ace_x, float ace_y);

            //sf::RectangleShape getBody();
            
            virtual void salvar() = 0;
            virtual void executar() = 0;
            //virtual void executar(float dt) = 0;
            
         };
}
