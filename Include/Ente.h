#pragma once

#include "Grafico.h"

#include<iostream>
#include<string>

using namespace std;

class Ent{
    private:

        int id;
        // ponteiro parar a sprite
        // e os ids de classes bases

        static Gerenciadores::GerenciadorGrafico* pGraf;
    public:

        Ent();
        ~Ent();

        Gerenciadores::GerenciadorGrafico* getPGG(){return pGraf;}

        virtual void executar() = 0;
}