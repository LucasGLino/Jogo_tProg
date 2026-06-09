#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

//using namespace std;
//using namespace sf;

namespace Gerenciadores{
    
    class Gerenciador_Grafico{
        private:
            sf::RenderWindow* janela;

            sf::Event* evento;

            sf::View* camera;
            
            unsigned int largura;
            unsigned int altura; 

            static Gerenciador_Grafico* pInstancia;

            Gerenciador_Grafico();

        public:
            ~Gerenciador_Grafico();

            static Gerenciador_Grafico* getInstancia();

            void desenhar(sf::Sprite* corpo);
            void desenhar(sf::RectangleShape aux);
            void desenhar(sf::Text* texto);

            sf::RenderWindow* getJanela()const;
            sf::View* getCamera() const;
            sf::Event* getEvent() const;


            void limpar();
            bool isOpen()const;
            void centralizar(sf::Vector2f pos);


            unsigned int getLarguraJanela()const{return largura;}
            unsigned int getAlturaJanela()const{return altura;}

            void mostrar();
            void fechar();
    };
}
