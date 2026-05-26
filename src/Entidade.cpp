#include"../include/Entidade.h"

Entidades::Entidade::Entidade(Vector2f p, RectangleShape corpo,Vector2f tam): Ent(), body(corpo), pos(p), size(tam)
{
    this->body.setSize(tam);
}