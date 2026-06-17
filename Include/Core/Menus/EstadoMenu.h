#pragma once

//#include "Core/Menus/Menu.h"
#include "Entidades/Ente.h"
#include <vector>
#include <string>


namespace Menus{

    class Menu;

    //essa calsse tem como objetivo fazer o state persi, para passar ao
    //context (menu) selecionar e executar o estado necessário de menu
    //menuPause, menuPrincipal e etc...
    class EstadoMenu : public Ente{

        protected:
            Menu* pMenu;

            std::vector<std::string> opcoes;
            std::vector<sf::Text*> textos;

            int selecionado;


        public:

            EstadoMenu(Menu* ponteiro_menu);
            ~EstadoMenu();

            
            virtual void executar();
            virtual void processar_Evento(sf::Event &evento);
            virtual void confirmar_Opcao() = 0; 

            
            void desenhar_Menu();
            void subir();
            void descer();
            void adicionar_Opcao(const std::string &opcao);
    };
}