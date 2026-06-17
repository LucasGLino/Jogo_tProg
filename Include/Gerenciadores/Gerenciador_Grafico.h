#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

//using namespace std;
//using namespace sf;

namespace Gerenciadores{
    
    class Gerenciador_Grafico{
        private:
            sf::RenderWindow* janela;

            sf::Event* evento;

            sf::View* camera;
            
            sf::Font fonte;

            unsigned int largura;
            unsigned int altura; 

            static Gerenciador_Grafico* pInstancia;

            Gerenciador_Grafico();

        public:
            ~Gerenciador_Grafico();

            static Gerenciador_Grafico* getInstancia();

            void desenhar(sf::Sprite* corpo);
            void desenhar(sf::RectangleShape* aux);
            void desenhar(sf::Text* texto);

            void setar_Fonte();
            sf::Text* setar_Texto(std::string texto, int tamanho, sf::Vector2f pos);
            void setar_Cor_Texto(sf::Text* texto, sf::Color cor);

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
