#include "Core/Jogo.h"

using namespace sf;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Personagens;

Jogo::Jogo():
    Ger_Graf(Gerenciador_Grafico::getInstancia()),
    jogador_1(Vector2f(50.f, 20.f), Vector2f(20.f, 40.f), 100, 3.f, -5.f),
    jogador_2(Vector2f(25.f, 0.f), Vector2f(20.f, 40.f), 100, 3.f, -5.f),
    fase_1_ativa(false),
    fase_2_ativa(false),
    acabou(false)
{

    //estado Menu;
    estado = 1;

    jogador_2.setar_Dois_Jogadores(false);

    //Ger_Graf = ::Gerenciador_Grafico::getInstancia();
    Ger_Graf = Gerenciador_Grafico::getInstancia();

    //inicialação das fases corrigida, agora função Atualiza chama setar_Fase quando necessário
    fase_1_ativa = true;
    fase_2_ativa = false;

    fase1.Setar_Jogadores(&jogador_1, &jogador_2);
    fase2.Setar_Jogadores(&jogador_1, &jogador_2);


}

Jogo::~Jogo(){

}

void Jogo::set_pJog2_Dois_Jogadores(bool valor) {
    jogador_2.setar_Dois_Jogadores(valor);
}

bool Jogo::get_pJog2_Dois_Jogadores() {
    return jogador_2.get_Dois_Jogadores();
}



void Jogo::executar(){

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


        if(fase_1_ativa){
            atualiza_Camera();
            setar_Fase();

            verifica_Fim_De_Jogo();
        }
        else if(fase_2_ativa){
            atualiza_Camera();
            setar_Fase();

            verifica_Fim_De_Jogo();
        }
        
        //EstadoDoJogo();

        Ger_Graf->mostrar();

        /*
        if(fase_1_ativa) {
            
            if (fase1.get_Ganhou()) {
                Ger_Graf->getJanela()->close();
            }
        }
        else if (fase_2_ativa) {

            if (fase2.get_Ganhou()) {
                Ger_Graf->getJanela()->close();
            }
        }
        */
    }
}


void Jogo::setar_Fase()
{
    //garante que os jogadores sejam setados
    //jogador_1.executar();
    //if (jogador_2.get_Dois_Jogadores()) {
    //    jogador_2.executar();
    //}

    //seta os jogadores na fase ativa
    if (fase_1_ativa) {
       //fase1.Setar_Jogadores(&jogador_1, &jogador_2);
        fase1.executar();

        jogador_1.executar();
        if (jogador_2.get_Dois_Jogadores()) {
            jogador_2.executar();
        }

        if(fase1.verifica_Se_Caiu_No_Abismo(static_cast<Entidade*>(&jogador_1))){
            jogador_1.diminuir_Vitalidade(200);
        }
        if(fase1.verifica_Se_Caiu_No_Abismo(static_cast<Entidade*>(&jogador_2))){
            jogador_2.diminuir_Vitalidade(200);
        }
        
	}
    else if (fase_2_ativa) {
    
//    if(fase_2_ativa){
        //fase2.Setar_Jogadores(&jogador_1, &jogador_2);
        fase2.executar();

        jogador_1.executar();
        if (jogador_2.get_Dois_Jogadores()) {
            jogador_2.executar();
        }

        if(fase2.verifica_Se_Caiu_No_Abismo(static_cast<Entidade*>(&jogador_1))){
            jogador_1.diminuir_Vitalidade(200);
        }
        if(fase2.verifica_Se_Caiu_No_Abismo(static_cast<Entidade*>(&jogador_2))){
            jogador_2.diminuir_Vitalidade(200);
        }
	}
}


void Jogo::verifica_Fim_De_Jogo()
{


    if(fase_1_ativa){
        if (fase1.get_Ganhou() || (jogador_1.get_Eliminado() && jogador_2.get_Eliminado()))
        {
            
            std::cout << "pontuacao jogador 1:" << jogador_1.get_Pontuacao() << std::endl;
            std::cout << "pontuacao jogador 2:" << jogador_2.get_Pontuacao() << std::endl;

            Ger_Graf->getJanela()->close();
            acabou = true;
        }
    }else if(fase_2_ativa){
    // if(fase_2_ativa){
        if (fase2.get_Ganhou() || (jogador_1.get_Eliminado() && jogador_2.get_Eliminado()))
        {
            std::cout << "pontuacao jogador 1:" << jogador_1.get_Pontuacao() << std::endl;
            std::cout << "pontuacao jogador 2:" << jogador_2.get_Pontuacao() << std::endl;

            Ger_Graf->getJanela()->close();
			acabou = true;
        }
	}
}

void Jogo::atualiza_Camera() {

    if(fase_1_ativa){
       fase1.atualiza_Camera_Fase(&jogador_1, &jogador_2);
    }
    else if(fase_2_ativa){
        fase2.atualiza_Camera_Fase(&jogador_1, &jogador_2);
    }

    Ger_Graf->getJanela()->setView(*Ger_Graf->getCamera());

    //isso deve ser passado para a fase, que deve ajustar a camera conforme o jogador se move pelo mapa.
    //Ger_Graf->getCamera()->setCenter(jogador_1.get_Centro());

}
