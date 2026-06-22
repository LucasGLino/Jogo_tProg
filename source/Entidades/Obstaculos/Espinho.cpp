#include "Entidades/Obstaculos/Espinho.h"


Entidades::Obstaculos::Espinho::Espinho(): tetano(false), dano_tetano(5), Jog_tetano(false), pJog(nullptr), contador_dano(0)
{

    densidade_superficial = 0.05f;

    srand(static_cast<unsigned int>(time(0)));

    danoso = true;

    danosidade =  (rand() % 5 + 5);

    int aux = (rand() % 6);

    if(aux == 3){
        tetano = true;
    }

    dt = clock.restart().asSeconds();
}

Entidades::Obstaculos::Espinho::~Espinho()
{

}

void Entidades::Obstaculos::Espinho::executar()
{

    desenhar();
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
        
        if(tetano == true){
            Jog_tetano = true;
            pJog = pJogador;
        }
	}
}

void Entidades::Obstaculos::Espinho::Tetano_Danar()
{
     static float tempo = 0.f;

    const float Tempo_Ataque = 0.5f;


    if(tempo > 0.f){
        tempo -= dt;
        if(contador_dano == 3){
            pJog = nullptr;
            contador_dano = 0;
            Jog_tetano = false;
        }
    }else if(tempo <= 0.f){
        tempo = Tempo_Ataque;
        pJog->diminuir_Vitalidade(dano_tetano);
        contador_dano++;
    }
   
}

void Entidades::Obstaculos::Espinho::salvar()
{

}
