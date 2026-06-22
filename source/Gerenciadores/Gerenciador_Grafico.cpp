#include "Gerenciadores/Gerenciador_Grafico.h"

using namespace sf;
using namespace std;
using namespace Gerenciadores;

Gerenciador_Grafico* Gerenciador_Grafico::pInstancia = NULL;

Gerenciador_Grafico::Gerenciador_Grafico()
{
    largura = 1280;
    altura = 720;

    janela = new RenderWindow(VideoMode(largura, altura), "Mar dos Condenados", sf::Style::Titlebar | sf::Style::Close);
    evento = new Event();
    camera = new View(Vector2f(largura / 2.f, altura / 2.f), Vector2f(static_cast<float>(largura), static_cast<float>(altura)));

    janela->setFramerateLimit(60);
    janela->setView(*camera);

    setar_Fonte();
}

Gerenciadores::Gerenciador_Grafico::~Gerenciador_Grafico()
{

    delete evento;
    delete camera;
    delete janela;
}

Gerenciador_Grafico* Gerenciador_Grafico::getInstancia()
{
    if(pInstancia == NULL){
        pInstancia = new Gerenciador_Grafico();
    }
    return pInstancia;
}

void Gerenciador_Grafico::destruirInstancia()
{
    if(pInstancia != NULL){
        delete pInstancia;
        pInstancia = NULL;
    }
}

void Gerenciadores::Gerenciador_Grafico::desenhar(Sprite* corpo)
{
    janela->draw(*corpo);
}

void Gerenciadores::Gerenciador_Grafico::desenhar(RectangleShape* aux)
{
    janela->draw(*aux);
}

void Gerenciadores::Gerenciador_Grafico::desenhar(Text* texto)
{
    janela->draw(*texto);
}

void Gerenciadores::Gerenciador_Grafico::setar_Fonte(){
    if(!fonte.loadFromFile("Assets/Fontes/PirataOne-Regular.ttf")){
        std::cout << "Erro ao carregar a fonte!" << std::endl;
    }
}

Text* Gerenciadores::Gerenciador_Grafico::setar_Texto(string texto, int tamanho, Vector2f pos){

    sf::Text* retorno = new Text;

    retorno->setFont(fonte);
    retorno->setString(texto);
    retorno->setCharacterSize(tamanho);
    retorno->setPosition(pos);
    retorno->setColor(sf::Color::White);

    return retorno;
}

void Gerenciadores::Gerenciador_Grafico::setar_Cor_Texto(sf::Text* texto, sf::Color cor){

    texto->setColor(cor);
}

RenderWindow *Gerenciadores::Gerenciador_Grafico::getJanela() const
{
    return janela;
}

View* Gerenciadores::Gerenciador_Grafico::getCamera() const
{
    return camera;
}

sf::Event* Gerenciador_Grafico::getEvent() const {
	return evento;
}

void Gerenciadores::Gerenciador_Grafico::limpar()
{
    if(isOpen()){
        janela->clear();
    }
}

bool Gerenciadores::Gerenciador_Grafico::isOpen() const
{
    return janela->isOpen();
}

void Gerenciadores::Gerenciador_Grafico::centralizar(Vector2f pos)
{
    float cameraX = pos.x;
    
    const float maxCam = 5000.0f - largura / 2;

    if (cameraX < largura / 2) {
        cameraX = largura / 2;
    } else if (cameraX > maxCam) {
        cameraX = maxCam;
    }
    
    camera->setCenter(cameraX, camera->getCenter().y);
    
    janela->setView(*camera);
}


void Gerenciadores::Gerenciador_Grafico::mostrar()
{
    if(isOpen()){
        janela->display();
    }
}

void Gerenciadores::Gerenciador_Grafico::fechar()
{
    janela->close();
}
