#include "Gerenciadores/Gerenciador_Colisoes.h"


using namespace Gerenciadores;
using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;
using namespace std;


Gerenciador_colisoes::Gerenciador_colisoes() : direita(1),cima(2),esquerda(3),baixo(4)
{

	empurrao = 50.0f;

	lista_Inimigos.clear();
	lista_Obstaculos.clear();
	lista_Projeteis.clear();
	
	pJogador1 = nullptr;
	pJogador2 = nullptr;
}

Gerenciador_colisoes::~Gerenciador_colisoes(){



	lista_Inimigos.clear();
	lista_Obstaculos.clear();
	lista_Projeteis.clear();

	pJogador1 = nullptr;
	pJogador2 = nullptr;
}

void Gerenciador_colisoes::Incluir_Obstaculo(Obstaculo* p_Obstaculo){
	lista_Obstaculos.push_back(p_Obstaculo);
}

void Gerenciador_colisoes::Incluir_Inimigo(Inimigo* p_Inimigo){
	lista_Inimigos.push_back(p_Inimigo);
}

void Gerenciador_colisoes::Incluir_Projetil(Projetil* p_Projetil){
	lista_Projeteis.insert(p_Projetil);
}

void Gerenciador_colisoes::Setar_Jogador(Jogador* p_Jogador1, Jogador* p_Jogador2){

	if (p_Jogador1 != nullptr) {
		pJogador1 = p_Jogador1;
	}
	if (p_Jogador2 != nullptr) {
		pJogador2 = p_Jogador2;
	}
}


void Gerenciadores::Gerenciador_colisoes::projetil_Destruido(Projetil* pProj)
{

	if (pProj != nullptr) {

		//remove diretamente
		lista_Projeteis.erase(pProj);
	}
}



Entidade* Gerenciador_colisoes::Inimigo_neutralizado(Inimigo* inimigo_eliminado)
{
	int i;
	Entidade* aux;

	for (i = 0; i < lista_Inimigos.size(); i++) {
		if (lista_Inimigos[i] == inimigo_eliminado) {
			aux = static_cast<Entidade*>(lista_Inimigos[i]);
			lista_Inimigos.erase(lista_Inimigos.begin() + i);
			return aux;
		}
	}
	return nullptr;
}

//Verifica se a lista de inimigos do gerenciador está vazia
bool Gerenciador_colisoes::verifica_Lista_Inimigos_Vazia()
{
	if (lista_Inimigos.size() == 0) {
		return true;
	}
	else {
		return false;
	}
}

//colisão do jogador com os obstáculos
void Gerenciador_colisoes::tratar_Colisoes_Jogador_Obstaculo(Jogador* p_Jogador) {

	list<Obstaculo*>::iterator itr = lista_Obstaculos.begin();

	//verifica o tipo de colisão especificamente com objetos.
	while (itr != lista_Obstaculos.end()) {

		int lado = verifica_Tipo_De_Colisao(static_cast<Entidade*>(p_Jogador), static_cast<Entidade*>(*itr));

		//direita
		if (lado == 1) {

			p_Jogador->setar_Pos(((*itr)->get_X() - p_Jogador->get_Largura()), p_Jogador->get_Y());
			(*itr)->obstacular(p_Jogador, lado);
		}
		//cima
		else if (lado == 2) {

			p_Jogador->setar_Pos(p_Jogador->get_X(), (*itr)->get_Comprimento_A());
			p_Jogador->setar_No_Ar(true);
			p_Jogador->setar_Estado_Pulando(true);
			p_Jogador->setar_Bateu_A_Cabeca();
			(*itr)->obstacular(p_Jogador, lado);
		}
		//esquerda
		else if (lado == 3) {

			p_Jogador->setar_Pos((*itr)->get_Comprimento_L(), p_Jogador->get_Y());
			(*itr)->obstacular(p_Jogador, lado);
		}
		//baixo
		else if (lado == 4) {

			p_Jogador->setar_Pos(p_Jogador->get_X(), ((*itr)->get_Y() - p_Jogador->get_Altura()));
			p_Jogador->setar_No_Ar(false);
			p_Jogador->setar_Estado_Pulando(false);
			(*itr)->obstacular(p_Jogador, lado);
		}

		itr++;
	}
}

//colisão de projeteis com o jogador
void Gerenciador_colisoes::tratar_Colisoes_Jogador_Projeteis(Jogador* p_Jogador){

	set<Projetil*>::iterator itr;

	itr = lista_Projeteis.begin();

	if (p_Jogador != nullptr) {

		while (itr != lista_Projeteis.end()) {


			if ((*itr)->get_Ativo()) {

				int lado = verifica_Tipo_De_Colisao(static_cast<Entidade*>(p_Jogador), static_cast<Entidade*>(*itr));

				if (lado != 0) {

					(*itr)->Atingiu_Jogador(p_Jogador);
					(*itr)->setar_Ativo(false);
					projetil_Destruido(*itr);
					break;
				}
			}
			itr++;

		}
	}

}

//colisão de qualquer coisa com os obstáculos
void Gerenciador_colisoes::tratar_Colisoes_Obstaculo(Entidade* pEntidadeRef) {

	list<Obstaculo*>::iterator itr;

	itr = lista_Obstaculos.begin();


	//verifica o tipo de colisão especificamente com objetos.
	while (itr != lista_Obstaculos.end()) {

		int lado = verifica_Tipo_De_Colisao(static_cast<Entidade*>(pEntidadeRef), static_cast<Entidade*>(*itr));

		//direita
		if (lado == 1) {

			pEntidadeRef->setar_Pos(((*itr)->get_X() - pEntidadeRef->get_Largura()), pEntidadeRef->get_Y());
		}
		//cima
		else if (lado == 2) {

			pEntidadeRef->setar_Pos(pEntidadeRef->get_X(), (*itr)->get_Comprimento_A());
		}
		//esquerda
		else if (lado == 3) {

			pEntidadeRef->setar_Pos((*itr)->get_Comprimento_L(), pEntidadeRef->get_Y());
		}
		//baixo
		else if (lado == 4) {

			pEntidadeRef->setar_Pos(pEntidadeRef->get_X(), ((*itr)->get_Y() - pEntidadeRef->get_Altura()));
		}

		itr++;
	}
}

//colisão de projeteis com os obstáculos
void Gerenciador_colisoes::tratar_Colisoes_Projeteis(){

	set<Projetil*>::iterator itr_proj;
	list<Obstaculo*>::iterator itr_obst;

	itr_proj = lista_Projeteis.begin();

	while (itr_proj != lista_Projeteis.end()) {

		itr_obst = lista_Obstaculos.begin();

		while (itr_obst != lista_Obstaculos.end()) {

			int lado = verifica_Tipo_De_Colisao(static_cast<Entidade*>(*itr_proj), static_cast<Entidade*>(*itr_obst));

			if (lado != 0) {

				(*itr_proj)->setar_Ativo(false);
				projetil_Destruido(*itr_proj);
			}

			itr_obst++;
		}

		itr_proj++;
	}
}

//trata as colisões entre os inimigos e os outros objetos não em inimigos (ainda)
void Gerenciador_colisoes::tratar_Colisoes_Inimigos(){

	int i;

	for (i = 0; i < lista_Inimigos.size(); i++) {

		if(lista_Inimigos[i] == nullptr){
			continue;
		}

		if (lista_Inimigos[i]->get_Vitalidade() <= 0) {
			std::cout << "entidade " << i << " foi neutralizada" << std::endl;
		}


		if (pJogador2->get_Dois_Jogadores()) {
			tratar_Colisoes_Obstaculo(static_cast<Entidade*>(lista_Inimigos[i]));
			
			tratar_Colisoes_Jogador_Inimigos(pJogador1, lista_Inimigos[i]);
			tratar_Colisoes_Jogador_Inimigos(pJogador2, lista_Inimigos[i]);

		}
		else {
			tratar_Colisoes_Obstaculo(static_cast<Entidade*>(lista_Inimigos[i]));
			tratar_Colisoes_Jogador_Inimigos(pJogador1, lista_Inimigos[i]);
			
		}

	}

}

//trata as colisões entre o jogador e os inimigos
void Gerenciador_colisoes::tratar_Colisoes_Jogador_Inimigos(Jogador* pJogador, Inimigo* pInimigo) {

	int lado = verifica_Tipo_De_Colisao(pInimigo, pJogador);


	//direita
	if (lado == 1) {

		pJogador->setar_Pos(pInimigo->get_Comprimento_L() + empurrao, pJogador->get_Y());
		pInimigo->verifica_Acao_de_Colisao(lado, pJogador);
	}
	//cima
	else if (lado == 2) {

		pJogador->setar_Pos(pJogador->get_X(), (pInimigo->get_Y() - pJogador->get_Altura()));
		pInimigo->verifica_Acao_de_Colisao(lado, pJogador);
		
	}
	//esquerda
	else if (lado == 3) {

		pJogador->setar_Pos((pInimigo->get_X() - pJogador->get_Largura() - empurrao), pJogador->get_Y());
		pInimigo->verifica_Acao_de_Colisao(lado, pJogador);
	}
	//baixo
	else if (lado == 4) {

		pJogador->setar_Pos(pJogador->get_X(), pInimigo->get_Comprimento_A() + empurrao);
		pInimigo->verifica_Acao_de_Colisao(lado, pJogador);
	}

	/*
	//direita
	if (lado == 1) {

		pJogador->setar_Pos((pInimigo->get_X() - pJogador->get_Largura() - empurrao), pJogador->get_Y());
		pInimigo->verifica_Acao_de_Colisao(lado, pJogador);
	}
	//cima
	else if (lado == 2) {

		pJogador->setar_Pos(pJogador->get_X(), pInimigo->get_Comprimento_A() + empurrao);
		pInimigo->verifica_Acao_de_Colisao(lado, pJogador);
	}
	//esquerda
	else if (lado == 3) {

		pJogador->setar_Pos(pInimigo->get_Comprimento_L() + empurrao, pJogador->get_Y());
		pInimigo->verifica_Acao_de_Colisao(lado, pJogador);
	}
	//baixo
	else if (lado == 4) {

		pJogador->setar_Pos(pJogador->get_X(), (pInimigo->get_Y() - pJogador->get_Altura()));
		pInimigo->verifica_Acao_de_Colisao(lado, pJogador);
	}
		*/

}

//Essa classe tem como objetivo Garantir corretamente o lado colidido da entidade referência.
//Primeiro ela verifica as coordenadas principais, depois confirma com as secundárias, referente a colisão respectivamente.
const int Gerenciador_colisoes::verifica_Tipo_De_Colisao(Entidade* pEntidade_Ref, Entidade* pEntidade2) {
	
	float maior = 0;
	int lado = 0;
	bool colisao = false;
	float comprimento_baixo = 0;
	float comprimento_cima = 0;
	float comprimento_direita = 0;
	float comprimento_esquerda = 0;

	//Baixo
	if (verifica_Colisao_Baixo(static_cast<Entidade*>(pEntidade_Ref), static_cast<Entidade*>(pEntidade2))) {

		if ((pEntidade_Ref->get_X() < pEntidade2->get_X()) && (pEntidade_Ref->get_Comprimento_L() > pEntidade2->get_X())) {

			comprimento_baixo = pEntidade_Ref->get_Comprimento_L() - pEntidade2->get_X();
			colisao = true;
		}
		else if ((pEntidade_Ref->get_X() >= pEntidade2->get_X()) && (pEntidade_Ref->get_Comprimento_L() <= pEntidade2->get_Comprimento_L())) {

			comprimento_baixo = pEntidade_Ref->get_Largura();
			colisao = true;
		}

		else if ((pEntidade_Ref->get_X() > pEntidade2->get_X()) && (pEntidade_Ref->get_Comprimento_L() > pEntidade2->get_Comprimento_L())) {
			
			comprimento_baixo = pEntidade2->get_Comprimento_L() - pEntidade_Ref->get_X();
			colisao = true;
		}

	}

	//Cima
	if (verifica_Colisao_Cima(static_cast<Entidade*>(pEntidade_Ref), static_cast<Entidade*>(pEntidade2))) {

		if ((pEntidade_Ref->get_X() < pEntidade2->get_X()) && (pEntidade_Ref->get_Comprimento_L() > pEntidade2->get_X())) {

			comprimento_cima = pEntidade_Ref->get_Comprimento_L() - pEntidade2->get_X();
			colisao = true;
		}
		else if ((pEntidade_Ref->get_X() >= pEntidade2->get_X()) && (pEntidade_Ref->get_Comprimento_L() <= pEntidade2->get_Comprimento_L())){

			comprimento_cima = pEntidade_Ref->get_Largura();
			colisao = true;
		}
		else if ((pEntidade_Ref->get_X() > pEntidade2->get_X()) && (pEntidade_Ref->get_Comprimento_L() > pEntidade2->get_Comprimento_L())) {

			comprimento_cima = pEntidade2->get_Comprimento_L() - pEntidade_Ref->get_X();
			colisao = true;
		}
	}
	
	//Direita
	if (verifica_Colisao_Direita(static_cast<Entidade*>(pEntidade_Ref), static_cast<Entidade*>(pEntidade2))) {

		if ((pEntidade_Ref->get_Y() < pEntidade2->get_Y()) && (pEntidade2->get_Y() < pEntidade_Ref->get_Comprimento_A())) {

			comprimento_direita = pEntidade_Ref->get_Comprimento_A() - pEntidade2->get_Y();
			colisao = true;
		}
		else if ((pEntidade_Ref->get_Y() >= pEntidade2->get_Y()) && (pEntidade_Ref->get_Comprimento_A() <= pEntidade2->get_Comprimento_A()) ) {
			
			comprimento_direita = pEntidade_Ref->get_Altura();
			colisao = true;
		}
		else if ((pEntidade_Ref->get_Y() > pEntidade2->get_Y()) && (pEntidade_Ref->get_Comprimento_A() > pEntidade2->get_Comprimento_A())) {

			comprimento_direita = pEntidade2->get_Comprimento_A() - pEntidade_Ref->get_Y();
			colisao = true;
		}
	}

	//Esquerda
	if (verifica_Colisao_Esquerda(static_cast<Entidade*>(pEntidade_Ref), static_cast<Entidade*>(pEntidade2))) {

		if ((pEntidade_Ref->get_Y() < pEntidade2->get_Y()) && (pEntidade2->get_Y() < pEntidade_Ref->get_Comprimento_A())) {

			comprimento_esquerda = pEntidade_Ref->get_Comprimento_A() - pEntidade2->get_Y();
			colisao = true;
		}
		else if ((pEntidade_Ref->get_Y() >= pEntidade2->get_Y()) && (pEntidade_Ref->get_Comprimento_A() <= pEntidade2->get_Comprimento_A())) {

			comprimento_esquerda = pEntidade_Ref->get_Altura();
			colisao = true;
		}
		else if ((pEntidade_Ref->get_Y() > pEntidade2->get_Y()) && (pEntidade_Ref->get_Comprimento_A() > pEntidade2->get_Comprimento_A())) {

			comprimento_esquerda = pEntidade2->get_Comprimento_A() - pEntidade_Ref->get_Y();
			colisao = true;
		}
	}
	
	// verifica o maior lado em contato da entidade Referência com a colidida e retorna o lado colidido.
	if (colisao) {
		if (maior < comprimento_baixo) {

			maior = comprimento_baixo;
			lado = baixo;
		}

		if (maior < comprimento_cima) {

			maior = comprimento_cima;
			lado = cima;
		}
		if (maior < comprimento_direita) {

			maior = comprimento_direita;
			lado = direita;
		}
		if (maior < comprimento_esquerda) {

			maior = comprimento_esquerda;
			lado = esquerda;
		}
	}

	return lado;
}

//verifica se o objeto esta com possibilidade de colisão.
const bool Gerenciador_colisoes::verifica_Mesma_Pos(Entidade* pEntidade_Ref, Entidade* pEntidade2) {

	bool pos = true;

	// (y > y2 + a) ou (y + a < y2)
	if ((pEntidade_Ref->get_Y() > pEntidade2->get_Comprimento_A()) ||
		(pEntidade_Ref->get_Comprimento_A() < pEntidade2->get_Y())) {
		pos = false;
	}
	// (x > x2 + l) ou (x + l < x2)
	else if ((pEntidade_Ref->get_X() > pEntidade2->get_Comprimento_L()) ||
		(pEntidade_Ref->get_Comprimento_L() < pEntidade2->get_X())) {
		pos = false;
	}

	return pos;
}

//Auto explicativo
const bool Gerenciador_colisoes::verifica_Colisao_Cima (Entidade* pEntidade_Ref, Entidade* pEntidade2) {

	if (!verifica_Mesma_Pos(pEntidade_Ref, pEntidade2)) {
		return false;
	}
	else {

		// (y <= y2 + a) && (y + a >= y2 + a)
		if ((pEntidade_Ref->get_Y() <= pEntidade2->get_Comprimento_A()) &&
			(pEntidade_Ref->get_Comprimento_A() >= pEntidade2->get_Comprimento_A()))
		{
			return true;
		}
	}

	return false;
}

//Auto explicativo
const bool Gerenciador_colisoes::verifica_Colisao_Esquerda(Entidade* pEntidade_Ref, Entidade* pEntidade2) {


	if (!verifica_Mesma_Pos(pEntidade_Ref, pEntidade2)) {
		return false;
	}
	else {

		// (x <= x2 + l) && (x + l >= x2 + l)
		if ((pEntidade_Ref->get_X() <= pEntidade2->get_Comprimento_L()) &&
			(pEntidade_Ref->get_Comprimento_L() >= pEntidade2->get_Comprimento_L()))
		{
			return true;
		}

	}

	return false;
}

//Auto explicativo
const bool Gerenciador_colisoes::verifica_Colisao_Baixo(Entidade* pEntidade_Ref, Entidade* pEntidade2) {

	if (!verifica_Mesma_Pos(pEntidade_Ref, pEntidade2)) {
		return false;
	}
	else {

		//(y + a >= y2) && (y + a <= y2 + h)
		if ((pEntidade_Ref->get_Comprimento_A() >= pEntidade2->get_Y()) &&
			(pEntidade_Ref->get_Comprimento_A() <= pEntidade2->get_Comprimento_A()))
		{
			return true;

		}
	}

	return false;
}

//Auto explicativo
const bool Gerenciador_colisoes::verifica_Colisao_Direita(Entidade* pEntidade_Ref, Entidade* pEntidade2) {

	if (!verifica_Mesma_Pos(pEntidade_Ref, pEntidade2)) {
		return false;
	}
	else {

		// (x <= x2) && (x + l => x2)
		if ((pEntidade_Ref->get_X() <= pEntidade2->get_X()) &&
			(pEntidade_Ref->get_Comprimento_L() >= pEntidade2->get_X()))
		{
			return true;
		}
	}

	return false;
}

void Gerenciador_colisoes::Executar(){

	if (pJogador1 && !(pJogador1->get_Eliminado())) {
		tratar_Colisoes_Jogador_Obstaculo(pJogador1);
		tratar_Colisoes_Jogador_Projeteis(pJogador1);
	}
	if (pJogador2->get_Dois_Jogadores() && !(pJogador2->get_Eliminado())) {
		tratar_Colisoes_Jogador_Obstaculo(pJogador2);
		tratar_Colisoes_Jogador_Projeteis(pJogador2);
	}

	tratar_Colisoes_Inimigos();
	tratar_Colisoes_Projeteis();
}