#pragma once
#include "Entidades/Personagens/Inimigos/Inimigo.h"

namespace Entidades {
    namespace Personagens {

        class Pirata : public Inimigo
        {
            private:
                // Aumenta quando o pirata bate no jogador pelo lado errado.
                int raiva;

                // Estado da patrulha entre as pontas da plataforma ou chao.
                bool patrulha_esq_concluida;
                bool patrulha_dir_concluida;
                bool patrulhando;

                // Limites da patrulha.
                float patrulha_esquerda;
                float patrulha_direita;

                // Limite para a velocidade ganhar bonus sem crescer sem fim.
                float velocidade_maxima;

            public:
                Pirata();
                virtual ~Pirata();
            
                // Salvar ainda nao foi implementado para pirata.
                void salvar();

                // Atualiza gravidade, patrulha e bonus de raiva.
                void executar();

                // Define os limites da patrulha.
                void setar_Patrulha(float patrulha_esq, float patrulha_dir);

                // Atualiza o destino da patrulha.
                void mover();

                // Aplica os bonus gerados pela raiva.
                void bonus_De_Irritabilidade();

                // Trata colisao com jogador.
                void danificar(int lado, Entidades::Personagens::Jogador* pJogador);

                // Muda o sentido da patrulha ao bater em obstaculo.
                void colidiu_Obstaculo(int lado);

                // Define quantos pontos o pirata vale.
                void setar_Pontos_Por_Eliminacao(int pontos);
        };
    }
}
