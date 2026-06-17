#include "Elementos/Botao.h"

#define corBotao sf::Color(100, 100, 100, 200)

#define bHover sf::Color(150, 150, 150, 255)


Botao::Botao(const std::string& stri, const sf::Font& fonte, sf::Vector2f pos):str(stri, fonte, 30), press(false)
{    

    pGg = Gerenciadores::Gerenciador_Grafico::getInstancia();
    
    this->str.setFillColor(sf::Color::White);

    sf::FloatRect tamanhoStr = this->str.getGlobalBounds();

    this->str.setOrigin({tamanhoStr.getPosition().x + tamanhoStr.getSize().x / 2.0f, tamanhoStr.getPosition().y + tamanhoStr.getSize().y / 2.0f});

    const float paddingX = 40.0f;
    const float paddingY = 20.0f;

    float larguraBotao = tamanhoStr.getSize().x + paddingX;
    float tamanhoBotao = tamanhoStr.getSize().y + paddingY;

    this->botao.setSize({larguraBotao, tamanhoBotao});
    this->botao.setFillColor(corBotao);

    this->botao.setOrigin({larguraBotao / 2.0f, tamanhoBotao / 2.0f});

    this->botao.setPosition(pos);
    this->str.setPosition(pos);

}

Botao::~Botao()
{
}

void Botao::desenhar()
{
    Gerenciadores::Gerenciador_Grafico* pGg = Gerenciadores::Gerenciador_Grafico::getInstancia();

    pGg->desenhar(&botao);
    pGg->desenhar(&str);
}

void Botao::hover()
{
    sf::RenderWindow* window = pGg->getJanela();
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    sf::Vector2f mousePosMundo = (sf::Vector2f)mousePos;
   
    if(this->botao.getGlobalBounds().contains(mousePosMundo)){
        this->botao.setFillColor(bHover);
    }else{
        this->botao.setFillColor(corBotao);
    }
}
bool Botao::getPress()
{
    sf::RenderWindow* window = pGg->getJanela();
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    sf::Vector2f mousePosMundo = (sf::Vector2f)mousePos;

    if (!this->botao.getGlobalBounds().contains(mousePosMundo)) {

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
             press = false; 
        }
        return false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        
        press = true; 
        return false; 
    } 

    else if (press) 
    {

        press = false; 

        return true; 
    }
    
    return false;
}

void Botao::executar()
{
    hover();
}
