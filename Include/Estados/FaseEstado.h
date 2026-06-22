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
        Fases::Fase* pFase;
        Gerenciador_Estado* pGe;
        bool fase; // se false fase 1 se true fase 2
    public:
        Fase_Estado(Gerenciador_Estado* pGe,int i);
        ~Fase_Estado();
        void carregar() override {}
        void descarregar() override;
        void executar_fase(); 
        // void proximaFase();
        void executar() override;
        void desenhar() override {}
        void voltarMenu(){ pGe->removerEstado();}
        void tratarInput() override;
};