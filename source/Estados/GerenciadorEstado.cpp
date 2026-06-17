#include "include/Estados/FaseEstado.h"

void Gerenciador_Estado::adicionarEstado(Estado *novoEstado)
{
    if(novoEstado == nullptr){
        return;
    }

    novoEstado->carregar();

    pilhaEstados.push(novoEstado);

}

void Gerenciador_Estado::removerEstado()
{
    if (pilhaEstados.empty()){
        return;
    }

    pilhaEstados.top()->descarregar(); 
    delete pilhaEstados.top();
    pilhaEstados.pop();
}
void Gerenciador_Estado::setEstado(Estado *novoEstado)
{
    if (novoEstado == nullptr) {
        return;    
    }

    if (!pilhaEstados.empty()) {
        
        removerEstado(); 
    }

    
    adicionarEstado(novoEstado);
}

void Gerenciador_Estado::limparPilha()
{
    while(!pilhaEstados.empty()) {
        removerEstado(); 
    }
}



void Gerenciador_Estado::executar()
{
    if (!pilhaEstados.empty()) {
        pilhaEstados.top()->executar();
    }
}

void Gerenciador_Estado::tratarInput()
{
    if (!pilhaEstados.empty()) {
        pilhaEstados.top()->tratarInput();
    }
}

void Gerenciador_Estado::desenhar()
{
    if (!pilhaEstados.empty()) {
        pilhaEstados.top()->desenhar();
    }
}
