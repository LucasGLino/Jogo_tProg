#include "Entidades/Projetil.h"
#include "Entidades/Personagens/Inimigos/Capitao.h"

using namespace Entidades;

/*
Projetil::Projetil(): Entidade(id_base) {
*/
Projetil::Projetil(): Entidade(id_base, sf::Vector2f(0.f, 0.f), sf::Vector2f(10.f, 15.f)) {

	//setId(semente_id_entidade);
	dano = 0;

	proprietario = nullptr;

	sf::Vector2f tamanho;
	tamanho.x = 10.f;
	tamanho.y = 15.f;

	atingiu_jogador = false;

	tempo_ativo = 0;
	tempo_de_vida = 180;

	pos.x = 0;
	pos.y = 0;

	ativo = false;
	lado = 0;
	velocidade.x = 0.5f;
	velocidade.y = 0.f;
	

	pFigura->setSize(tamanho);
	//pFigura->setFillColor(sf::Color(222, 120, 31));
	if (!textura.loadFromFile("assets/Projetil.png")) {
		std::cout << "Erro ao carregar textura do projetil." << std::endl;
		pFigura->setFillColor(sf::Color(222, 120, 31));
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
	pFigura->setPosition(pos.x, pos.y);
}


/*
Projetil::Projetil(float saida_x, float saida_y, int direcao) : Entidade(id_base) {
*/
Projetil::Projetil(float saida_x, float saida_y, int direcao) : Entidade(id_base, sf::Vector2f(saida_x, saida_y), sf::Vector2f(5.f, 10.f)) {

	//setId(semente_id_entidade);
	dano = 0;

	proprietario = nullptr;

	sf::Vector2f tamanho;
	tamanho.x = 5.f;
	tamanho.y = 10.f;

	tempo_ativo = 0;
	tempo_de_vida = 180;

	velocidade.x = 0.f;
	velocidade.y = 0.f;

	pos.x = saida_x;
	pos.y = saida_y;

	ativo = false;
	lado = direcao;

	pFigura->setSize(tamanho);
	//pFigura->setFillColor(sf::Color(222, 120, 31));
	if (!textura.loadFromFile("assets/Projetil.png")) {
		std::cout << "Erro ao carregar textura do projetil." << std::endl;
		pFigura->setFillColor(sf::Color(222, 120, 31));
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
	pFigura->setPosition(pos.x, pos.y);
}

Projetil::~Projetil(){

	ativo = false;
}

void Projetil::setar_Ativo(bool atv){
	ativo = atv;
}

void Projetil::setar_Dano(int dan){
	dano = dan;
}

void Projetil::setar_Direcao(int direcao) {
	lado = direcao;
}

void Entidades::Projetil::setar_Proprietario(Entidades::Entidade* propriet)
{
	proprietario = propriet;
}

int Projetil::get_Dano() {
	return dano;
}

bool Entidades::Projetil::get_Ativo()
{
	return ativo;
}

void Projetil::executar_Gravidade() {
	pos.y += gravidade;
	pos.y -= gravidade;
}

void Projetil::Executar() {

	setar_Pos(pos.x, pos.y);

	if (ativo) {

		//tempo_ativo++;

		if (lado == direita) {
			pos.x += velocidade.x;
		}
		else if (lado == cima) {
			pos.y -= velocidade.y;
		}
		else if (lado == esquerda) {
			pos.x -= velocidade.x;
		}
		else if (lado == baixo) {
			pos.y += velocidade.y;
		}

		desenhar();
	}
	else {

		//std::cout << "Projetil ID " << getId() << " inativo na pos (" << pos.x << "," << pos.y << ")" << std::endl;
	}

	/*
	if(tempo_ativo >= tempo_de_vida){
		ativo = false;
		tempo_ativo = 0;
	}
	*/
}

void Projetil::Salvar() {

}

void Projetil::executar() {
	Executar();
}

void Projetil::salvar() {
	Salvar();
}

void Projetil::Atingiu_Jogador(Entidades::Personagens::Jogador* pJogador)
{
	if(ativo){
		pJogador->diminuir_Vitalidade(dano);
	}
}

void Projetil::setar_Cor(sf::Color cor){

	pFigura->setFillColor(cor);
}

const int Projetil::id_base(10000);
