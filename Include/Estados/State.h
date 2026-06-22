#pragma once


class Gerenciador_Estado;

class Estado{
    protected:
        Gerenciador_Estado* pGerenciador;
    
    
    public:
        Estado(Gerenciador_Estado* pGe): pGerenciador(pGe){}
        virtual ~Estado() = default;

        virtual void carregar() = 0;
        virtual void descarregar() = 0;
        virtual void executar() = 0; 
        virtual void desenhar() = 0;   
        virtual void tratarInput() = 0;

};