#include "Entidades/Personagens/Inimigos/Capitao.h"

using namespace Entidades;
using namespace Personagens;

Capitao::Capitao(): recarga(0), espera(240){

	//num_vitalidade = 200;
	vitalidade = 200;
	
	dano = 20;
	dano_do_balote = 15;

	lado_fraco = cima;

	disparou = false;
	pode_disparar = true;

	tamanho.x = 35.0;
	tamanho.y = 65.0;

	pos_inicial.x = 0.f;
	pos_inicial.y = 0.f;

	pos_final = pos_inicial;

	velocidade.x = 2.0f;

	velocidade_proj.x = 3.0f;
	velocidade_proj.y = 0.0f;

	visao.x = 200.f;
	visao.y = (tamanho.y*1.5f);

	//pFigura->setFillColor(sf::Color::Magenta);

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

Capitao::~Capitao(){

	disparos.clear();
	pode_disparar = false;
	disparou = false;
}

const bool Capitao::get_Disparou()
{
	return disparou;
}


void Entidades::Personagens::Capitao::incluir_Projetil(Projetil* projet) {

	projet->setar_Ativo(true);
	projet->setar_Direcao(direcao);
	projet->setar_Dano(dano_do_balote);
	projet->setar_Proprietario(static_cast<Entidade*>(this));
	projet->setar_velocidade(velocidade_proj.x, velocidade_proj.y);


	if (direcao == esquerda) {
		//projet->setar_Pos((pos.x - projet->get_Largura()), (this->get_Centro().y - projet->get_Centro().y));
		projet->setar_Pos((pos.x - projet->get_Largura()), (pos.y));
	}
	else if (direcao == direita) {
		//projet->setar_Pos((pos.x + this->get_Largura()), (this->get_Centro().y - projet->get_Centro().y));
		projet->setar_Pos((pos.x + this->get_Largura()), (pos.y));
	}

	//std::cout << "Incluiu projetil ID " << projet->getId() << " na pos (" << projet->get_X() << "," << projet->get_Y() << ")" << std::endl;

	disparos.push_back(projet);
	//imprime_Projeteis_Ids_Ativos_e_Pos();
}

void Capitao::remover_Projetil(Projetil* projet) {

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

std::vector<Projetil*>* Capitao::get_Vetor_De_Projetis(){

	return &disparos;
}

void Capitao::executar() {


	if(!get_Eliminado()){

		executar_Gravidade();

		desenhar();
		disparou = false;
		setar_Pos(pos.x,pos.y);
		

		if (pode_disparar) {

			if (recarga < espera) {
				recarga++;
			}
			else if (recarga >= espera && !disparou){

				disparou = true;
				// << "Disparou, pos (" << pos.x << "," << pos.y << ") direcao " << direcao << std::endl;

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

		sondando_Por_Jogadores();
	}
	
}

void Capitao::imprime_Projeteis_Ids_Ativos_e_Pos() {

	for (int i = 0; i < disparos.size(); i++) {
		if (disparos[i]->get_Ativo()) {
			std::cout << "  Projetil ID: " << disparos[i]->getId() << " Pos (" << disparos[i]->get_X() << "," << disparos[i]->get_Y() << ")" << std::endl;
		}
	}
}


void Capitao::salvar() {

}


void Capitao::danificar(int lado, Jogador* pJogador){

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

void Capitao::setar_Pontos_Por_Eliminacao(int pontos){

	pontos_de_eliminacao = pontos;
}

void Capitao::sondando_Por_Jogadores(){

	//verifica se está dentro da visão em X 
	if((ponteiro_jogador1->get_X() > (get_Centro().x - visao.x)) && (ponteiro_jogador1->get_X() < (get_Centro().x + visao.x))){

		// verifica se está na mesma altura, apartir do seu pé até o alcance de visão em Y para cima.
		if((ponteiro_jogador1->get_Y() > (get_Centro().y - visao.y)) && (ponteiro_jogador1->get_Y() < (get_Centro().y + tamanho.y/2)))
		{
			setar_direcao();
			pode_disparar = true;
			this->andar_ate(ponteiro_jogador1->get_Centro().x, ponteiro_jogador1->get_Centro().y);
			parar = false;
		}
	}

	//verifica se está dentro da visão em X
	else if((ponteiro_jogador2->get_X() > (get_Centro().x - visao.x)) && (ponteiro_jogador2->get_X() < (get_Centro().x + visao.x))){

		// verifica se está na mesma altura, apartir do seu pé até o alcance de visão em Y para cima.
		if((ponteiro_jogador2->get_Y() > (get_Centro().y - visao.y)) && (ponteiro_jogador2->get_Y() < (get_Centro().y + tamanho.y/2)))
		{
			setar_direcao();
			pode_disparar = true;
			this->andar_ate(ponteiro_jogador2->get_Centro().x, ponteiro_jogador2->get_Centro().y);
			parar = false;
		}
	}

	else {

		parar = true;
		pode_disparar = false;
		andar_ate(pos.x,pos.y);
	}
	
}
