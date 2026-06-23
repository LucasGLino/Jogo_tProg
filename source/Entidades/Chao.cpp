#include "Entidades/Chao.h"

using namespace Entidades;

const int Chao::id_base(9000);

// Comeca vazio porque a fase configura tamanho e posicao depois.
Chao::Chao() : Entidade(id_base, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f))
{
	limite_abismo = 0.f;
}

// Nao precisa liberar nada alem do que a classe base ja cuida.
Chao::~Chao()
{
}

// Configura o piso da fase e ja calcula o limite do abismo.
void Chao::configurar_Chao(float alt, float larg, float origem_x, float origem_y, const std::string& assets)
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

// Sobrescreve o limite do abismo quando a fase quiser outro valor.
void Chao::setar_Limite_Abismo(float limite)
{
	limite_abismo = limite;
}

// Retorna true quando a entidade passou abaixo do limite do chao.
bool Chao::entidade_Caiu_No_Abismo(Entidade* pEntidade)
{
	if (pEntidade == nullptr) {
		return false;
	}

	return (pEntidade->get_Y() > limite_abismo);
}

// O chao so precisa aparecer na tela.
void Chao::executar()
{
	desenhar();
}

// Salvar ainda nao foi implementado para chao.
void Chao::salvar()
{
}
