#include "Entidades/Personagens/Jogador/Jogador.h"

using namespace Entidades;
using namespace Personagens;


const int Jogador::id_base(10);

/*
Jogador::Jogador() : Personagem(id_base) {

	//arrumar isso posteriormente
	//setId(semente_id_entidade);

	segundo_jogador = false;
	estado_pulando = false;
	no_ar = false;
	estado_caindo = true;

	vida = 100;

	dano = 70;

	gravidade = 6.0f;

	tamanho.x = 20;
	tamanho.y = 40;

	pos.x = 0.f;
	pos.y = (pGG->getCamera()->getSize().y/3);

	setVida(100);
	setar_Figura();
	setar_Pos(pos.x,pos.y);

	forca_de_impulso = -9.0;
	acelerando = false;
	
	//altura_de_pulo = 50.0;
	
	velocidade.y = -5.0;
	velocidade.x = 3.0;
	//velocidade.y = 5.0;

	pontos = 0;
}
*/

//Jogador::Jogador(int semente, sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely):
Jogador::Jogador(sf::Vector2f p, sf::Vector2f tam, int vida, float velx, float vely):
	Personagem(id_base, p, tam, vida, velx, vely) 
{
	//arrumar isso posteriormente
	//setId(semente_id_entidade);

	segundo_jogador = false;
	estado_pulando = false;
	no_ar = false;
	estado_caindo = true;

	vitalidade = vida;

	dano = 70;

	gravidade = 6.0f;

	pos = p;
	tamanho = tam;

	set_Vitalidade(vida);
	setar_Figura();
	setar_Pos(pos.x, pos.y);

	forca_de_impulso = -9.0;
	acelerando = false;
	
	//altura_de_pulo = 50.0;
	
	velocidade.y = vely;
	velocidade.x = velx;
	//velocidade.x = 3.0f;
	//velocidade.y = -5.0;

	pontos = 0;
}

Jogador::~Jogador() {

}

void Jogador::Executar() {


	if (!eliminado) {

		executar_Gravidade();

		Desenhar();
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

void Jogador::setar_Estado_Pulando(bool estado){
	estado_pulando = estado;
}

bool Jogador::get_Eliminado() const
{
	return eliminado;
}

void Entidades::Personagens::Jogador::executar_Gravidade() {

	if (velocidade.y <= forca_de_impulso) {
		acelerando = false;
	}

	if (estado_pulando) {
		if (acelerando) {
			velocidade.y -= 0.3f;
		}
		else {
			velocidade.y += 0.3f;
		}
		//velocidade.y += 1.5f;
	}

	else if (velocidade.y <= gravidade) {
		//pos.y += velocidade.y;
		velocidade.y += 1.5f;
		//velocidade.y = gravidade;
	}
	if (velocidade.y > gravidade) {
		velocidade.y = gravidade;
	}

	pos.y += velocidade.y;
}


void Jogador::setar_Dois_Jogadores(bool jogador_dois) {

	if (jogador_dois) {
		segundo_jogador = jogador_dois;
		//pFigura->setFillColor(sf::Color::Cyan);
		if (!textura.loadFromFile("assets/Jogador_2.png")) {
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

void Jogador::Salvar(){

}

void Jogador::salvar(){
	Salvar();
}

void Jogador::executar(){
	Executar();
}


void Jogador::danificar(Personagem* pAtacado) {

	pAtacado->diminuir_Vida(dano);
	setar_Estado_Pulando(false);
	setar_No_Ar(false);
	executando_Pulo();
}


void Jogador::diminuir_Vitalidade(int dano) {

	vitalidade -= dano;
	if (vitalidade <= 0) {
		vitalidade = 0;
		eliminado = true;
	}
	std::cout << "Jogador " << getId() << " tomou " << dano << " de dano. Vitalidade atual: " << vitalidade << std::endl;

	if (eliminado) {
		std::cout << "Jogador " << getId() << " foi eliminado!" << std::endl;
	}
}

// adicionar em classes primordiais? tais como Ente ou Entidades?
void Jogador::setar_Figura() {

	pFigura->setSize(tamanho);
	//pFigura->setFillColor(sf::Color::Blue);
	if (!textura.loadFromFile("assets/Jogador_1.png")) {
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

void Jogador::setar_No_Ar(bool no_meio_do_ar){

	no_ar = no_meio_do_ar;
}

void Jogador::setar_Bateu_A_Cabeca(){
	
	velocidade.y = 0;
	acelerando = false;
}






/*
#include <cmath>

using namespace Entidades::Personagens;
using namespace sf;


//Entidades::Personagens::Jogador::Jogador(RectangleShape b, Vector2f pos, Vector2f tam, int life, int p): Personagem, pos, tam, life, 100.0f, 200.f, false), pontos(p),pulo(false),tempoTotal(0)//dano_a_tomar(0) 
//{
    //salvar();    
//}


Jogador::Jogador(int semente, Vector2f pos, Vector2f tam, int life, int p):
    Personagem(semente, pos, tam, life, 100.0f, 200.f),
    pontos(p),
    tempoTotal(0),
    cdDano(0),
    podePular(false),
    status(false),
    velAtual(0.f, 0.f)
{
    salvar();
}


//void Entidades::Personagens::Jogador::carregar()

void Jogador::salvar()
{
    // if (!textura.loadFromFile(JogadorAndar)) {
    //     std::cout << "ERRO: Não foi possível carregar: " << JogadorAndar << std::endl;
    //     return;
    // }
        
    // this->setFiguraAnimada(&textura, 8, body); dependendo de como funcionar subir essa função para Entidade
    
}

Jogador::~Jogador()
{
}

int Jogador::getPontos()
{
    return pontos;
}

void Jogador::setPular(bool p)
{
    //this->pulo = p;
    podePular = p;
}

bool Jogador::getPular()
{
    //return pulo;
    return podePular;
}

const int Jogador::getPontos() const
{
    return pontos;
}

void Jogador::move(float dt)
{

    const float velocidadeCorrida = 200.f;

    //sf::Vector2f velocidade = getVel();
    velAtual = velocidade;
    velAtual.y += gravidade * dt;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        velAtual.x = -velocidadeCorrida;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        
        velAtual.x = velocidadeCorrida;
        
    }
    else {
        velAtual.x = 0;
    }


    //if (pulo && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    if (podePular && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

        velAtual.y = pulo;

        setPular(false);
    }
    //setVel(velocidade);
    setar_velocidade(velAtual.x, velAtual.y);

    //setPos(getPos() + velocidade * dt);
    setar_Pos(getPos() + velAtual * dt);
}

// void Entidades::Personagens::Jogador::setDanoPorSegundo(float tempo, int dano)
// {
//     tempoTotal = tempo;
//     dano_a_tomar = dano;
//}

void Jogador::colisao(Entidades::Entidade *ent, sf::Vector2f inter)
{
    //if(ent->getId() == Plataforma){
    if(ent != NULL){
        sf::Vector2f posOriginal = getPos();

        if(std::fabs(inter.y) > 0.0f) { 
            
            
            //setPos(posOriginal + sf::Vector2f(0.0f, inter.y)); 
            setar_Pos(posOriginal + sf::Vector2f(0.0f, inter.y)); 
            
            
            //setVel(sf::Vector2f(getVel().x, 0.0f)); 
            setar_velocidade(velocidade.x, 0.0f); 

            if(inter.y < 0) {
                
                setPular(true);
            }
        } 
        
        else if(std::fabs(inter.x) > 0.0f) { 

            //setPos(posOriginal + sf::Vector2f(inter.x, 0.0f));
            setar_Pos(posOriginal + sf::Vector2f(inter.x, 0.0f));

            //setVel(sf::Vector2f(0.0f, getVel().y));
            setar_velocidade(0.0f, velocidade.y);
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
    // a ser definido
}
void Jogador::colisao(Entidades::Entidade *ent, float dt)
{
    static float tempo = 0.f;

    const float cdAtaque = 0.5f;

    if(ent == NULL){
        return;
    }

    if(tempo > 0.f){
        tempo -= dt;
    }else if(tempo <= 0.f){
        
        //if(ent->getId() == inimigo){
        
        if(false){
            // Entidades::Personagens::Fogo* pFire = static_cast<Entidades::Personagens::Fogo*>(ent);

            // pFire->atacar(this);

        }

        tempo = cdAtaque;
    }
        
}

void Jogador::executar(float dt)
{  
    move(dt);
    danificar(dt); 
}

void Jogador::danificar(float dt)
{
    static float tempo = 0.f;

    const float cdAtaque = 1.f;
    
    if(tempoTotal > 0.f){
        if(tempo > 0.f){
            tempo -= dt;
        }else if(tempo <= 0.f){

            // vida -= dano_a_tomar;
            tempo = cdAtaque;

        }

    }
    tempoTotal -= dt;
}

*/
