#pragma once

#include"State.h"
#include"Elementos/Botao.h"
#include"vector"
#include"Entidades/Ente.h"
#include"Gerenciadores/Gerenciador_Grafico.h"
#include"GerenciadorEstado.h"
#include"FaseEstado.h"
#include"MenuEstado.h"

class Pause_Estado : public Estado, public Ente{
    private: 
        Estado* eAnterior;
        
        std::vector<Botao*> pBt;

        sf::Font fPause;

        Gerenciador_Estado* pGe;

        void carregarBotoes();

    public:
        Pause_Estado(Estado* anterior, Gerenciador_Estado* pGe);
        
        void carregar() override;
        
        void descarregar() override;

        void executar() override;

        void desenhar() override;

        void tratarInput() override;
};