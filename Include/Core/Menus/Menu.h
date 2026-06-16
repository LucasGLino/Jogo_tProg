#pragma once

#include "Entidades/Ente.h"

class Jogo;

namespace Menus{

    class EstadoMenu;

    class Menu : public Ente {

        private:
            Jogo *pJogo;
            Menus::EstadoMenu* estado_atual;

            
            int estado;

        public:

            Menu();
            ~Menu();
            void executar();
            void mudar_Estado_Menu(int estad);


            void abrir_Menu_Principal();
            void abrir_Menu_NovoJogo();
            void abrir_Menu_Pause();
            void abrir_Menu_Ranking();
            void abrir_Menu_ResultadoPartida(bool venceu);

    };
}
