#pragma once

#include <SFML/Graphics.hpp>
#include"Gerenciadores/Gerenciador_Grafico.h"
#include<string>

class Botao{
    private:
        sf::RectangleShape botao;

        bool press;

        sf::Text str;

        sf::Texture corBotao;

        sf::Texture corBotao2;

        Gerenciadores::Gerenciador_Grafico* pGg;

        bool troca_cor;

        
     public:
        Botao(const std::string& stri, const sf::Font& fonte,sf::Vector2f pos);

        ~Botao();

        void desenhar();

        void hover();

        void hover_selecionado();

        void set_troca_cor(bool c);

        bool getPress();

        void executar();
};
