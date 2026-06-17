#include "Include/Entidades/Obstaculos/Baril.h"
#include "Baril.h"

Entidades::Obstaculos::Baril::Baril()
{
    srand(static_cast<unsigned int>(time(0)));

    danoso = true;

    dano_explisivo = (rand() % 20 + 10);
}
Entidades::Obstaculos::Baril::~Baril()
{
}

void Entidades::Obstaculos::Baril::Executar()
{
   if(ativa){
    desenhar();
   }
}

void Entidades::Obstaculos::Baril::obstacular(Entidades::Personagens::Jogador *p, int lado)
{
     if(lado == cima){
		p->diminuir_Vitalidade(dano_explisivo);
        ativa = false;
	}
}

void Entidades::Obstaculos::Baril::Salvar()
{
}
