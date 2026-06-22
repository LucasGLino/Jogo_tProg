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
    std::vector<Botao*> Menu_externo;
    sf::Font fMenu;

    Gerenciador_Estado* pGe;
    std::vector<Botao*> Menu_interno;
    Botao* btn_1_Jogador;
    Botao* btn_2_Jogador;

    bool menu; // se true executa o menu interno se false o menu externo

    bool dois_Jogadores;
    const float centroX;
    const float centroY;
    const float espacamento_altura; 
    const float espacamento_largura;


    void carregar_Menu_externo();
    void carregar_Menu_Interno();

public:
    Menu_Estado(Gerenciador_Estado* pGe);

    void carregar() override;
    void descarregar() override;
    void descarregar_Menu_externo();
    void descarregar_Menu_interno();
    void executar() override;
    void desenhar() override;
    void tratarInput() override;
    void tratar_Input_Externo();
    void tratar_Input_Interno();
};
