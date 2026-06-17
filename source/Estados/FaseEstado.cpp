#include "Estados/FaseEstado.h"

Fase_Estado::Fase_Estado(Gerenciador_Estado* pGe,int i): Estado(nullptr),pGe(pGe) , i(i)
{
    criarFase();
}

Fase_Estado::~Fase_Estado()
{
}

void Fase_Estado::descarregar()
{
    delete pFase;
}

void Fase_Estado::criarFase()
{
    switch (i) { 
        case 0:            
            
        case 1: 
            
        case 2:
           
    }

}

void Fase_Estado::proximaFase()
{
    pGe->removerEstado(); 
        
        
    pGe->adicionarEstado(new Fase_Estado(pGe, 1));
}

void Fase_Estado::executar()
{
    // pFase->executar(); 
    // tratarInput();
    // if(pFase->getFinalizar()){
    //     pGe->limparPilha(); 
    //     pGe->adicionarEstado(new Menu_Estado(pGe));
    // }
}

void Fase_Estado::tratarInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        Pause_Estado* pPause = new Pause_Estado(this,pGe);
        pGe->adicionarEstado(pPause);
    }
}
