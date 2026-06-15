#include "Entidades/Personagens/Inimigos/Pirata.h"
#include <cstdlib>
#include <ctime>

using namespace Entidades;
using namespace Personagens;

Pirata::Pirata() {

	srand(static_cast<unsigned int>(time(0)));

	nivel_maldade = (rand() % 6);

	raiva = 0;

	//num_vitalidade = 100;
	vitalidade = 100;
	dano = 20;

	patrulha_esq_concluida = false;
	patrulha_dir_concluida = true;
	patrulhando = true;

	tamanho.x = 25.0;
	tamanho.y = 55.0;

	pos_inicial.x = 200.f;
	pos_inicial.y = 159.f;

	pos_final = pos_inicial;

	velocidade.x = 1.0f;

	velocidade_maxima = 2 * velocidade.x;

	//pFigura->setFillColor(sf::Color::Red);

	pFigura->setSize(tamanho);
	if (!textura.loadFromFile("assets/Esqueleto.png")) {
		std::cout << "Erro ao carregar textura do esqueleto." << std::endl;
		pFigura->setFillColor(sf::Color::Red);
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
	pFigura->setPosition(pos_inicial);

	setar_Pontos_Por_Eliminacao(200);
}

Pirata::~Pirata() {

}

void Pirata::executar() {

	desenhar();
	setar_Pos(pos.x, pos.y);

	if(!parar){
		if ((pos_final.x != pos.x) && (pos_final.y != pos.y)) {

			if (pos_final.x > pos.x) {
				pos.x += velocidade.x;
			}
			else if (pos_final.x < pos.x) {
				pos.x -= velocidade.x;
			}

		}
	}

	patrulhar();
	bonus_De_Irritabilidade();
}

void Pirata::Danificar(Personagem* pAtacado){

	pAtacado->diminuir_Vitalidade(dano);
}

void Pirata::andar_ate(float em_x, float em_y){

	pos_final.x = em_x;
	pos_final.y = em_y;
	
}

void Pirata::salvar() {

}

void Pirata::verifica_Acao_de_Colisao(int lado, Jogador* pJogador) {

	if (lado == lado_fraco) {
		pJogador->danificar(static_cast<Personagem*>(this));

		if(get_Eliminado()){
			pJogador->aumentar_Pontuacao(pontos_de_eliminacao);
		}
	}
	else {

		danificar(static_cast<Personagem*>(pJogador));
		raiva += 5;
	}
}

void Pirata::bonus_De_Irritabilidade(){

	dano += raiva;
	set_Vitalidade(get_Vitalidade() + (5 * raiva));
	//velocidade.x += (nivel_maldade*0,1);
	velocidade.x += (nivel_maldade * 0.1f);

	if(velocidade.x >= velocidade_maxima){
		velocidade.x = velocidade_maxima;
	}

	raiva = 0;
	regeneracao = 0;
}

void Pirata::setar_Patrulha(float patrulha_esq, float patrulha_dir){

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

void Pirata::patrulhar(){

	
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

void Pirata::setar_Pontos_Por_Eliminacao(int pontos){
	
	pontos_de_eliminacao = pontos;
}
