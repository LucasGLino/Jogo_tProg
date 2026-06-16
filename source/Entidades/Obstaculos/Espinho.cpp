#include "Entidades/Obstaculos/Espinho.h"


Entidades::Obstaculos::Espinho::Espinho()
{
    srand(static_cast<unsigned int>(time(0)));

    tetano = (rand() % 6);
}
Entidades::Obstaculos::Espinho::~Espinho()
{
}

void Entidades::Obstaculos::Espinho::Executar()
{
    if(ativa){

		desenhar();
	}
}

void Entidades::Obstaculos::Espinho::obstacular(Entidades::Personagens::Jogador *p, int lado)
{
    if(lado == baixo){
		p->diminuir_Vitalidade(10);
        int aux  = (rand() % 6);
        if(aux == tetano){
            p->diminuir_Vitalidade(5);
        }
	}
}

void Entidades::Obstaculos::Espinho::Salvar()
{
    Salvar();
}
