#include"../include/Entidade.h"

Entidades::Entidade::Entidade(Vector2f p, RectangleShape corpo,Vector2f tam): Ent(), body(corpo), pos(p), size(tam), gravidade(1000.f)
{
    this->body.setSize(tam);
}

void Entidades::Entidade::setPos(Vector2f p){
    this->pos = p;
    body.setPosition(pos);
}