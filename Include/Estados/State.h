#pragma once
#include"Gerenciadores/Gerenciador_Grafico.h"

class Gerenciador_Estado;

class Estado{
    protected:
        Gerenciador_Estado* pGerenciador;
    
        Gerenciadores::Gerenciador_Grafico* pGg;
    public:
        Estado(Gerenciador_Estado* pGe): pGerenciador(pGe){pGg = Gerenciadores::Gerenciador_Grafico::getInstancia();}
        virtual ~Estado() = default;

        virtual void carregar() = 0;
        virtual void descarregar() = 0;
        virtual void executar() = 0; 
        virtual void desenhar() = 0;   
        virtual void tratarInput() = 0;

};