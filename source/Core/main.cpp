//#include "Core/Jogo.h"
#include "Core/Jogo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

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
    srand(time(NULL));
    
    Jogo* jogo = Jogo::getInstancia();

    jogo->executar();

    return 0;
}
