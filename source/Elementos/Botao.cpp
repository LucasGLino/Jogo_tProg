#include "Elementos/Botao.h"


#define corBotao sf::Color::Transparent

#define bHover sf::Color(10, 150, 150, 255)


Botao::Botao(const std::string& stri, const sf::Font& fonte, sf::Vector2f pos):str(stri, fonte, 30), press(false),troca_cor(false)
{    

    pGg = Gerenciadores::Gerenciador_Grafico::getInstancia();
    
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
void Botao::hover_selecionado()
{
    if(troca_cor){
        this->str.setFillColor(sf::Color::Blue);
    }else{
        this->str.setFillColor(sf::Color::Yellow);
    }
}
void Botao::set_troca_cor(bool c)
{
    troca_cor = c;
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
    hover_selecionado();
}
