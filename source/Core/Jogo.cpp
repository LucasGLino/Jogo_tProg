#include "Core/Jogo.h"


using namespace sf;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Personagens;

Jogo* Jogo::pInstancia = NULL;

Jogo::Jogo():
    Ger_Graf(Gerenciador_Grafico::getInstancia()),
    jogador_1(nullptr),
    jogador_2(nullptr),
    fase1(nullptr),
    fase2(nullptr)
{
    pGe = new Gerenciador_Estado();
    pGe->setEstado(new Menu_Estado(this->pGe));
    
    if(jogador_1 == nullptr){
        std::cout << "mostra algo 1" << std::endl;
    }
    if(jogador_2 == nullptr){
        std::cout << "mostra algo 2" << std::endl;
    }
    if(fase1 == nullptr){
        std::cout << "mostra algo 3" << std::endl;
    }
    if(fase2 == nullptr){
        std::cout << "mostra algo 4" << std::endl;
    }
    executar();
}




Jogo::~Jogo(){
    delete(fase1);
    delete(fase2); 
    delete(jogador_1);
    delete(jogador_2);
    delete(pGe);

}

Jogo *Jogo::getInstancia()
{
    if(pInstancia == NULL){
        pInstancia = new Jogo();
    }
    return pInstancia;
}

void Jogo::executar()
{
    while (Ger_Graf->getJanela()->isOpen())
    {
        
        Event evento;

        Ger_Graf->getJanela()->setFramerateLimit(60);


        while (Ger_Graf->getJanela()->pollEvent(evento))
        {
                if (evento.type == Event::Closed) {
                    Ger_Graf->getJanela()->close();
                }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            // deve ser modificado para encaixar o menu de pause.
            Ger_Graf->getJanela()->close();
        }

        pGe->executar();

		Ger_Graf->limpar();

        pGe->desenhar();

		Ger_Graf->mostrar();

    }
}
