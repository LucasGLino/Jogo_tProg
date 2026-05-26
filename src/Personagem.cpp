#include"../include/Personagem.h"

Entidades::Personagens::Personagem::Personagem(ID i, RectangleShape b, Vector2f p, Vector2f tam, int life, float velx, float vely, bool e): Entidade(i,p,b,tam), esq(e),vida(life), gravidade(1000.f), pulo(-500.f)
{
    setVel({velx,vely});
}

void Entidades::Personagens::Personagem::setPos(Vector2f p)
{    
    this->pos = p;

    body.setPosition(pos);

    desenho->setPosition({body.getPosition().x - 38.0f, body.getPosition().y - 46.0f});

}