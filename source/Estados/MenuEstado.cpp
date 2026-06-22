#include "../../include/Estados/FaseEstado.h"


#define font "Assets/PermanentMarker-Regular.ttf"

using namespace std;
using namespace sf;

void Menu_Estado::carregar_Menu_externo()
{
    
    Vector2f posIniciar = {centroX, centroY - espacamento_altura}; 
    Botao* btnIniciar = new Botao("Iniciar Jogo", fMenu, posIniciar);
    Menu_externo.push_back(btnIniciar);

    Vector2f posOpcoes = {centroX, centroY}; 
    Botao* btnOpcoes = new Botao("Opcoes", fMenu, posOpcoes);
    Menu_externo.push_back(btnOpcoes);

    Vector2f posSair = {centroX, centroY + espacamento_altura}; 
    Botao* btnSair = new Botao("Sair", fMenu, posSair);
    Menu_externo.push_back(btnSair);

}
void Menu_Estado::carregar_Menu_Interno()
{
   
    Vector2f pos_1_Jogador = {centroX - espacamento_largura, centroY - espacamento_largura}; 
    btn_1_Jogador = new Botao("1 Jogador", fMenu, pos_1_Jogador);
    Menu_interno.push_back(btn_1_Jogador);

    Vector2f pos_2_Jogador = {centroX + espacamento_largura, centroY - espacamento_largura}; 
    btn_2_Jogador = new Botao("2 Jogadores", fMenu, pos_2_Jogador);
    Menu_interno.push_back(btn_2_Jogador);

    Vector2f pos_Fase_1 = {centroX - espacamento_largura, centroY}; 
    Botao* btn_Fase_1 = new Botao("Fase 1", fMenu, pos_Fase_1);
    Menu_interno.push_back(btn_Fase_1);

    Vector2f pos_Fase_2 = {centroX + espacamento_largura, centroY}; 
    Botao* btn_Fase_2 = new Botao("Fase 2", fMenu, pos_Fase_2);
    Menu_interno.push_back(btn_Fase_2);

    Vector2f posVoltar = {centroX + 200, centroY + 200}; 
    Botao* btnVoltar = new Botao("Voltar", fMenu, posVoltar);
    Menu_interno.push_back(btnVoltar);
}
Menu_Estado::Menu_Estado(Gerenciador_Estado *pGe): 
    Estado(pGe),
    Ente(200),
    pGe(pGe),
    espacamento_altura(100.f),
    espacamento_largura(200.f),
    centroX(pGG->getLarguraJanela() / 2.0f),
    centroY(pGG->getAlturaJanela() / 2.0f),
    menu(false)
{
    carregar();
    carregar_Menu_externo();
    carregar_Menu_Interno();
}
void Menu_Estado::carregar()
{
    if (!fMenu.loadFromFile(font)){
        cerr << "Erro ao carregar a fonte!" << std::endl;
        return;
    }    
}

void Menu_Estado::descarregar()
{
    descarregar_Menu_externo();
    descarregar_Menu_interno();
}

void Menu_Estado::descarregar_Menu_externo()
{
    for(vector<Botao*>::iterator it = Menu_externo.begin(); it != Menu_externo.end(); it++){
        if(*it){
            delete *it;
            *it = nullptr;
        }
    }
    Menu_externo.clear();
}

void Menu_Estado::descarregar_Menu_interno()
{
    for(vector<Botao*>::iterator it = Menu_interno.begin(); it != Menu_interno.end(); it++){
        if(*it){
            delete *it;
            *it = nullptr;
        }
    }
    Menu_interno.clear();
}

void Menu_Estado::executar()
{
    if(!menu){
        for(vector<Botao*>::iterator it = Menu_externo.begin(); it != Menu_externo.end(); it++){
            (*it)->executar();
        }
    }else{
        for(vector<Botao*>::iterator it = Menu_interno.begin(); it != Menu_interno.end(); it++){
            (*it)->executar();
        }
    }
    tratarInput();
    
}

void Menu_Estado::desenhar()
{
    sf::RenderWindow* window = pGG->getJanela();
    
    window->setView(window->getDefaultView());
    
    if(!menu){
        for(vector<Botao*>::iterator it = Menu_externo.begin(); it != Menu_externo.end(); it++){
            (*it)->desenhar();
        }
    }else{
        for(vector<Botao*>::iterator it = Menu_interno.begin(); it != Menu_interno.end(); it++){
            (*it)->desenhar();
        }
    }
    
}

void Menu_Estado::tratarInput()
{
    if(!menu){
        tratar_Input_Externo();
    }else{
        tratar_Input_Interno();
    }

}

void Menu_Estado::tratar_Input_Externo()
{
    for (size_t i = 0; i < Menu_externo.size(); ++i) {            
        Botao* b = Menu_externo[i];
        
        if (b->getPress()) {
                
            switch (i) { 
                case 0: 
                    menu = true;
                    break;
                case 1: 
                    std::cout << "Opções Clicadas!" << std::endl;
                    break;
                case 2:
                    std::cout << "teste" << std::endl;
                    // this->pGG->fechar();
                    break;
                default:
                    break;
            }
            return;
        }
    }
}

void Menu_Estado::tratar_Input_Interno()
{
    for (size_t i = 0; i < Menu_interno.size(); ++i) {            
        Botao* b = Menu_interno[i];
        
        if (b->getPress()) {
                
            switch (i) { 
                case 0:
                    btn_1_Jogador->set_troca_cor(true);
                    btn_2_Jogador->set_troca_cor(false);
                    dois_Jogadores = false;
                    break;
                case 1: 
                    btn_1_Jogador->set_troca_cor(false);
                    btn_2_Jogador->set_troca_cor(true);
                    dois_Jogadores = true;
                    break;
                case 2:
                    pGe->adicionarEstado(new Fase_Estado(this->pGe,0,dois_Jogadores));
                    break;
                case 3:
                    pGe->adicionarEstado(new Fase_Estado(this->pGe,1,dois_Jogadores));
                    break;
                case 4:
                    menu = false;
                    descarregar_Menu_interno();
                    break;
                default:
                    break;
            }
            return;
        }
    }
}
