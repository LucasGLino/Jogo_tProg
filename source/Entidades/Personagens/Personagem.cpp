#include "Entidades/Personagens/Personagem.h"

using namespace Entidades::Personagens;

// Comeca o personagem vivo e com a velocidade passada pela classe filha.
Personagem::Personagem(int semente, sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely):
    Entidade(semente, p, tam),
    num_vidas(vida)
{
    if (num_vidas < 0) {
        num_vidas = 0;
    }

    eliminado = (num_vidas <= 0);
    setar_velocidade(velx, vely);
}

// Nao precisa liberar nada alem do que a classe base ja cuida.
Personagem::~Personagem()
{
}

// Atualiza vidas e deixa eliminado coerente com o novo valor.
void Personagem::set_Vitalidade(int vida)
{
    num_vidas = vida;
    if (num_vidas < 0) {
        num_vidas = 0;
    }

    eliminado = (num_vidas <= 0);
}

// Retorna as vidas atuais.
int Personagem::get_Vitalidade() const
{
    return num_vidas;
}

// Tira vidas e elimina quando chegar em zero.
void Personagem::diminuir_Vitalidade(int dano)
{
    num_vidas -= dano;
    if(num_vidas <= 0){
        num_vidas = 0;
        eliminado = true;
    }
}

// Retorna se o personagem ja foi eliminado.
bool Personagem::get_Eliminado() const
{
    return eliminado;
}
