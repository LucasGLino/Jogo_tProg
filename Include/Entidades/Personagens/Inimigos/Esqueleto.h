#pragma once
#include "Entidades/Personagens/Inimigos/Inimigo.h"

namespace Entidades {
    namespace Personagens {

        class Esqueleto : public Inimigo
        {
            private:
                // Aumenta quando o esqueleto apanha e melhora o dano dele.
                int forca;

                // Estado da patrulha entre as pontas da plataforma ou chao.
                bool patrulha_esq_concluida;
                bool patrulha_dir_concluida;
                bool patrulhando;

                // Estado da investida depois que ele sobrevive a um ataque.
                bool preparando_investida;
                bool investindo;

                // Limites da patrulha.
                float patrulha_esquerda;
                float patrulha_direita;

                // Controle da investida.
                float velocidade_maxima;
                float pos_inicio_investida;
                int investidas_restantes;

                // Relogios usados para preparo da investida e pausas.
                sf::Clock relogio_investida;
                sf::Clock relogio_parada;

            public:
                Esqueleto();
                virtual ~Esqueleto();
            
                // Salvar ainda nao foi implementado para esqueleto.
                void salvar();

                // Atualiza gravidade, patrulha e investida.
                void executar();

                // Define os limites da patrulha.
                void setar_Patrulha(float patrulha_esq, float patrulha_dir);

                // Deixa o esqueleto mais forte depois de apanhar.
                void aumentar_Forca();

                // Trata colisao com jogador.
                void danificar(int lado, Entidades::Personagens::Jogador* pJogador);

                // Muda o sentido da patrulha ao bater em obstaculo.
                void colidiu_Obstaculo(int lado);

                // Entra no estado de preparo antes de investir.
                void preparar_Investida();

                // Decide a direcao da investida depois de levar dano.
                void iniciar_Investida_Apos_Dano(Entidades::Personagens::Jogador* pJogador);

                // Atualiza a patrulha normal.
                void mover();

                // Executa o preparo e o avanco da investida.
                void executar_Investida();

                // Volta da investida para a patrulha.
                void encerrar_Investida();

                // Sorteia pausas curtas durante a patrulha.
                void verificar_Parada();

                // Define quantos pontos o esqueleto vale.
                void setar_Pontos_Por_Eliminacao(int pontos);
        };
    }
}
