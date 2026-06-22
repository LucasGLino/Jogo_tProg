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
    pFase(nullptr)
{
    pGe = new Gerenciador_Estado();
    pGe->setEstado(new Menu_Estado(this->pGe));
    
}




Jogo::~Jogo(){
    delete(pFase);
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

        Ger_Graf->limpar();

        pGe->executar();

        pGe->desenhar();

		Ger_Graf->mostrar();

    }
}
void Jogo::criar_fase_1()
{
    if(pFase){
        delete(pFase);
        pFase = new Fases::Fase_1();
    }else{
        pFase = new Fases::Fase_1();
    }
    
}

void Jogo::criar_fase_2()
{
    if(pFase){
        delete(pFase);
        pFase = new Fases::Fase_2();
    }else{
        pFase = new Fases::Fase_2();
    }
}

void Jogo::cria_jogador_1()
{
    jogador_1 = new Entidades::Personagens::Jogador(Vector2f(25.f, 20.f), Vector2f(20.f, 40.f), 100, 3.f, -5.f);
}

void Jogo::cria_jogador_2()
{
    jogador_2 = new Entidades::Personagens::Jogador(Vector2f(50.f, 20.f), Vector2f(20.f, 40.f), 100, 3.f, -5.f);
}

void Jogo::set_pJog2_Dois_Jogadores(bool valor)
{
    jogador_2->setar_Dois_Jogadores(valor);
}

bool Jogo::get_pJog2_Dois_Jogadores() {
    return jogador_2->get_Dois_Jogadores();
}

void Jogo::setar_Fase()
{
    if (pFase) {
        pFase->Setar_Jogadores(jogador_1, jogador_2);
        pFase->executar();
        jogador_1->executar();
        if (jogador_2 && jogador_2->get_Dois_Jogadores()) {
            jogador_2->executar();
        }
        std::cout << "passou"<< std::endl;

        if(pFase->verifica_Se_Caiu_No_Abismo(static_cast<Entidade*>(jogador_1))){
            jogador_1->diminuir_Vitalidade(200);
        }
        if(jogador_2 &&  pFase->verifica_Se_Caiu_No_Abismo(static_cast<Entidade*>(jogador_2))){
            jogador_2->diminuir_Vitalidade(200);
            
        }
        
	}
    std::cout << "saiu"<< std::endl;
}
void Jogo::atualiza_Camera()
{
    
    if(pFase){
       pFase->atualiza_Camera_Fase(jogador_1, jogador_2);
    }
}
void Jogo::verifica_Fim_De_Jogo()
{


    if(pFase){
        if (pFase->get_Ganhou() || (jogador_1->get_Eliminado() && jogador_2->get_Eliminado()))
        {
            
            std::cout << "pontuacao jogador 1:" << jogador_1->get_Pontuacao() << std::endl;
            std::cout << "pontuacao jogador 2:" << jogador_2->get_Pontuacao() << std::endl;

            
            delete(pFase);

            pGe->limparPilha(); 
            pGe->adicionarEstado(new Menu_Estado(pGe));
        }
    }
}
