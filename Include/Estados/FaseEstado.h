#pragma once

#include"State.h"
#include"Fases/Fase_1.h"
#include"Fases/Fase_2.h"
#include"GerenciadorEstado.h"
#include"Estados/PauseEstado.h"
class Fase_Estado : public Estado{
    private:
        int i;
        Fases::Fase* pFase;
        Gerenciador_Estado* pGe;
    public:
        Fase_Estado(Gerenciador_Estado* pGe,int i);
        ~Fase_Estado();
        void carregar() override {}
        void descarregar() override;
        void criarFase();
        void proximaFase();
        void executar() override;
        void desenhar() override {}
        void voltarMenu(){ pGe->removerEstado();}
        void tratarInput() override;
};