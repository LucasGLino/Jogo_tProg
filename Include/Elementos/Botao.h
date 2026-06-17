#pragma once

#include <SFML/Graphics.hpp>
#include"Gerenciadores/Gerenciador_Grafico.h"
#include<string>

class Botao{
    private:
        sf::RectangleShape botao;

        bool press;

        sf::Text str;

        sf::Color corBotao;

        sf::Color bHover;

        Gerenciadores::Gerenciador_Grafico* pGg;

        
     public:
        Botao(const std::string& stri, const sf::Font& fonte,sf::Vector2f pos);

        ~Botao();

        void desenhar();

        void hover();

        bool getPress();

        void executar();
};


