//#include "Core/Jogo.h"
#include "Core/Jogo.h"
#include <iostream>

/*
int main{

    Jogo jogo;

    jogo.Executar();

    return 0;
}
*/

int main()
{
    //std::cout << "ERRO" << std::endl;
    
    Jogo* jogo = Jogo::getInstancia();

    jogo->executar();

    return 0;
}
