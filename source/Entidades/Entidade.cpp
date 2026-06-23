#include "Entidades/Entidade.h"


using namespace Entidades;
using namespace sf;

// Inicializa posicao, tamanho, lados de colisao e figura da entidade.
Entidade::Entidade(int semente, Vector2f p, Vector2f tam):
	Ente(semente),
	pos(p),
	tamanho(tam),
	direita(1), cima(2),
	esquerda(3), baixo(4)
{
	velocidade = Vector2f(0.f, 0.f);
	gravidade = 6.0f;

	pFigura->setSize(tam);
	pFigura->setPosition(pos);
}

// Destrutor virtual para permitir destruicao correta pelas classes filhas.
Entidade::~Entidade()
{
}

// Aumenta a velocidade vertical ate o limite de queda e move a entidade.
void Entidade::executar_Gravidade()
{
	if (velocidade.y <= gravidade) {
		velocidade.y += 0.3f;
	}

	if (velocidade.y > gravidade) {
		velocidade.y = gravidade;
	}

	pos.y += velocidade.y;
}

// Calcula o centro usando a posicao atual e o tamanho da figura.
Vector2f Entidade::get_Centro()
{
	return Vector2f(pos.x + (get_Largura() / 2), pos.y + (get_Altura() / 2));
}

// Retorna a largura atual da figura da entidade.
float Entidade::get_Largura()
{
	return pFigura->getLocalBounds().width;
}

// Retorna a altura atual da figura da entidade.
float Entidade::get_Altura()
{
	return pFigura->getLocalBounds().height;
}

// Retorna o limite inferior da entidade.
float Entidade::get_Comprimento_A()
{
	return get_Y() + get_Altura();
}

// Retorna o limite direito da entidade.
float Entidade::get_Comprimento_L()
{
	return get_X() + get_Largura();
}

// Retorna a coordenada x atual.
float Entidade::get_X() const
{
	return pos.x;
}

// Retorna a coordenada y atual.
float Entidade::get_Y() const
{
	return pos.y;
}

// Atualiza a posicao interna e sincroniza a figura.
void Entidade::setar_Pos(float pos_x, float pos_y)
{
	pos.x = pos_x;
	pos.y = pos_y;

	pFigura->setPosition(pos);
}

// Sobrecarga para atualizar a posicao usando um vetor.
void Entidade::setar_Pos(Vector2f p)
{
	setar_Pos(p.x, p.y);
}

// Define a velocidade usada por movimento, gravidade e impulso.
void Entidade::setar_velocidade(float vel_x, float vel_y)
{
	velocidade.x = vel_x;
	velocidade.y = vel_y;
}
