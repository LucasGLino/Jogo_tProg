#include "Entidades/Obstaculos/Obstaculo.h"

using namespace Entidades;
using namespace Obstaculos;

const int Obstaculo::id_base(1000);

// Comeca sem massa calculada.
Obstaculo::Obstaculo() : Entidade(id_base, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f))
{
	densidade_superficial = 0.f;
	massa = 0.f;
}

// Nao precisa liberar nada alem do que a classe base ja cuida.
Obstaculo::~Obstaculo()
{
}

// Define figura, textura, posicao e massa do obstaculo.
void Obstaculo::seta_Obstaculo(float alt, float larg, float origem_x, float origem_y, const std::string& assets)
{
	tamanho.x = larg;
	tamanho.y = alt;

	pFigura->setSize(tamanho);
	if (!textura.loadFromFile(assets)) {
		std::cout << "Erro ao carregar textura do obstaculo." << std::endl;
		pFigura->setFillColor(sf::Color::Green);
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}

	setar_Pos(origem_x, origem_y);
	massa = densidade_superficial * calcula_Densidade_de_Area(*pFigura, 50, 50);
}

// Usa as bordas da figura para saber se o ponto esta dentro dela.
bool Obstaculo::pontoDentroDoPoligono(const sf::Shape& figura, sf::Vector2f ponto)
{
	bool dentro = false;
	unsigned int quantidadePontos = figura.getPointCount();

	for (unsigned int indiceAtual = 0, indiceAnterior = quantidadePontos - 1;
		 indiceAtual < quantidadePontos;
		 indiceAnterior = indiceAtual++)
	{
		sf::Vector2f pontoAtual = figura.getTransform().transformPoint(figura.getPoint(indiceAtual));
		sf::Vector2f pontoAnterior = figura.getTransform().transformPoint(figura.getPoint(indiceAnterior));

		bool cruza =
			((pontoAtual.y > ponto.y) != (pontoAnterior.y > ponto.y)) &&
			(ponto.x < (pontoAnterior.x - pontoAtual.x) *
			(ponto.y - pontoAtual.y) /
			(pontoAnterior.y - pontoAtual.y) + pontoAtual.x);

		if (cruza) {
			dentro = !dentro;
		}
	}

	return dentro;
}

// Divide a figura em uma grade e soma os quadrados que ficam dentro dela.
float Obstaculo::calcula_Densidade_de_Area(const sf::Shape& figura, int divisoesHorizontais, int divisoesVerticais)
{
	if (divisoesHorizontais <= 0 || divisoesVerticais <= 0) {
		return 0.f;
	}

	sf::FloatRect limites = figura.getGlobalBounds();
	float larguraQuadrado = limites.width / divisoesHorizontais;
	float alturaQuadrado = limites.height / divisoesVerticais;
	float area = 0.f;

	for (int coluna = 0; coluna < divisoesHorizontais; coluna++) {
		for (int linha = 0; linha < divisoesVerticais; linha++) {
			float xMeio = limites.left + (coluna + 0.5f) * larguraQuadrado;
			float yMeio = limites.top + (linha + 0.5f) * alturaQuadrado;
			sf::Vector2f pontoMedio(xMeio, yMeio);

			if (pontoDentroDoPoligono(figura, pontoMedio)) {
				area += larguraQuadrado * alturaQuadrado;
			}
		}
	}

	return area;
}

// Retorna a massa calculada pela densidade e area.
float Obstaculo::get_Massa() const
{
	return massa;
}
