#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

namespace Gerenciadores{
    
    class Gerenciador_Grafico{
        private:
            // Janela, evento e camera usados por todo o jogo.
            sf::RenderWindow* janela;

            sf::Event* evento;

            sf::View* camera;
            
            // Fonte padrao usada nos textos dos menus.
            sf::Font fonte;

            unsigned int largura;
            unsigned int altura; 

            // Instancia unica do gerenciador grafico.
            static Gerenciador_Grafico* pInstancia;

            Gerenciador_Grafico();

        public:
            ~Gerenciador_Grafico();

            // Controla a instancia unica do gerenciador grafico.
            static Gerenciador_Grafico* getInstancia();
            static void destruirInstancia();

            // Desenha elementos basicos do SFML na janela.
            void desenhar(sf::Sprite* corpo);
            void desenhar(sf::RectangleShape* aux);
            void desenhar(sf::Text* texto);

            // Configura fonte, texto e cor usados na interface.
            void setar_Fonte();
            sf::Text* setar_Texto(const std::string& texto, int tamanho, sf::Vector2f pos);
            void setar_Cor_Texto(sf::Text* texto, sf::Color cor);

            // Acessos diretos aos recursos graficos principais.
            sf::RenderWindow* getJanela() const;
            sf::View* getCamera() const;
            sf::Event* getEvent() const;

            // Operacoes basicas da janela.
            void limpar();
            bool isOpen() const;
            void centralizar(sf::Vector2f pos);

            unsigned int getLarguraJanela() const { return largura; }
            unsigned int getAlturaJanela() const { return altura; }

            void mostrar();
            void fechar();
    };
}
