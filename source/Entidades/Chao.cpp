#include "Entidades/Chao.h"

using namespace Entidades;

Chao::Chao() : Entidade(id_base, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f))
{
	limite_abismo = 0.f;
}

Chao::~Chao()
{
}

void Chao::configurar_Chao(float alt, float larg, float origem_x, float origem_y, std::string assets)
{
	tamanho.x = larg;
	tamanho.y = alt;

	pFigura->setSize(tamanho);
	if (!textura.loadFromFile(assets)) {
		std::cout << "Erro ao carregar textura do chao." << std::endl;
		pFigura->setFillColor(sf::Color::Green);
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}

	setar_Pos(origem_x, origem_y);
	limite_abismo = origem_y + alt;
}

void Chao::setar_Limite_Abismo(float limite)
{
	limite_abismo = limite;
}

bool Chao::entidade_Caiu_No_Abismo(Entidade* pEntidade)
{
	if (pEntidade == nullptr) {
		return false;
	}

	return (pEntidade->get_Y() > limite_abismo);
}

void Chao::executar()
{
	desenhar();
}

void Chao::salvar()
{
}

const int Chao::id_base(9000);
