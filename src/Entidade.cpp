#include"../include/Entidade.h"

Entidades::Entidade::Entidade(ID i, Vector2f p, RectangleShape corpo,Vector2f tam): Ent(EntID::entidade), id(i), body(corpo), pos(p), size(tam)
{
    this->body.setSize(tam);
}