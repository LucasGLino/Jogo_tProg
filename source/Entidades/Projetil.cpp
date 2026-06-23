#include "Entidades/Projetil.h"
#include "Entidades/Personagens/Jogador/Jogador.h"

using namespace Entidades;

const int Projetil::id_base(10000);

// Inicializa o projetil inativo ate ser configurado pelo capitao.
Projetil::Projetil(): Entidade(id_base, sf::Vector2f(0.f, 0.f), sf::Vector2f(10.f, 15.f))
{
	dano = 0;
	ativo = false;
	lado = 0;

	velocidade.x = 0.5f;
	velocidade.y = 0.f;

	pFigura->setSize(tamanho);
	if (!textura.loadFromFile("Assets/Imagens/Projetil.png")) {
		std::cout << "Erro ao carregar textura do projetil." << std::endl;
		pFigura->setFillColor(sf::Color(222, 120, 31));
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
	pFigura->setPosition(pos.x, pos.y);
}

// Desativa o projetil antes da destruicao.
Projetil::~Projetil()
{
	ativo = false;
}

// Atualiza se o projetil participa do movimento e das colisoes.
void Projetil::setar_Ativo(bool atv)
{
	ativo = atv;
}

// Define o dano aplicado ao jogador atingido.
void Projetil::setar_Dano(int dan)
{
	dano = dan;
}

// Define para qual lado o projetil deve se mover.
void Projetil::setar_Direcao(int direcao)
{
	lado = direcao;
}

// Retorna se o projetil ainda deve ser processado.
bool Entidades::Projetil::get_Ativo()
{
	return ativo;
}

// Aplica dano apenas quando o projetil ainda esta ativo.
void Projetil::Atingiu_Jogador(Entidades::Personagens::Jogador* pJogador)
{
	if (ativo) {
		pJogador->diminuir_Vitalidade(dano);
	}
}

// Move o projetil ativo e atualiza sua posicao na tela.
void Projetil::executar()
{
	if (!ativo) {
		return;
	}

	executar_Gravidade();
	executar_Empuxo();
	
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

	setar_Pos(pos.x, pos.y);
	desenhar();
}

// Salvar ainda nao foi implementado para projetil.
void Projetil::salvar()
{
}

// Compensa parte da gravidade para dar uma queda leve ao disparo.
void Projetil::executar_Empuxo()
{
	pos.y -= (velocidade.y - 0.3f);
}
