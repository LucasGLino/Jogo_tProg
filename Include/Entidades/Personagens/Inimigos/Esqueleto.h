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
                bool preparando_investida;
                bool investindo;

                float patrulha_esquerda;
                float patrulha_direita;

                float velocidade_maxima;
                float pos_inicio_investida;

                int investidas_restantes;

                sf::Clock relogio_investida;
                sf::Clock relogio_parada;

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
                void colidiu_Obstaculo(int lado);
                void preparar_Investida();
                void iniciar_Investida_Apos_Dano(Entidades::Personagens::Jogador* pJogador);
                void executar_Investida();
                void encerrar_Investida();
                void verificar_Parada();

                void setar_Pontos_Por_Eliminacao(int pontos);
        };
    }
}
