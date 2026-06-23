#include "Entidades/Personagens/Inimigos/Esqueleto.h"

#include <cstdlib>
#include <ctime>

using namespace Entidades;
using namespace Personagens;

// Configura vida, patrulha, investida e textura do esqueleto.
Esqueleto::Esqueleto()
{
	srand(static_cast<unsigned int>(time(0)));

	nivel_maldade = (rand() % 3);
	forca = 0;
	num_vidas = 80;
	dano = 5 * nivel_maldade;

	patrulha_esq_concluida = false;
	patrulha_dir_concluida = true;
	patrulhando = true;
	preparando_investida = false;
	investindo = false;

	tamanho.x = 25.0f;
	tamanho.y = 55.0f;

	pos_inicial.x = 200.f;
	pos_inicial.y = 159.f;
	pos_final = pos_inicial;

	velocidade.x = 0.5f;
	velocidade_maxima = 3 * velocidade.x;
	pos_inicio_investida = pos.x;
	investidas_restantes = 0;

	relogio_parada.restart();

	pFigura->setSize(tamanho);
	if (!textura.loadFromFile("Assets/Imagens/Esqueleto.png")) {
		std::cout << "Erro ao carregar textura do esqueleto." << std::endl;
		pFigura->setFillColor(sf::Color::Magenta);
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
	pFigura->setPosition(pos_inicial);

	setar_Pontos_Por_Eliminacao(400);
}

// Nao precisa liberar nada alem do que a classe base ja cuida.
Esqueleto::~Esqueleto()
{
}

// Salvar ainda nao foi implementado para esqueleto.
void Esqueleto::salvar()
{
}

// Atualiza queda, desenho, patrulha e investida.
void Esqueleto::executar()
{
	executar_Gravidade();
	desenhar();
	setar_Pos(pos.x, pos.y);

	if(preparando_investida || investindo){
		executar_Investida();
	}
	else {
		verificar_Parada();
		mover();

		if(!parar){
			if (pos_final.x != pos.x) {
				if (pos_final.x > pos.x) {
					pos.x += velocidade.x;
				}
				else if (pos_final.x < pos.x) {
					pos.x -= velocidade.x;
				}
			}
		}
	}
}

// Define as pontas onde o esqueleto vai patrulhar.
void Esqueleto::setar_Patrulha(float patrulha_esq, float patrulha_dir)
{
	if(rand()%2 == 1){
		patrulha_dir_concluida = false;
		patrulha_esq_concluida = true;
	}
	else{
		patrulha_dir_concluida = true;
		patrulha_esq_concluida = false;
	}

	patrulha_esquerda = patrulha_esq;
	patrulha_direita = patrulha_dir - get_Largura();
	patrulhando = true;
	parar = false;
}

// Aumenta o dano extra quando o esqueleto sobrevive a um ataque.
void Esqueleto::aumentar_Forca()
{
	forca += 5;
}

// Jogador causa dano pelo lado fraco, senao toma dano com bonus de forca.
void Esqueleto::danificar(int lado, Jogador* pJogador)
{
	if (lado == lado_fraco) {
		pJogador->colidir(static_cast<Personagem*>(this));
		aumentar_Forca();

		if(get_Eliminado()){
			pJogador->aumentar_Pontuacao(pontos_de_eliminacao);
		}
		else {
			iniciar_Investida_Apos_Dano(pJogador);
		}
	}
	else {
		pJogador->diminuir_Vitalidade(dano + forca);
	}
}

// Inverte o sentido da patrulha quando bate de lado.
void Esqueleto::colidiu_Obstaculo(int lado)
{
	if(lado == direita){
		patrulha_esq_concluida = false;
		patrulha_dir_concluida = true;
	}
	else if(lado == esquerda){
		patrulha_esq_concluida = true;
		patrulha_dir_concluida = false;
	}
}

// Comeca a preparacao antes da investida.
void Esqueleto::preparar_Investida()
{
	if(!preparando_investida && !investindo){
		preparando_investida = true;
		investindo = false;
		patrulhando = false;
		parar = true;
		pos_inicio_investida = pos.x;
		relogio_investida.restart();
	}
}

// Escolhe a direcao e prepara duas investidas seguidas.
void Esqueleto::iniciar_Investida_Apos_Dano(Jogador* pJogador)
{
	if(pJogador != nullptr && !preparando_investida && !investindo){
		if(pJogador->get_X() > pos.x){
			direcao = esquerda;
		}
		else{
			direcao = direita;
		}

		investidas_restantes = 2;
		preparar_Investida();
	}
}

// Atualiza o destino da patrulha normal.
void Esqueleto::mover()
{
	if(patrulhando) {
		if(!patrulha_esq_concluida && patrulha_dir_concluida){
			pos_final.x = patrulha_esquerda;
		}
		else if(patrulha_esq_concluida && !patrulha_dir_concluida){
			pos_final.x = patrulha_direita;
		}

		if(pos.x <= patrulha_esquerda){
			patrulha_esq_concluida = true;
			patrulha_dir_concluida = false;
		}
		else if(pos.x >= patrulha_direita ){
			patrulha_esq_concluida = false;
			patrulha_dir_concluida = true;
		}
	}
}

// Controla o tempo de preparo e o avanco rapido da investida.
void Esqueleto::executar_Investida()
{
	const float tempo_preparo_investida = 0.6f;
	const float distancia_maxima_investida = 140.f;

	if(preparando_investida){
		if(relogio_investida.getElapsedTime().asSeconds() >= tempo_preparo_investida){
			preparando_investida = false;
			investindo = true;
			parar = false;
		}
		return;
	}

	if(investindo){
		if(direcao == direita){
			pos.x += velocidade_maxima;
		}
		else if(direcao == esquerda){
			pos.x -= velocidade_maxima;
		}

		float distancia_percorrida = pos.x - pos_inicio_investida;
		if(distancia_percorrida < 0.f){
			distancia_percorrida *= -1.f;
		}

		if(distancia_percorrida >= distancia_maxima_investida || pos.x <= patrulha_esquerda || pos.x >= patrulha_direita){
			investidas_restantes--;

			if(investidas_restantes > 0){
				if(direcao == direita){
					direcao = esquerda;
				}
				else{
					direcao = direita;
				}

				preparando_investida = true;
				investindo = false;
				parar = true;
				pos_inicio_investida = pos.x;
				relogio_investida.restart();
			}
			else {
				encerrar_Investida();
			}
		}
	}
}

// Volta o esqueleto para a patrulha normal.
void Esqueleto::encerrar_Investida()
{
	preparando_investida = false;
	investindo = false;
	investidas_restantes = 0;
	patrulhando = true;
	parar = false;
	relogio_parada.restart();
}

// Sorteia pausas curtas para quebrar o movimento repetido.
void Esqueleto::verificar_Parada()
{
	const float intervalo_sorteio = 2.0f;
	const float duracao_parada = 0.7f;

	if(parar){
		if(relogio_parada.getElapsedTime().asSeconds() >= duracao_parada){
			parar = false;
			relogio_parada.restart();
		}
	}
	else {
		if(relogio_parada.getElapsedTime().asSeconds() >= intervalo_sorteio){
			int chance_parar = (rand() % 100);

			if(chance_parar <= 40){
				parar = true;
			}

			relogio_parada.restart();
		}
	}
}

// Guarda a pontuacao dada ao jogador quando o esqueleto morre.
void Esqueleto::setar_Pontos_Por_Eliminacao(int pontos)
{
	pontos_de_eliminacao = pontos;
}
