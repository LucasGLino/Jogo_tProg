#include"../include/Personagem.h"

Entidades::Personagens::Personagem::Personagem(RectangleShape b, Vector2f p, Vector2f tam, int life, float velx, float vely, bool e): Entidade(p,b,tam), esq(e),vida(life), pulo(-500.f)
{
    setVel({velx,vely});
}
