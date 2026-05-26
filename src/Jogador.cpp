#include"../include/Jogador.h"

Entidades::Personagens::Jogador::Jogador(RectangleShape b, Vector2f pos, Vector2f tam, int life, int p): Personagem(ID::jogador, b, pos, tam, life, 100.0f, 200.f, false), pontos(p),pulo(false),tempoTotal(0)//dano_a_tomar(0) 
{
    carregar();    
}

void Entidades::Personagens::Jogador::carregar()
{
    if (!textura.loadFromFile(JogadorAndar)) {
        std::cout << "ERRO: Não foi possível carregar: " << JogadorAndar << std::endl;
        return;
    }
        
    this->setFiguraAnimada(&textura, 8, body);
    
}

void Entidades::Personagens::Jogador::move(float dt)
{
    // const float gravidade = 1000.f; se torna algo global para todos os personagens
    // const float velocidadePulo = -500.f; vai ser uma variavel global para personagens
    // const float velocidadeCorrida = 200.f; a decidir

    sf::Vector2f velocidade = getVel();
        velocidade.y += gravidade * dt;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        velocidade.x = -velocidadeCorrida;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        
        velocidade.x = velocidadeCorrida;
        
    }
    else {
        velocidade.x = 0;
    }


    if (pulo && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

        velocidade.y = velocidadePulo;

        setPular(false);
    }
    setVel(velocidade);

    setPos(getPos() + velocidade * dt);
}

// void Entidades::Personagens::Jogador::setDanoPorSegundo(float tempo, int dano)
// {
//     tempoTotal = tempo;
//     dano_a_tomar = dano;
//}

void Entidades::Personagens::Jogador::colisao(Entidade *ent, sf::Vector2f inter)
{
    if(ent->getId() == Plataforma){
        sf::Vector2f posOriginal = getPos();

        if(fabs(inter.y) > 0.0f) { 
            
            
            setPos(posOriginal + sf::Vector2f(0.0f, inter.y)); 
            
            
            setVel(sf::Vector2f(getVel().x, 0.0f)); 

            if(inter.y < 0) {
                
                setPular(true);
            }
        } 
        
        else if(fabs(inter.x) > 0.0f) { 

            setPos(posOriginal + sf::Vector2f(inter.x, 0.0f));

            setVel(sf::Vector2f(0.0f, getVel().y));
        }
    }
    // }else if(ent->getId() == lava){
    //     sf::Vector2f posOriginal = getPos();

    //     if(fabs(inter.y) > 0.0f) { 
            
            
    //         setPos(posOriginal + sf::Vector2f(0.0f, inter.y)); 
            
            
    //         setVel(sf::Vector2f(getVel().x, 0.0f)); 

    //         if(inter.y < 0) {
    //             Entidades::Obstaculos::Lava* pLava = static_cast<Entidades::Obstaculos::Lava*>(ent);
    //             setDanoPorSegundo(pLava->getTempo(),pLava->getDano());
    //             setPular(true);

    //         }
    //     } 
        
    //     else if(fabs(inter.x) > 0.0f) { 

    //         setPos(posOriginal + sf::Vector2f(inter.x, 0.0f));

    //         setVel(sf::Vector2f(0.0f, getVel().y));
    //     }
    // } a ser definido
}
void Entidades::Personagens::Jogador::colisao(Entidade *ent, float dt)
{
    static float tempo = 0.f;

    const float cdAtaque = 0.5f;


    if(tempo > 0.f){
        tempo -= dt;
    }else if(tempo <= 0.f){
        if(ent->getId() == inimigo){
            // Entidades::Personagens::Fogo* pFire = static_cast<Entidades::Personagens::Fogo*>(ent);

            // pFire->atacar(this);

        }

        tempo = cdAtaque;
    }
        
}

void Entidades::Personagens::Jogador::executar(float dt)
{  
    move(dt);
    danificar(dt); 
}

void Entidades::Personagens::Jogador::danificar(float dt)
{
    static float tempo = 0.f;

    const float cdAtaque = 1.f;
    
    if(tempoTotal > 0.f){
        if(tempo > 0.f){
            tempo -= dt;
        }else if(tempo <= 0.f){

            vida -= dano_a_tomar;
            tempo = cdAtaque;

        }

    }
    tempoTotal -= dt;
}