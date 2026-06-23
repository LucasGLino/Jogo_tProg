#include "Gerenciadores/Gerenciador_Grafico.h"

using namespace sf;
using namespace std;
using namespace Gerenciadores;

Gerenciador_Grafico* Gerenciador_Grafico::pInstancia = nullptr;

// Cria a janela principal, a camera inicial e carrega a fonte padrao.
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

// Libera os recursos graficos criados pelo gerenciador.
Gerenciadores::Gerenciador_Grafico::~Gerenciador_Grafico()
{
    delete evento;
    delete camera;
    delete janela;
}

// Retorna a instancia unica do gerenciador grafico.
Gerenciador_Grafico* Gerenciador_Grafico::getInstancia()
{
    if(pInstancia == nullptr){
        pInstancia = new Gerenciador_Grafico();
    }
    return pInstancia;
}

// Destroi a instancia unica quando o jogo encerra.
void Gerenciador_Grafico::destruirInstancia()
{
    if(pInstancia != nullptr){
        delete pInstancia;
        pInstancia = nullptr;
    }
}

// Desenha um sprite se o ponteiro recebido for valido.
void Gerenciadores::Gerenciador_Grafico::desenhar(Sprite* corpo)
{
    if(corpo == nullptr){
        return;
    }

    janela->draw(*corpo);
}

// Desenha um retangulo se o ponteiro recebido for valido.
void Gerenciadores::Gerenciador_Grafico::desenhar(RectangleShape* aux)
{
    if(aux == nullptr){
        return;
    }

    janela->draw(*aux);
}

// Desenha um texto se o ponteiro recebido for valido.
void Gerenciadores::Gerenciador_Grafico::desenhar(Text* texto)
{
    if(texto == nullptr){
        return;
    }

    janela->draw(*texto);
}

// Carrega a fonte usada pelos textos do jogo.
void Gerenciadores::Gerenciador_Grafico::setar_Fonte(){
    if(!fonte.loadFromFile("Assets/Fontes/PirataOne-Regular.ttf")){
        std::cout << "Erro ao carregar a fonte!" << std::endl;
    }
}

// Cria um texto configurado; quem chama fica responsavel por deletar esse ponteiro.
Text* Gerenciadores::Gerenciador_Grafico::setar_Texto(const string& texto, int tamanho, Vector2f pos){
    sf::Text* retorno = new Text;

    retorno->setFont(fonte);
    retorno->setString(texto);
    retorno->setCharacterSize(tamanho);
    retorno->setPosition(pos);
    retorno->setColor(sf::Color::White);

    return retorno;
}

// Altera a cor do texto se o ponteiro recebido for valido.
void Gerenciadores::Gerenciador_Grafico::setar_Cor_Texto(sf::Text* texto, sf::Color cor){
    if(texto == nullptr){
        return;
    }

    texto->setColor(cor);
}

// Retorna a janela principal do jogo.
RenderWindow *Gerenciadores::Gerenciador_Grafico::getJanela() const
{
    return janela;
}

// Retorna a camera usada pela janela.
View* Gerenciadores::Gerenciador_Grafico::getCamera() const
{
    return camera;
}

// Retorna o evento usado pelo loop principal.
sf::Event* Gerenciador_Grafico::getEvent() const {
	return evento;
}

// Limpa a janela antes de desenhar o proximo quadro.
void Gerenciadores::Gerenciador_Grafico::limpar()
{
    if(isOpen()){
        janela->clear();
    }
}

// Informa se a janela ainda esta aberta.
bool Gerenciadores::Gerenciador_Grafico::isOpen() const
{
    return janela->isOpen();
}

// Centraliza a camera no eixo x, respeitando os limites do mapa.
void Gerenciadores::Gerenciador_Grafico::centralizar(Vector2f pos)
{
    float cameraX = pos.x;
    
    // Limite horizontal atual do mapa.
    const float maxCam = 5000.0f - largura / 2;

    if (cameraX < largura / 2) {
        cameraX = largura / 2;
    } else if (cameraX > maxCam) {
        cameraX = maxCam;
    }
    
    camera->setCenter(cameraX, camera->getCenter().y);
    
    janela->setView(*camera);
}

// Mostra na tela tudo que foi desenhado no quadro atual.
void Gerenciadores::Gerenciador_Grafico::mostrar()
{
    if(isOpen()){
        janela->display();
    }
}

// Fecha a janela principal.
void Gerenciadores::Gerenciador_Grafico::fechar()
{
    janela->close();
}
