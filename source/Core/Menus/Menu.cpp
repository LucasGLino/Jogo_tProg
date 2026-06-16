#include "Core/Menus/Menu.h"
#include "Core/Menus/EstadoMenu.h"


#include "Core/Jogo.h"


using namespace sf;
using namespace Menus;


Menu::Menu() : Ente(0){


}

Menu::~Menu(){


}

void Menu::executar(){


    if(estado_atual!=NULL){
        estado_atual->executar();
    }

}

void Menu::mudar_Estado_Menu(int estad){

    if(estado != estad){

        estado = estad;
        delete estado_atual;

        if(estado == 0 ){

            estado_atual = nullptr;
        }
        if(estado == 1){

            abrir_Menu_Principal();
        }
        else if(estado == 2){

            abrir_Menu_Pause();
        }
        else if(estado == 3){

            abrir_Menu_ResultadoPartida(true);
        }
        else if(estado == 4){

            abrir_Menu_ResultadoPartida(false);
        }
    }
}

//deve apenas instanciar o menu principal;
void Menu::abrir_Menu_Principal(){


}

//deve ser solicitado dentro do concrete state (NovoJogo)
void Menu::abrir_Menu_NovoJogo(){

}

//deve apenas intanciar o estadoPause;
void Menu::abrir_Menu_Pause(){

}

//deve ser solicitado pelo estadoPrincipal
void Menu::abrir_Menu_Ranking(){


}

//deve apenas instanciar o estadoPrincipal
void Menu::abrir_Menu_ResultadoPartida(bool venceu){


}


