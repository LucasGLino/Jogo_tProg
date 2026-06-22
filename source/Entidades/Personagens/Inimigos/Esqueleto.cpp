#include "Entidades/Personagens/Inimigos/Esqueleto.h"

Entidades::Personagens::Esqueleto::Esqueleto()
{
    srand(static_cast<unsigned int>(time(0)));

	nivel_maldade = (rand() % 3);
	forca = 0;

	//num_vitalidade = 100;
	vitalidade = 80;
	dano = 5*nivel_maldade;

	patrulha_esq_concluida = false;
	patrulha_dir_concluida = true;
	patrulhando = true;
	preparando_investida = false;
	investindo = false;

	tamanho.x = 25.0;
	tamanho.y = 55.0;

	pos_inicial.x = 200.f;
	pos_inicial.y = 159.f;

	pos_final = pos_inicial;

	velocidade.x = 0.5f;

	velocidade_maxima = 3 * velocidade.x;
	pos_inicio_investida = pos.x;
	investidas_restantes = 0;

	relogio_parada.restart();

	//pFigura->setFillColor(sf::Color::Red);

	pFigura->setSize(tamanho);
	if (!textura.loadFromFile("Assets/Imagens/Esqueleto.png")) {
		std::cout << "Erro ao carregar textura do esqueleto." << std::endl;
		pFigura->setFillColor(sf::Color::Magenta);
	}
	else {
		pFigura->setFillColor(sf::Color::White);
		pFigura->setTexture(&textura);
	}
	pFigura->setPosition(pos_inicial);

	setar_Pontos_Por_Eliminacao(400);
}

void Entidades::Personagens::Esqueleto::andar_ate(float em_x, float em_y)
{
    pos_final.x = em_x;
	pos_final.y = em_y;
}

Entidades::Personagens::Esqueleto::~Esqueleto()
{
}

void Entidades::Personagens::Esqueleto::salvar()
{
}

void Entidades::Personagens::Esqueleto::executar()
{

	executar_Gravidade();
	
	desenhar();
	setar_Pos(pos.x, pos.y);

	if(preparando_investida || investindo){
		executar_Investida();
	}
	else {
		verificar_Parada();
		mover();

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

void Entidades::Personagens::Esqueleto::setar_Patrulha(float patrulha_esq, float patrulha_dir)
{
    if(rand()%2 == 1){
		patrulha_dir_concluida = false;
		patrulha_esq_concluida = true;
	}
	else{
		patrulha_dir_concluida = true;
		patrulha_esq_concluida = false;
	}

	patrulha_esquerda = patrulha_esq;
	patrulha_direita = patrulha_dir - get_Largura();
	patrulhando = true;
	parar = false;
}

void Entidades::Personagens::Esqueleto::mover()
{
    if(patrulhando) {

		if(!patrulha_esq_concluida && patrulha_dir_concluida){

			pos_final.x = patrulha_esquerda;
		}
		else if(patrulha_esq_concluida && !patrulha_dir_concluida){

			pos_final.x = patrulha_direita;
		}

		if(pos.x <= patrulha_esquerda){

			patrulha_esq_concluida = true;
			patrulha_dir_concluida = false;
		}
		else if(pos.x >= patrulha_direita ){
			
			patrulha_esq_concluida = false;
			patrulha_dir_concluida = true;
		}
	}
}

void Entidades::Personagens::Esqueleto::aumentar_Forca()
{
    forca += 5;
}

void Entidades::Personagens::Esqueleto::colidiu_Obstaculo(int lado)
{
	if(lado == direita){
		patrulha_esq_concluida = false;
		patrulha_dir_concluida = true;
	}
	else if(lado == esquerda){
		patrulha_esq_concluida = true;
		patrulha_dir_concluida = false;
	}
}

void Entidades::Personagens::Esqueleto::danificar(int lado, Entidades::Personagens::Jogador *pJogador)
{
    if (lado == lado_fraco) {
		pJogador->colidir(static_cast<Personagem*>(this));
        aumentar_Forca();

		if(get_Eliminado()){
			pJogador->aumentar_Pontuacao(pontos_de_eliminacao);
		}
		else {
			iniciar_Investida_Apos_Dano(pJogador);
		}
	}
	else {

		pJogador->diminuir_Vitalidade(dano);
	}
}

void Entidades::Personagens::Esqueleto::preparar_Investida()
{
	if(!preparando_investida && !investindo){
		preparando_investida = true;
		investindo = false;
		patrulhando = false;
		parar = true;
		pos_inicio_investida = pos.x;
		relogio_investida.restart();
	}
}

void Entidades::Personagens::Esqueleto::iniciar_Investida_Apos_Dano(Entidades::Personagens::Jogador *pJogador)
{
	if(pJogador != nullptr && !preparando_investida && !investindo){
		if(pJogador->get_X() > pos.x){
			direcao = esquerda;
		}
		else{
			direcao = direita;
		}

		investidas_restantes = 2;
		preparar_Investida();
	}
}

void Entidades::Personagens::Esqueleto::executar_Investida()
{
	const float tempo_preparo_investida = 0.6f;
	const float distancia_maxima_investida = 140.f;

	if(preparando_investida){
		if(relogio_investida.getElapsedTime().asSeconds() >= tempo_preparo_investida){
			preparando_investida = false;
			investindo = true;
			parar = false;
		}
		return;
	}

	if(investindo){
		if(direcao == direita){
			pos.x += velocidade_maxima;
		}
		else if(direcao == esquerda){
			pos.x -= velocidade_maxima;
		}

		float distancia_percorrida = pos.x - pos_inicio_investida;
		if(distancia_percorrida < 0.f){
			distancia_percorrida *= -1.f;
		}

		if(distancia_percorrida >= distancia_maxima_investida || pos.x <= patrulha_esquerda || pos.x >= patrulha_direita){
			investidas_restantes--;

			if(investidas_restantes > 0){
				if(direcao == direita){
					direcao = esquerda;
				}
				else{
					direcao = direita;
				}

				preparando_investida = true;
				investindo = false;
				parar = true;
				pos_inicio_investida = pos.x;
				relogio_investida.restart();
			}
			else {
				encerrar_Investida();
			}
		}
	}
}

void Entidades::Personagens::Esqueleto::encerrar_Investida()
{
	preparando_investida = false;
	investindo = false;
	investidas_restantes = 0;
	patrulhando = true;
	parar = false;
	relogio_parada.restart();
}

void Entidades::Personagens::Esqueleto::verificar_Parada()
{
	const float intervalo_sorteio = 2.0f;
	const float duracao_parada = 0.7f;

	if(parar){
		if(relogio_parada.getElapsedTime().asSeconds() >= duracao_parada){
			parar = false;
			relogio_parada.restart();
		}
	}
	else {
		if(relogio_parada.getElapsedTime().asSeconds() >= intervalo_sorteio){
			int chance_parar = (rand() % 100);

			if(chance_parar <= 40){
				parar = true;
			}

			relogio_parada.restart();
		}
	}
}

void Entidades::Personagens::Esqueleto::setar_Pontos_Por_Eliminacao(int pontos)
{
    pontos_de_eliminacao = pontos;
}
