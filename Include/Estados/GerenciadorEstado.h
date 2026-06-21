#pragma once

#include"State.h"
#include"stack"
#include<iostream>

class Gerenciador_Estado
{
private:
    std::stack<Estado*> pilhaEstados;

public:
    Gerenciador_Estado(){}
    ~Gerenciador_Estado() { while(!pilhaEstados.empty()){removerEstado();} }

    void adicionarEstado(Estado* novoEstado);

    void removerEstado();

    void setEstado(Estado* novoEstado);

    void limparPilha();
    
    void executar();

    void tratarInput();

    void desenhar();
};