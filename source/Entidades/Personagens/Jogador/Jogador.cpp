#include "Entidades/Personagens/Jogador/Jogador.h"

using namespace Entidades;
using namespace Personagens;

const int Jogador::id_base(10);

// Carrega a imagem do jogador 1 e usa cor simples se a textura falhar.
void Jogador::setar_Figura()
{
	pFigura->setSize(tamanho);
	if (!textura.loadFromFile("Assets/Imagens/Jogador_1.png")) {
		std::cout << "Erro ao carregar textura do jogador 1." << std::endl;
		pFigura->setFillColor(sf::Color::Blue);
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
}

// Comeca o jogador com estado limpo de movimento, pulo e pontuacao.
Jogador::Jogador(sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely):
	Personagem(id_base, p, tam, vida, velx, vely)
{
	segundo_jogador = false;
	estado_pulando = false;
	no_ar = false;
	acelerando = false;
	forca_de_impulso = -9.0f;
	pontos = 0;
	dano = 70;

	setar_Figura();
	setar_Pos(pos.x, pos.y);
}

// Nao precisa liberar nada alem do que a classe base ja cuida.
Jogador::~Jogador()
{
}

// Configura a aparencia e estado inicial quando este objeto vira jogador 2.
void Jogador::setar_Dois_Jogadores(bool jogador_dois)
{
	if (jogador_dois) {
		segundo_jogador = jogador_dois;
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
}

// Retorna se este objeto esta sendo usado como jogador 2.
bool Jogador::get_Dois_Jogadores() const
{
	return segundo_jogador;
}

// Inicia o pulo apenas se o jogador nao estiver pulando nem no ar.
void Jogador::executando_Pulo()
{
	if (!estado_pulando && !no_ar) {
		velocidade.y = forca_de_impulso + 3.0f;
		estado_pulando = true;
		no_ar = true;
		acelerando = true;
	}
}

// Para o impulso vertical quando o jogador bate por cima.
void Jogador::setar_Bateu_A_Cabeca()
{
	velocidade.y = 0;
	acelerando = false;
	estado_pulando = true;
	no_ar = true;
}

// Libera o pulo de novo quando o jogador pisa em algo.
void Jogador::setar_Pode_Pular()
{
	estado_pulando = false;
	no_ar = false;
}

// Retorna os pontos acumulados.
int Jogador::get_Pontuacao() const
{
	return pontos;
}

// Aplica dano e mostra as vidas atuais no console.
void Jogador::diminuir_Vitalidade(int dano)
{
	num_vidas -= dano;
	if (num_vidas <= 0) {
		num_vidas = 0;
		eliminado = true;
	}
	std::cout << "Jogador " << getId() << " tomou " << dano << " de dano. Vidas atuais: " << num_vidas << std::endl;
}

// Danifica o alvo e faz o jogador quicar depois do ataque.
void Jogador::colidir(Personagem* pAtacado)
{
	pAtacado->diminuir_Vitalidade(dano);
	setar_Pode_Pular();
	executando_Pulo();
}

// Soma pontos ganhos durante a fase.
void Jogador::aumentar_Pontuacao(int pontos_a_adicionar)
{
	pontos += pontos_a_adicionar;
}

// Move com WASD no jogador 1 e setas no jogador 2.
void Jogador::mover()
{
	if (!segundo_jogador) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			pos.x += velocidade.x;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			pos.x -= velocidade.x;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			executando_Pulo();
		}
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
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

// Atualiza pulo, gravidade, desenho e movimento do jogador.
void Jogador::executar()
{
	if (!eliminado) {
		if (velocidade.y <= forca_de_impulso) {
			acelerando = false;
		}

		if (estado_pulando && acelerando) {
			velocidade.y -= 0.6f;
		}

		executar_Gravidade();
		desenhar();
		setar_Pos(pos.x, pos.y);
		mover();
	}
}

// Salvar ainda nao foi implementado para jogador.
void Jogador::salvar()
{
}
