#pragma once

#include"State.h"
#include"Fases/Fase_1.h"
#include"Fases/Fase_2.h"
#include"GerenciadorEstado.h"
#include"Estados/PauseEstado.h"
#include"Core/Jogo.h"

class Jogo;

class Fase_Estado : public Estado{
    private:
        int i;
        Jogo* pJogo;
        Gerenciador_Estado* pGe;
        bool Jogadores;
    public:
        Fase_Estado(Gerenciador_Estado* pGe,int i, bool j);
        ~Fase_Estado();
        void carregar() override {}
        void descarregar() override;
        void executar_fase();
        void cria_jogadores(); 
        void executar() override;
        void desenhar() override {}
        void voltarMenu(){ pGe->removerEstado();}
        void tratarInput() override;
};