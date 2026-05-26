#include"../include/Grafico.h"

using namespace sf;
using namespace std;
using namespace Gerenciadores;

unsigned int GerenciadorGrafico::largura(1280);
unsigned int GerenciadorGrafico::altura(720);

GerenciadorGrafico* GerenciadorGrafico::pInstancia = nullptr;

GerenciadorGrafico::GerenciadorGrafico(): window(new RenderWindow(VideoMode({largura, altura}), "Fantasy", sf::Style::Titlebar | sf::Style::Close)),view(Vector2f(largura / 2, altura / 2), Vector2f(largura, altura))
{
    window->setFramerateLimit(60);
}

Gerenciadores::GerenciadorGrafico::~GerenciadorGrafico()
{
    delete(window);
}

GerenciadorGrafico* GerenciadorGrafico::getInstancia()
{
    if(pInstancia == nullptr){
        pInstancia = new GerenciadorGrafico();
    }
    return pInstancia;
}

void Gerenciadores::GerenciadorGrafico::desenhar(Sprite* corpo)
{
    window->draw(*corpo);
}

void Gerenciadores::GerenciadorGrafico::desenhar(RectangleShape rect)
{
    window->draw(rect);
}

void Gerenciadores::GerenciadorGrafico::desenhar(Text* texto)
{
    window->draw(*texto);
}


RenderWindow *Gerenciadores::GerenciadorGrafico::getWindow() const
{
    return window;
}

void Gerenciadores::GerenciadorGrafico::limpar()
{
    if(isOpen()){
        window->clear();
    }
}

bool Gerenciadores::GerenciadorGrafico::isOpen() const
{
    return window->isOpen();
}

void Gerenciadores::GerenciadorGrafico::centralizar(Vector2f pos)
{
    float viewX = pos.x;
    
    const float maxCam = 5000.0f - largura / 2;


    float cameraX = viewX;

    if (viewX < largura / 2) {
        cameraX = largura / 2;
    } else if (viewX > maxCam) {
        cameraX = maxCam;
    }
    
    view.setCenter({cameraX,view.getCenter().y});
    
    window->setView(view);
}

View Gerenciadores::GerenciadorGrafico::getView() const
{
    return view;
}

void Gerenciadores::GerenciadorGrafico::mostrar()
{
    if(isOpen()){
        window->display();
    }
}

void Gerenciadores::GerenciadorGrafico::fechar()
{
    window->close();
}