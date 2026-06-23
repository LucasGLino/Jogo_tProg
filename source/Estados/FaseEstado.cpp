#include "Estados/FaseEstado.h"

Fase_Estado::Fase_Estado(Gerenciador_Estado* pGe,int i, bool j): Estado(nullptr), pGe(pGe) , i(i),Jogadores(j)
{
    pJogo = pJogo->getInstancia();
    cria_jogadores();
    executar_fase();
}

Fase_Estado::~Fase_Estado()
{
    
}

void Fase_Estado::descarregar()
{
}

void Fase_Estado::executar_fase()
{
    switch (i) { 
           case 0:
                pJogo->criar_fase_1();
                break;
            case 1:
                pJogo->criar_fase_2();
                break;
    }

}

void Fase_Estado::cria_jogadores()
{
    if(!Jogadores){
        pJogo->cria_jogador_1();
        pJogo->set_pJog2_Dois_Jogadores(Jogadores);
    }else{
        pJogo->cria_jogador_1();
        pJogo->cria_jogador_2();
        pJogo->set_pJog2_Dois_Jogadores(Jogadores);
    }
}

void Fase_Estado::executar()
{
    pJogo->atualiza_Camera();
    pJogo->setar_Fase();
    
    tratarInput();
    pJogo->verifica_Fim_De_Jogo();
}

void Fase_Estado::desenhar()
{
}
void Fase_Estado::tratarInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        Pause_Estado* pPause = new Pause_Estado(this,pGe);
        pGe->adicionarEstado(pPause);
    }
}
