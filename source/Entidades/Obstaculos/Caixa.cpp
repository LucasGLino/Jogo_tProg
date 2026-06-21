#include "Entidades/Obstaculos/Caixa.h"

Entidades::Obstaculos::Caixa::Caixa(): Mover_Esq(false), mover(false)
{
    densidade_superficial = 0.02f;

    velocidade.x = 1.f;
    velocidade.y = 1.f;
}
Entidades::Obstaculos::Caixa::~Caixa()
{
}

void Entidades::Obstaculos::Caixa::executar()
{
    desenhar();
    if(mover){
        if(Mover_Esq){
            Mover_Esquerda();
            mover = false;
        }else{
            Mover_Direita();
            mover = false;
        }
    }
}

void Entidades::Obstaculos::Caixa::obstacular(Entidades::Personagens::Jogador *p, int lado)
{
    
     if(lado == esquerda){
        mover = true; 
        Mover_Esq = true;
	}else if(lado == true){
        mover = true;
        Mover_Esq = false;
    }
    
}

void Entidades::Obstaculos::Caixa::Mover_Esquerda()
{
    for(int i = 0; i < 3; i++){
        pos.x -= velocidade.x;
    }
}

void Entidades::Obstaculos::Caixa::Mover_Direita()
{
    for(int i = 0; i < 3; i++){
        pos.x += velocidade.x;
    }    
}

void Entidades::Obstaculos::Caixa::salvar()
{
}
