#include "Entidades/Personagens/Inimigos/Capitao.h"

using namespace Entidades;
using namespace Personagens;

// Configura vida, tiro, visao e textura do capitao.
Capitao::Capitao(): recarga(0), espera(240)
{
	num_vidas = 200;
	dano = 20;
	forca = 15;
	lado_fraco = cima;
	disparou = false;
	pode_disparar = true;

	tamanho.x = 35.0f;
	tamanho.y = 65.0f;

	pos_inicial.x = 0.f;
	pos_inicial.y = 0.f;
	pos_final = pos_inicial;

	velocidade.x = 2.0f;
	velocidade_proj.x = 3.0f;
	velocidade_proj.y = 0.0f;

	visao.x = 200.f;
	visao.y = tamanho.y * 1.5f;

	pFigura->setSize(tamanho);
	if (!textura.loadFromFile("Assets/Imagens/Capitao.png")) {
		std::cout << "Erro ao carregar textura do capitao." << std::endl;
		pFigura->setFillColor(sf::Color::Magenta);
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
	pFigura->setPosition(pos_inicial);

	setar_Pontos_Por_Eliminacao(400);
}

// Limpa a lista auxiliar de projeteis.
Capitao::~Capitao()
{
	disparos.clear();
	pode_disparar = false;
	disparou = false;
}

// Informa para a fase se precisa criar projetil.
bool Capitao::get_Disparou() const
{
	return disparou;
}

// Ativa e posiciona o projetil criado pela fase.
void Capitao::incluir_Projetil(Projetil* projet)
{
	if (projet == nullptr) {
		return;
	}

	projet->setar_Ativo(true);
	projet->setar_Direcao(direcao);
	projet->setar_Dano(forca);
	projet->setar_velocidade(velocidade_proj.x, velocidade_proj.y);

	if (direcao == esquerda) {
		projet->setar_Pos(pos.x - projet->get_Largura(), pos.y);
	}
	else if (direcao == direita) {
		projet->setar_Pos(pos.x + get_Largura(), pos.y);
	}

	disparos.push_back(projet);
}

// Tira o projetil da lista auxiliar do capitao.
void Capitao::remover_Projetil(Projetil* projet)
{
	if (projet == nullptr) {
		return;
	}

	std::vector<Entidades::Projetil*>::iterator itr;
	itr = disparos.begin();

	while (itr != disparos.end()) {
		if ((*itr)->getId() == projet->getId()) {
			disparos.erase(itr);
			break;
		}
		itr++;
	}
}

// Retorna a lista usada pela fase para limpar projeteis inativos.
std::vector<Projetil*>* Capitao::get_Vetor_De_Projetis()
{
	return &disparos;
}

// Atualiza gravidade, movimento e recarga do tiro.
void Capitao::executar()
{
	if(!get_Eliminado()){
		executar_Gravidade();
		desenhar();
		disparou = false;
		setar_Pos(pos.x,pos.y);
		mover();

		if (pode_disparar) {
			if (recarga < espera) {
				recarga++;
			}
			else if (recarga >= espera && !disparou){
				disparou = true;
				recarga = 0;
			}
		}

		if(!parar){
			if (pos_final.x != pos.x) {
				if (pos_final.x > pos.x) {
					pos.x += velocidade.x;
				}
				else if (pos_final.x < pos.x) {
					pos.x -= velocidade.x;
				}
			}
		}
	}
}

// Salvar ainda nao foi implementado para capitao.
void Capitao::salvar()
{
}

// Jogador causa dano pelo lado fraco, senao toma dano.
void Capitao::danificar(int lado, Jogador* pJogador)
{
	if(lado == lado_fraco){
		pJogador->colidir(static_cast<Personagem*>(this));

		if(get_Eliminado()){
			pJogador->aumentar_Pontuacao(pontos_de_eliminacao);
		}
	}
	else {
		pJogador->diminuir_Vitalidade(dano);
	}
}

// Verifica se algum jogador esta na visao do capitao.
void Capitao::mover()
{
	pode_disparar = false;
	parar = true;
	andar_ate(pos.x,pos.y);

	if((ponteiro_jogador1->get_X() > (get_Centro().x - visao.x)) && (ponteiro_jogador1->get_X() < (get_Centro().x + visao.x)) &&
	   (ponteiro_jogador1->get_Y() > (get_Centro().y - visao.y)) && (ponteiro_jogador1->get_Y() < (get_Centro().y + tamanho.y/2))){

		setar_direcao();
		pode_disparar = true;
		andar_ate(ponteiro_jogador1->get_Centro().x, ponteiro_jogador1->get_Centro().y);
		parar = false;
	}
	else if(ponteiro_jogador2 != nullptr &&
	        (ponteiro_jogador2->get_X() > (get_Centro().x - visao.x)) && (ponteiro_jogador2->get_X() < (get_Centro().x + visao.x)) &&
	        (ponteiro_jogador2->get_Y() > (get_Centro().y - visao.y)) && (ponteiro_jogador2->get_Y() < (get_Centro().y + tamanho.y/2))){

		setar_direcao();
		pode_disparar = true;
		andar_ate(ponteiro_jogador2->get_Centro().x, ponteiro_jogador2->get_Centro().y);
		parar = false;
	}
}

// Desvia ao bater de lado em obstaculo.
void Capitao::colidiu_Obstaculo(int lado)
{
	if(lado == direita){
		direcao = esquerda;
		andar_ate(pos.x - 80.f, pos.y);
		parar = false;
	}
	else if(lado == esquerda){
		direcao = direita;
		andar_ate(pos.x + 80.f, pos.y);
		parar = false;
	}
}

// Guarda a pontuacao dada ao jogador quando o capitao morre.
void Capitao::setar_Pontos_Por_Eliminacao(int pontos)
{
	pontos_de_eliminacao = pontos;
}
