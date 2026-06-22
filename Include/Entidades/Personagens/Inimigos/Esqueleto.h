#pragma once
#include "Entidades/Personagens/Inimigos/Inimigo.h"

namespace Entidades {
    namespace Personagens {

        class Esqueleto : public Inimigo
        {
            private:
                int forca;

                bool patrulha_esq_concluida;
                bool patrulha_dir_concluida;
                bool patrulhando;

                float patrulha_esquerda;
                float patrulha_direita;

                float velocidade_maxima;

            public:
                Esqueleto();
                ~Esqueleto();
            
                void andar_ate(float em_x, float em_y);
                void salvar();
                void executar();
                void Danificar(Entidades::Personagens::Personagem* pAtacado);

                void setar_Patrulha(float patrulha_esq, float patrulha_dir);
                void patrulhar();
                void aumentar_Forca();
                void danificar(int lado, Entidades::Personagens::Jogador* pJogador);

                void setar_Pontos_Por_Eliminacao(int pontos);
        };
    }
}