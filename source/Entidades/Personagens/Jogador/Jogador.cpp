#include "Entidades/Personagens/Jogador/Jogador.h"

using namespace Entidades;
using namespace Personagens;


const int Jogador::id_base(10);

//Jogador::Jogador(int semente, sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely):
Jogador::Jogador(sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely):
	Personagem(id_base, p, tam, vida, velx, vely) 
{

	segundo_jogador = false;
	estado_pulando = false;
	no_ar = false;
	estado_caindo = true;

	vitalidade = vida;

	dano = 70;

	pos = p;
	tamanho = tam;

	set_Vitalidade(vida);
	setar_Figura();
	setar_Pos(pos.x, pos.y);

	forca_de_impulso = -9.0;
	acelerando = false;
	
	velocidade.y = vely;
	velocidade.x = velx;

	pontos = 0;
}

Jogador::~Jogador() {

}

void Jogador::executar() {


	if (!eliminado) {

		if (velocidade.y <= forca_de_impulso) {
			acelerando = false;
		}

		if (estado_pulando) {
			if (acelerando) {
				velocidade.y -= 0.6f;
			}
		}

		executar_Gravidade();

		desenhar();
		setar_Pos(pos.x, pos.y);

		if (!segundo_jogador) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				pos.x += velocidade.x;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				pos.x -= velocidade.x;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				//pos.y -=2.f;
				executando_Pulo();
			}

		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				pos.x += velocidade.x;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				pos.x -= velocidade.x;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				executando_Pulo();
			}
		}
	}
	
}

bool Jogador::get_Eliminado() const
{
	return eliminado;
}


void Jogador::setar_Dois_Jogadores(bool jogador_dois) {

	if (jogador_dois) {
		segundo_jogador = jogador_dois;
		//pFigura->setFillColor(sf::Color::Cyan);
		if (!textura.loadFromFile("Assets/Imagens/Jogador_2.png")) {
			std::cout << "Erro ao carregar textura do jogador 2." << std::endl;
			pFigura->setTexture(NULL);
			pFigura->setFillColor(sf::Color::Cyan);
		}
		else {
			pFigura->setFillColor(sf::Color::White);
			pFigura->setTexture(&textura);
		}
		setar_Pos(pos.x + 25, pos.y);
		eliminado = false;
		estado_pulando = false;
		no_ar = false;
	}
	else {
		eliminado = true;
	}
}

bool Jogador::get_Dois_Jogadores() {
	return segundo_jogador;
}

void Entidades::Personagens::Jogador::executando_Pulo()
{
	if (!estado_pulando && !no_ar) {

		velocidade.y = forca_de_impulso + 3.0f;
		estado_pulando = true;
		no_ar = true;

		acelerando = true;
	}
}

void Jogador::salvar(){

}


void Jogador::colidir(Personagem* pAtacado) {

	pAtacado->diminuir_Vitalidade(dano);
	setar_Pode_Pular();
	executando_Pulo();
}


void Jogador::diminuir_Vitalidade(int dano) {

	vitalidade -= dano;
	if (vitalidade <= 0) {
		vitalidade = 0;
		eliminado = true;
	}
	// std::cout << "Jogador " << getId() << " tomou " << dano << " de dano. Vitalidade atual: " << vitalidade << std::endl;

	if (eliminado) {
		// std::cout << "Jogador " << getId() << " foi eliminado!" << std::endl;
	}
}

// adicionar em classes primordiais? tais como Ente ou Entidades?
void Jogador::setar_Figura() {

	pFigura->setSize(tamanho);
	//pFigura->setFillColor(sf::Color::Blue);
	if (!textura.loadFromFile("Assets/Imagens/Jogador_1.png")) {
		std::cout << "Erro ao carregar textura do jogador 1." << std::endl;
		pFigura->setFillColor(sf::Color::Blue);
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
}

void Jogador::aumentar_Pontuacao(int pontos_a_adicionar){

	pontos += pontos_a_adicionar;
}

int Jogador::get_Pontuacao() const {

	return pontos;
}

void Jogador::setar_Caindo(bool caindo){
	estado_caindo = caindo;
}

void Jogador::setar_Bateu_A_Cabeca(){
	
	velocidade.y = 0;
	acelerando = false;
	estado_pulando = true;
	no_ar = true;
}

void Jogador::setar_Pode_Pular(){

	estado_pulando = false;
	no_ar = false;

}