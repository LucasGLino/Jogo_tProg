#include "../../include/Estados/FaseEstado.h"
#define font "../assets/PermanentMarker-Regular.ttf"

using namespace std;
using namespace sf;

void Menu_Estado::carregarBotoes()
{
    const float centroX = pGg->getLarguraJanela() / 2.0f;
    const float centroY = pGg->getAlturaJanela() / 2.0f;
    const float espacamento = 120.0f; 
    
    Vector2f posIniciar = {centroX, centroY - espacamento}; 
    Botao* btnIniciar = new Botao("Iniciar Jogo", fMenu, posIniciar);
    pBt.push_back(btnIniciar);

    Vector2f posOpcoes = {centroX, centroY}; 
    Botao* btnOpcoes = new Botao("Opcoes", fMenu, posOpcoes);
    pBt.push_back(btnOpcoes);

    Vector2f posSair = {centroX, centroY + espacamento}; 
    Botao* btnSair = new Botao("Sair", fMenu, posSair);
    pBt.push_back(btnSair);

}
Menu_Estado::Menu_Estado(Gerenciador_Estado *pGe): Estado(pGe),Ente(200),pGe(pGe){ 

    carregar();
}
void Menu_Estado::carregar()
{
    if (!fMenu.loadFromFile(font)){
        cerr << "Erro ao carregar a fonte!" << std::endl;
        return;
    }else{
        carregarBotoes();
    }

    
}

void Menu_Estado::descarregar()
{
    for(vector<Botao*>::iterator it = pBt.begin(); it != pBt.end(); it++){
        if(*it){
            delete *it;
            *it = nullptr;
        }
    }
    pBt.clear();
}

void Menu_Estado::executar()
{
    for(vector<Botao*>::iterator it = pBt.begin(); it != pBt.end(); it++){
        (*it)->executar();
    }
    tratarInput();
}

void Menu_Estado::desenhar()
{
    sf::RenderWindow* window = pGg->getJanela();
    
    window->setView(window->getDefaultView());
    
    for(std::vector<Botao*>::iterator it = pBt.begin(); it != pBt.end(); it++){
        (*it)->desenhar();
    }
    
}

void Menu_Estado::tratarInput()
{
    for (size_t i = 0; i < pBt.size(); ++i) {            
            Botao* b = pBt[i];
        
            if (b->getPress()) {
                
                switch (i) { 
                    case 0: 
                        
                        pGe->adicionarEstado(new Fase_Estado(this->pGe,1)); 
                        break;
                    case 1: 
                        std::cout << "Opções Clicadas!" << std::endl;
                        break;
                    case 2:
                        this->pGg->fechar();
                        break;
                    default:
                        break;
                }
                return;
            }
        }

}
