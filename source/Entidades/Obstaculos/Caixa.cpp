#include "Entidades/Obstaculos/Caixa.h"


Entidades::Obstaculos::Caixa::Caixa(): sendo_empurrada(false), empurrar_esquerda(false), distancia_percorrida(0.f)
{
    densidade_superficial = 0.02f;

    velocidade.x = 1.f;
    velocidade.y = 1.f;

    relogio_empurrao.restart();
}
Entidades::Obstaculos::Caixa::~Caixa()
{
}

void Entidades::Obstaculos::Caixa::executar()
{
    desenhar();
    executar_Gravidade();

    if(sendo_empurrada){
        executar_Empurrao();
    }

    setar_Pos(pos.x, pos.y);
}

void Entidades::Obstaculos::Caixa::seta_Caixa(float origem_x, float origem_y)
{
    tamanho.x = 64.f;
	tamanho.y = 64.f;

	//pFigura->setFillColor(sf::Color::Green);
	pFigura->setSize(tamanho);
	if (!textura.loadFromFile("Assets/Imagens/Caixa.png")) {
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
void Entidades::Obstaculos::Caixa::obstacular(Entidades::Personagens::Jogador *p, int lado)
{
    if(lado == esquerda || lado == direita){
        iniciar_Empurrao(lado);
    }
}

void Entidades::Obstaculos::Caixa::iniciar_Empurrao(int lado)
{
    const float tempo_recarga = 0.35f;

    if(!sendo_empurrada && relogio_empurrao.getElapsedTime().asSeconds() >= tempo_recarga){
        sendo_empurrada = true;
        empurrar_esquerda = (lado == esquerda);
        distancia_percorrida = 0.f;
    }
}

void Entidades::Obstaculos::Caixa::executar_Empurrao()
{
    const float distancia_maxima = 24.f;
    const float velocidade_empurrao = 1.5f;

    if(empurrar_esquerda){
        pos.x -= velocidade_empurrao;
    }
    else{
        pos.x += velocidade_empurrao;
    }

    distancia_percorrida += velocidade_empurrao;

    if(distancia_percorrida >= distancia_maxima){
        parar_Empurrao();
    }
}

void Entidades::Obstaculos::Caixa::parar_Empurrao()
{
    sendo_empurrada = false;
    distancia_percorrida = 0.f;
    relogio_empurrao.restart();
}

void Entidades::Obstaculos::Caixa::salvar()
{
}
