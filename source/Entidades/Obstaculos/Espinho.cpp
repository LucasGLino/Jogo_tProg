#include "Entidades/Obstaculos/Espinho.h"
#include <cstdlib>


void Entidades::Obstaculos::Espinho::aplicar_Dano_Tetano()
{
    // Mantem o dano do tetano rodando por tempo limitado no jogador atingido.
    if(pJogador_tetano == nullptr){
        contador_dano = 0;
        tetano_ativo = false;
        return;
    }

    if(contador_dano >= max_danos_tetano){
        pJogador_tetano = nullptr;
        contador_dano = 0;
        tetano_ativo = false;
        return;
    }

    if(relogio_tetano.getElapsedTime().asSeconds() >= intervalo_tetano){
        pJogador_tetano->diminuir_Vitalidade(dano_tetano);
        contador_dano++;
        relogio_tetano.restart();
    }
}


Entidades::Obstaculos::Espinho::Espinho():
    enferrujado(false),
    danosidade(0),
    dano_tetano(5),
    relogio_tetano(),
    tetano_ativo(false),
    intervalo_tetano(0.5f),
    max_danos_tetano(3),
    contador_dano(0),
    pJogador_tetano(nullptr)
{
    // Define a massa do espinho e sorteia seu dano principal.
    densidade_superficial = 0.05f;
    danosidade =  (rand() % 5 + 5);

    // Alguns espinhos ficam enferrujados e podem causar tetano.
    if(rand()%3){
        enferrujado = true;
    }

    relogio_tetano.restart();
}

Entidades::Obstaculos::Espinho::~Espinho()
{

}

void Entidades::Obstaculos::Espinho::executar()
{
    // Atualiza a fisica normal do obstaculo e processa o tetano se existir.
    desenhar();
    executar_Gravidade();
    setar_Pos(pos.x,pos.y);
    
    if(tetano_ativo){
        aplicar_Dano_Tetano();
    }

}

void Entidades::Obstaculos::Espinho::obstacular(Entidades::Personagens::Jogador *pJogador, int lado)
{
    if(lado == baixo){
        // O espinho sempre machuca ao pisar e permite que o jogador pule de novo.
        pJogador->setar_Pode_Pular();
        pJogador->executando_Pulo();
		pJogador->diminuir_Vitalidade(danosidade);
        
        // O tetano comeca uma vez e continua sendo tratado no executar.
        if(enferrujado == true && !tetano_ativo){
            tetano_ativo = true;
            pJogador_tetano = pJogador;
            contador_dano = 0;
            relogio_tetano.restart();
        }
	}
}

void Entidades::Obstaculos::Espinho::salvar()
{
    // Salvar ainda nao foi implementado para espinho.
}
