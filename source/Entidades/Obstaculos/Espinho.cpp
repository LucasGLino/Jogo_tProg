#include "Entidades/Obstaculos/Espinho.h"


Entidades::Obstaculos::Espinho::Espinho(): enferrujado(false), dano_tetano(5), Jog_tetano(false), intervalo_tetano(0.5f), max_danos_tetano(3), contador_dano(0), pJog(nullptr)
{

    densidade_superficial = 0.05f;

    //srand(static_cast<unsigned int>(time(0)));

    danoso = true;

    danosidade =  (rand() % 5 + 5);

    if(rand()%3){
        enferrujado = true;
    }

    clock.restart();
}

Entidades::Obstaculos::Espinho::~Espinho()
{

}

void Entidades::Obstaculos::Espinho::executar()
{
    desenhar();
    executar_Gravidade();
    setar_Pos(pos.x,pos.y);
    
    if(Jog_tetano){
        Tetano_Danar();
    }

}

void Entidades::Obstaculos::Espinho::obstacular(Entidades::Personagens::Jogador *pJogador, int lado)
{
    if(lado == baixo){

        pJogador->setar_Pode_Pular();
        pJogador->executando_Pulo();
		pJogador->diminuir_Vitalidade(danosidade);
        
        if(enferrujado == true && !Jog_tetano){
            Jog_tetano = true;
            pJog = pJogador;
            contador_dano = 0;
            clock.restart();
        }
	}
}

void Entidades::Obstaculos::Espinho::Tetano_Danar()
{
    if(pJog == nullptr){
        contador_dano = 0;
        Jog_tetano = false;
        return;
    }

    if(contador_dano >= max_danos_tetano){
        pJog = nullptr;
        contador_dano = 0;
        Jog_tetano = false;
        return;
    }

    if(clock.getElapsedTime().asSeconds() >= intervalo_tetano){
        pJog->diminuir_Vitalidade(dano_tetano);
        contador_dano++;
        clock.restart();
    }
   
}

void Entidades::Obstaculos::Espinho::salvar()
{

}
