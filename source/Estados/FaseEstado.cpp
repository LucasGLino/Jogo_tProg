#include "Estados/FaseEstado.h"

Fase_Estado::Fase_Estado(Gerenciador_Estado* pGe,int i): Estado(nullptr), pGe(pGe) , i(i), fase(false), pFase(nullptr)
{
    if(!pFase){
        std::cout << "imprima algo" << std::endl;
    }
}

Fase_Estado::~Fase_Estado()
{
    
}

void Fase_Estado::descarregar()
{
    delete pFase;
}

void Fase_Estado::executar_fase()
{
    // switch (i) { 
    //        case 0:
    //             // std::cout << "entrou no switch case de fase" << std::endl;
    //             // // pJogo->get_Jogador_2()->setar_Dois_Jogadores(false);
    //             // // std::cout << "passou" << std::endl;
    //             // pFase = pJogo->get_fase_1();
    //             // std::cout << "saiu da criação da fase" << std::endl;
    //             // break;
    //         case 1:
    //             // pFase = pJogo->get_fase_2();
    //             // break;
    // }

}


void Fase_Estado::executar()
{
    executar_fase();
    std::cout << "esta para entrar em atualiza_Camera" << std::endl;
//     pJogo->atualiza_Camera(pFase);
//     pJogo->setar_Fase(pFase);
    
//     tratarInput();
//     if(pFase->get_Ganhou() || (pJogo->get_Jogador_1()->get_Eliminado() && pJogo->get_Jogador_2()->get_Eliminado())){
//         pGe->limparPilha(); 
//         pGe->adicionarEstado(new Menu_Estado(pGe));
//     }
}

void Fase_Estado::tratarInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        Pause_Estado* pPause = new Pause_Estado(this,pGe);
        pGe->adicionarEstado(pPause);
    }
}
