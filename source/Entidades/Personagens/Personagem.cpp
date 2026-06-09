#include"Entidades/Personagens/Personagem.h"

using namespace Entidades::Personagens;
using namespace sf;

/*
Entidades::Personagens::Personagem::Personagem(RectangleShape b, Vector2f p, Vector2f tam, int life, float velx, float vely, bool e): Entidade(p,b,tam), esq(e),vida(life), pulo(-500.f)
{
    setVel({velx,vely});
}
*/

Personagem::Personagem(int semente, Vector2f p, Vector2f tam, int vida, float velx, float vely):
    Entidade(semente, p, tam),
    vitalidade(vida),
    pulo(-500.f)
{
    eliminado = false;
    //setVel({velx,vely});
    setar_Gravidade(1000.f);
    setar_velocidade(velx, vely);
}

Personagem::~Personagem()
{
}

int Personagem::getVida()
{
    return vitalidade;
}

void Personagem::set_Vitalidade(int vida)
{
    vitalidade = vida;
}

void Personagem::diminuir_Vida(int dano){

    vitalidade -= dano;
    if(vitalidade <= 0){
        vitalidade = 0;
        eliminado = true;
    }
}

int Personagem::get_Vitalidade()
{
    return vitalidade;
}

void Personagem::setar_Vitalidade(int vida)
{
    set_Vitalidade(vida);
}

void Personagem::diminuir_Vitalidade(int dano)
{
    diminuir_Vida(dano);
}

bool Personagem::get_Eliminado() const
{
    return eliminado;
}

void Personagem::danificar(Personagem* pAtacado)
{
    if(pAtacado){
        pAtacado->diminuir_Vitalidade(dano);
    }
}

void Personagem::move(float dt)
{
}

/*
void Entidades::Personagens::Personagem::setPos(Vector2f p)
{    
    this->pos = p;

    pFigura->setPosition(pos);
    //body.setPosition(pos);

    pFigura->setPosition({pFigura->getPosition().x - 38.0f, pFigura->getPosition().y - 46.0f});
    //body.setPosition({body.getPosition().x - 38.0f, body.getPosition().y - 46.0f});

}
*/
