#include "Entidades/Entidade.h"


using namespace Entidades;
using namespace std;
using namespace sf;
/*
Entidade::Entidade(int semente, Vector2f p, RectangleShape corpo, Vector2f tam):
    Ente(semente),
    body(corpo),
    pos(p),
    size(tam),
    direita(1), cima(2),
    esquerda(3), baixo(4)
*/
Entidade::Entidade(int semente, Vector2f p, Vector2f tam):
    Ente(semente),
    pos(p),
    tamanho(tam),
    direita(1), cima(2),
    esquerda(3), baixo(4)
{
    //aceleracao = Vector2f(0.f, 0.f);
    velocidade = Vector2f(0.f, 0.f);
    gravidade = 6.0f;

    //pFigura = corpo;
    pFigura->setSize(tam);
    //pFigura->setSize(pos);
    pFigura->setPosition(pos);
    //body.setSize(tam);
    //body.setPosition(pos);
}

Entidade::~Entidade()
{
}

float Entidade::get_Gravidade() const
{
    return gravidade;
}

void Entidade::setar_Gravidade(float grav)
{
    gravidade = grav;
}

void Entidade::executar_Gravidade()
{
    
    //velocidade.y += gravidade;
    //setar_Pos(pos.x, pos.y + gravidade);

    //acelera até bater o teto da gravidade.
    if (velocidade.y <= gravidade) {
		//pos.y += velocidade.y;
		velocidade.y += 0.3f;
		//velocidade.y = gravidade;
	}
    //limita a velocidade a gravidade definida anteriormente, 6.0f
	if (velocidade.y > gravidade) {
		velocidade.y = gravidade;
	}
    

	pos.y += velocidade.y;
}

//Em relação a posição global.
Vector2f Entidade::get_Centro()
{
    centro_glob.x = pos.x + (get_Largura() / 2);
    centro_glob.y = pos.y + (get_Altura() / 2);

    return sf::Vector2f(centro_glob);
}


Vector2f Entidade::get_Tamanho()
{
    return tamanho;
}

float Entidade::get_Largura()
{
    return pFigura->getLocalBounds().width;
}

float Entidade::get_Altura()
{
    return pFigura->getLocalBounds().height;
}

float Entidade::get_Comprimento_A()
{
    return get_Y() + get_Altura();
}

float Entidade::get_Comprimento_L()
{
    return get_X() + get_Largura();
}

Vector2f Entidade::getPos()
{
    return pos;
}

float Entidade::get_X() const
{
    return pos.x;
}

float Entidade::get_Y() const
{
    return pos.y;
}

float Entidade::get_Vel_X() const {
    return velocidade.x;
}

float Entidade::get_Vel_Y() const {
    return velocidade.y;
}

void Entidade::setar_Pos(float pos_x, float pos_y)
{
    pos.x = pos_x;
    pos.y = pos_y;

    pFigura->setPosition(pos);
    //body.setPosition(pos);
}

void Entidade::setar_Pos(Vector2f p)
{
    setar_Pos(p.x, p.y);
}

void Entidade::setar_velocidade(float vel_x, float vel_y)
{
    velocidade.x = vel_x;
    velocidade.y = vel_y;
}

/*
void Entidade::setar_aceleracao(float ace_x, float ace_y){
    wd.x=ace_x;
    aceleracao.y=ace_y;
}
*/

/*
RectangleShape Entidade::getBody()
{
    return body;
}
*/
