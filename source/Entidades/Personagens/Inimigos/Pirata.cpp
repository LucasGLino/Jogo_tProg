#include "Entidades/Personagens/Inimigos/Pirata.h"

#include <cstdlib>
#include <ctime>

using namespace Entidades;
using namespace Personagens;

// Configura vida, raiva, patrulha e textura do pirata.
Pirata::Pirata()
{
	srand(static_cast<unsigned int>(time(0)));

	nivel_maldade = (rand() % 6);
	raiva = 0;
	num_vidas = 100;
	dano = 20;

	patrulha_esq_concluida = false;
	patrulha_dir_concluida = true;
	patrulhando = true;

	tamanho.x = 25.0f;
	tamanho.y = 55.0f;

	pos_inicial.x = 200.f;
	pos_inicial.y = 159.f;
	pos_final = pos_inicial;

	velocidade.x = 1.0f;
	velocidade_maxima = 2 * velocidade.x;

	pFigura->setSize(tamanho);
	if (!textura.loadFromFile("Assets/Imagens/Pirata_Inimigo.png")) {
		std::cout << "Erro ao carregar textura do Pirata Inimigo." << std::endl;
		pFigura->setFillColor(sf::Color::Red);
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
	pFigura->setPosition(pos_inicial);

	setar_Pontos_Por_Eliminacao(200);
}

// Nao precisa liberar nada alem do que a classe base ja cuida.
Pirata::~Pirata()
{
}

// Salvar ainda nao foi implementado para pirata.
void Pirata::salvar()
{
}

// Atualiza queda, desenho, movimento e bonus de raiva.
void Pirata::executar()
{
	executar_Gravidade();
	desenhar();
	setar_Pos(pos.x, pos.y);

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

	mover();
	bonus_De_Irritabilidade();
}

// Define as pontas onde o pirata vai patrulhar.
void Pirata::setar_Patrulha(float patrulha_esq, float patrulha_dir)
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

// Atualiza o destino da patrulha normal.
void Pirata::mover()
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

// Usa a raiva para curar, aumentar dano e acelerar o pirata.
void Pirata::bonus_De_Irritabilidade()
{
	dano += raiva;
	set_Vitalidade(get_Vitalidade() + (5 * raiva));
	velocidade.x += (nivel_maldade * 0.1f);

	if(velocidade.x >= velocidade_maxima){
		velocidade.x = velocidade_maxima;
	}

	raiva = 0;
}

// Jogador causa dano pelo lado fraco, senao toma dano e irrita o pirata.
void Pirata::danificar(int lado, Jogador* pJogador)
{
	if (lado == lado_fraco) {
		pJogador->colidir(static_cast<Personagem*>(this));

		if(get_Eliminado()){
			pJogador->aumentar_Pontuacao(pontos_de_eliminacao);
		}
	}
	else {
		pJogador->diminuir_Vitalidade(dano);
		raiva += 5;
	}
}

// Inverte o sentido da patrulha quando bate de lado.
void Pirata::colidiu_Obstaculo(int lado)
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

// Guarda a pontuacao dada ao jogador quando o pirata morre.
void Pirata::setar_Pontos_Por_Eliminacao(int pontos)
{
	pontos_de_eliminacao = pontos;
}
