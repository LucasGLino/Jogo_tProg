#pragma once

#include<iostream>

#include"State.h"
#include"Elementos/Botao.h"
#include"vector"
#include"Entidades/Ente.h"
#include"Gerenciadores/Gerenciador_Grafico.h"
#include"GerenciadorEstado.h"
#include"FaseEstado.h"

class Menu_Estado : public Estado, public Ente
{
private:
    std::vector<Botao*> pBt;
    sf::Font fMenu;

    Gerenciador_Estado* pGe;

    void carregarBotoes();

public:
    Menu_Estado(Gerenciador_Estado* pGe);

    void carregar() override;
    void descarregar() override;
    void executar() override;
    void desenhar() override;
    void tratarInput() override;
};
