#include "../../include/Estados/FaseEstado.h"

#define font "Assets/PermanentMarker-Regular.ttf"
using namespace sf;
using namespace std;
void Pause_Estado::carregarBotoes()
{

    const float centroX = pGG->getLarguraJanela() / 2.0f;
    const float centroY = pGG->getAlturaJanela() / 2.0f;
    const float espacamento = 120.0f; 
    
    Vector2f posVoltar = {centroX, centroY - espacamento}; 
    Botao* btnVoltar = new Botao("Voltar", fPause, posVoltar);
    pBt.push_back(btnVoltar);

    Vector2f posSair = {centroX, centroY + espacamento}; 
    Botao* btnSair = new Botao("Sair", fPause, posSair);
    pBt.push_back(btnSair);
    

}

Pause_Estado::Pause_Estado(Estado* anterior, Gerenciador_Estado *pGe): Estado(pGe),Ente(200), eAnterior(anterior), pGe(pGe)
{
}

void Pause_Estado::carregar()
{

    if (!fPause.loadFromFile(font)){

        return;
    }else{
        carregarBotoes();
    }


}

void Pause_Estado::descarregar()
{
    for(vector<Botao*>::iterator it = pBt.begin(); it != pBt.end(); it++){
        if(*it){
            delete *it;
            *it = nullptr;
        }
    }
    pBt.clear();
}

void Pause_Estado::executar()
{

    for(vector<Botao*>::iterator it = pBt.begin(); it != pBt.end(); it++){
        (*it)->executar();
    }
    tratarInput();
}

void Pause_Estado::desenhar()
{
    sf::RenderWindow* window = pGG->getJanela();

    if (eAnterior) {
        eAnterior->desenhar();
    }
    
    sf::View viewDoJogo = window->getView();

    window->setView(window->getDefaultView());
    
    for(vector<Botao*>::iterator it = pBt.begin(); it != pBt.end(); it++){
        (*it)->desenhar();
    }
    window->setView(viewDoJogo);
}

void Pause_Estado::tratarInput()
{
    for (size_t i = 0; i < pBt.size(); ++i) {            
            Botao* b = pBt[i];
        
            if (b->getPress()) {
                
                switch (i) { 
                    case 0: 
                        
                        pGe->removerEstado(); 
                        break;
                    case 1: 
                        pGe->limparPilha(); 
                        pGe->adicionarEstado(new Menu_Estado(pGe));
                        break;
                    default:
                        break;
                }
                return;
            }
        }
}
