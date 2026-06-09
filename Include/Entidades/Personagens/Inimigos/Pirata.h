#pragma once
#include "Entidades/Personagens/Inimigos/Inimigo.h"

namespace Entidades {
    namespace Personagens {

        class Pirata : public Inimigo
        {
            private:
                int raiva;
                int regeneracao;

                bool patrulha_esq_concluida;
                bool patrulha_dir_concluida;
                bool patrulhando;

                float patrulha_esquerda;
                float patrulha_direita;

                float velocidade_maxima;

            public:
                Pirata();
                ~Pirata();
            
                void andar_ate(float em_x, float em_y);
                void Salvar();
                void Executar();
                void Danificar(Entidades::Personagens::Personagem* pAtacado);

                void setar_Patrulha(float patrulha_esq, float patrulha_dir);
                void patrulhar();
                void bonus_De_Irritabilidade();
                void verifica_Acao_de_Colisao(int lado, Entidades::Personagens::Jogador* pJogador);

                void setar_Pontos_Por_Eliminacao(int pontos);
        };
    }
}