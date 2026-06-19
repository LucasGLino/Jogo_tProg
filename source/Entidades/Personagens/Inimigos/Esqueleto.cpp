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

	tamanho.x = 25.0;
	tamanho.y = 55.0;

	pos_inicial.x = 200.f;
	pos_inicial.y = 159.f;

	pos_final = pos_inicial;

	velocidade.x = 0.5f;

	velocidade_maxima = 2 * velocidade.x;

	//pFigura->setFillColor(sf::Color::Red);

	pFigura->setSize(tamanho);
	if (!textura.loadFromFile("assets/Esqueleto.png")) {
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
    desenhar();
	setar_Pos(pos.x, pos.y);

	srand(static_cast<unsigned int>(time(0)));
	int chance_parar = (rand() % 100);
	if(chance_parar <= 40){
		parar = true;
	}else{
		parar = false;
	}
	
	if(!parar){
		if ((pos_final.x != pos.x) && (pos_final.y != pos.y)) {

			if (pos_final.x > pos.x) {
				pos.x += velocidade.x;
			}
			else if (pos_final.x < pos.x) {
				pos.x -= velocidade.x;
			}

		}
	}

	patrulhar();
}

void Entidades::Personagens::Esqueleto::Danificar(Entidades::Personagens::Personagem *pAtacado)
{
    pAtacado->diminuir_Vitalidade(dano);
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

void Entidades::Personagens::Esqueleto::patrulhar()
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

void Entidades::Personagens::Esqueleto::verifica_Acao_de_Colisao(int lado, Entidades::Personagens::Jogador *pJogador)
{
    if (lado == lado_fraco) {
		pJogador->danificar(static_cast<Personagem*>(this));
        aumentar_Forca();

		if(get_Eliminado()){
			pJogador->aumentar_Pontuacao(pontos_de_eliminacao);
		}
	}
	else {

		danificar(static_cast<Personagem*>(pJogador));
	}
}

void Entidades::Personagens::Esqueleto::setar_Pontos_Por_Eliminacao(int pontos)
{
    pontos_de_eliminacao = pontos;
}
