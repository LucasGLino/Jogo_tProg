#include "Entidades/Obstaculos/Obstaculo.h"

using namespace Entidades;
using namespace Personagens;
using namespace Obstaculos;

/*
Obstaculo::Obstaculo() : Entidade(id_base)
*/
Obstaculo::Obstaculo() : Entidade(id_base, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)) 
{
	//agressivo = false;
	danoso = false;
	//setId(semente_id_entidade);

	densidade_superficial = 0.f;
	massa = 0.f;
	//densidade_de_area = (massa/calcula_Densidade_de_Area(*pFigura,200,200));

	tamanho.x = 0.f;
	tamanho.y = 0.f;
	gravidade = 6.0f;
	
}

Obstaculo::~Obstaculo() {

}

//n�o sei como executar a gravidade aplicada ao obstaculo.
// void Obstaculo::executar_Gravidade(){
// 	pos.y += gravidade;
// 	pos.y -= gravidade;
// }

void Entidades::Obstaculos::Obstaculo::seta_Obstaculo(float alt, float larg, float origem_x, float origem_y, std::string assets)
{
	tamanho.x = larg;
	tamanho.y = alt;

	//pFigura->setFillColor(sf::Color::Green);
	pFigura->setSize(tamanho);
	if (!textura.loadFromFile(assets)) {
		std::cout << "Erro ao carregar textura da plataforma." << std::endl;
		pFigura->setFillColor(sf::Color::Green);
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
	this->setar_Pos(origem_x, origem_y);

	massa = (densidade_superficial * calcula_Densidade_de_Area(*pFigura,50,50));
}

bool Obstaculo::pontoDentroDoPoligono(const sf::Shape& figura, sf::Vector2f ponto)
{
    bool dentro = false;

    unsigned int quantidadePontos = figura.getPointCount();

    for (unsigned int indiceAtual = 0, indiceAnterior = quantidadePontos - 1;
         indiceAtual < quantidadePontos;
         indiceAnterior = indiceAtual++)
    {
        sf::Vector2f pontoAtual =
            figura.getTransform().transformPoint(figura.getPoint(indiceAtual));

        sf::Vector2f pontoAnterior =
            figura.getTransform().transformPoint(figura.getPoint(indiceAnterior));

        bool cruza =
            ((pontoAtual.y > ponto.y) != (pontoAnterior.y > ponto.y)) &&
            (ponto.x < (pontoAnterior.x - pontoAtual.x) *
            (ponto.y - pontoAtual.y) /
            (pontoAnterior.y - pontoAtual.y) + pontoAtual.x);

        if (cruza)
        {
            dentro = !dentro;
        }
    }

    return dentro;
}

float Obstaculo::calcula_Densidade_de_Area(const sf::Shape& figura, int divisoesHorizontais, int divisoesVerticais){

	if (divisoesHorizontais <= 0 || divisoesVerticais <= 0)
    {
        return 0.f;
    }

    sf::FloatRect limites = figura.getGlobalBounds();

    float larguraQuadrado = limites.width / divisoesHorizontais;
    float alturaQuadrado = limites.height / divisoesVerticais;

    float area = 0.f;

    for (int coluna = 0; coluna < divisoesHorizontais; coluna++)
    {
        for (int linha = 0; linha < divisoesVerticais; linha++)
        {
            float xMeio = limites.left + (coluna + 0.5f) * larguraQuadrado;
            float yMeio = limites.top + (linha + 0.5f) * alturaQuadrado;

            sf::Vector2f pontoMedio(xMeio, yMeio);

            if (pontoDentroDoPoligono(figura, pontoMedio))
            {
                area += larguraQuadrado * alturaQuadrado;
            }
        }
    }

    return area;

}

/*
void Obstaculo::setar_Massa_Densidade(int aux_massa){
	massa = aux_massa;
	densidade_de_area = (massa/calcula_Densidade_de_Area(*pFigura,50,50));
}
*/

float Obstaculo::get_Massa(){
	return massa;
}

void Obstaculo::salvar(){
}

void Obstaculo::executar(){
}

const int Obstaculo::id_base(1000);

