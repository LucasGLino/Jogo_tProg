#include "Fases/Fase_1.h"

using namespace Entidades;
using namespace Personagens;
using namespace Fases;
using namespace Obstaculos;
using namespace Gerenciadores;

Fases::Fase_1::Fase_1() {

	//srand(static_cast<unsigned int>(time(0)));
	
	i = 0;
	j = 0;

	// entre 3 e 10
	num_esqueletos = (rand() % 7) + 3;

	//entre 3 e 8
	num_piratas = (rand() % 5) + 3;
	//num_piratas = 0;

	//entre 3 a 4
	num_caixas = (rand()%1) + 3;
	//num_espinhos = 0;

	num_restante_esqueletos = num_esqueletos;
	num_restante_piratas = num_piratas;
	num_restante_caixas = num_caixas;

	zoom_camera = 1.3f;

	

	num_plataformas_totais = rand() % 10;

	num_max_andares = 4;

	tam_Piso_Fase.x = pGG->getCamera()->getSize().x * zoom_camera;
	tam_Piso_Fase.y = pGG->getCamera()->getSize().y / 3.f;

	pos_Piso.x = 0.f;
	pos_Piso.y = tam_Piso_Fase.y;


	tamanho_da_tela_x = pGG->getCamera()->getSize().x * zoom_camera;
	espaco_vazio_x = 0;

	num_max_plataformas = 10;

	fundo_carregado = false;
	if (!textura_fundo.loadFromFile("Assets/Imagens/Fundo_fase2.png")) {
		std::cout << "Erro ao carregar textura do fundo da fase 2." << std::endl;
	}
	else {
		fundo.setTexture(textura_fundo);
		fundo_carregado = true;
	}
	
	
	setar_Camera_Fase();
	ajustar_Fundo_A_Camera();
	Cria_Obstaculos();

	// precisa ser antes que Cria Obstaculos, justamente pq precisa ser setado os inimigos nas plataformas primeiro.
	Cria_Inimigos();

	//lista_Entidades.imprimir_Ids();
}

void Fases::Fase_1::ajustar_Fundo_A_Camera()
{
	if (!fundo_carregado) {
		return;
	}

	sf::Vector2u tam_fundo = textura_fundo.getSize();

	if (tam_fundo.x == 0 || tam_fundo.y == 0) {
		return;
	}

	sf::Vector2f tam_camera = pGG->getCamera()->getSize();
	sf::Vector2f centro_camera = pGG->getCamera()->getCenter();

	fundo.setPosition(centro_camera.x - (tam_camera.x / 2.f), centro_camera.y - (tam_camera.y / 2.f));
	fundo.setScale(tam_camera.x / static_cast<float>(tam_fundo.x), tam_camera.y / static_cast<float>(tam_fundo.y));
}

Fases::Fase_1::~Fase_1(){

	num_plataformas_por_andar.clear();
}


void Fases::Fase_1::Cria_Obstaculos(){

	Cria_Piso();
	Posiciona_plataforma();
}

void Fases::Fase_1::executar(){

	verifica_Inimigos_Neutralizados();

	if (!ganhou) {
		if (fundo_carregado) {
			pGG->getJanela()->draw(fundo);
		}

		gerenciador_colisoes.Executar();
		lista_Entidades.percorrer();

		// for (i = 0; i < lista_cap.size(); i++) {

		// }

	}

}

void Fases::Fase_1::Cria_Inimigos(){


	sf::Vector2f aux;
	Esqueleto aux_esq;
	Pirata aux_pirata;

	for(i=0;i<num_restante_esqueletos;i++){

		aux.x = pos_Piso.x + (rand() % static_cast<int>(tam_Piso_Fase.x));
		aux.y = pos_Piso.y;

		Cria_Esqueletos(aux.x, aux.y, pos_Piso.x, tam_Piso_Fase.x);
	}

	for(i = 0; i<num_restante_piratas; i++){

		aux.x = pos_Piso.x + (rand() % static_cast<int>(tam_Piso_Fase.x));
		aux.y = pos_Piso.y;

		Cria_Pirata(aux.x, aux.y, pos_Piso.x, tam_Piso_Fase.x);
	}
}

//cria o inimigo dificil (Boss)
void Fase_1::Cria_Esqueletos(float x, float y,float patrulha_ate_a, float patrula_ate_b){

	Esqueleto* esqueleto;
	esqueleto = new Esqueleto;

	esqueleto->setar_Patrulha(patrulha_ate_a, patrula_ate_b);

	lista_id_inimigos.push_front(esqueleto->getId());
	gerenciador_colisoes.Incluir_Inimigo(esqueleto);
	lista_Entidades.adicionar(static_cast<Entidade*>(esqueleto));
}

void Fases::Fase_1::setar_Camera_Fase()
{
	pGG->getCamera()->zoom(zoom_camera);
}

// void Fases::Fase_1::atualiza_Camera_Fase(Jogador* p_jogador1, Jogador* p_jogador2)
// {
// 	sf::Vector2f pos_camera;

// 	pos_camera.x = tam_Piso_Fase.x/2;
// 	pos_camera.y = -tam_Piso_Fase.y/3;

// 	//trava a camera;
// 	pGG->getCamera()->setCenter(pos_camera);
// 	ajustar_Fundo_A_Camera();

// }

void Fases::Fase_1::seta_Tamanho_Plataformas(int n_plataformas) {

	if(n_plataformas == 1){

		//70% do tamanho da tela.
		tam_plataforma.x = tamanho_da_tela_x*0.7f;
		espaco_vazio_x = static_cast<float>((tamanho_da_tela_x*0.3)/2);
	}
	else if(n_plataformas == 2){

		//35% do tamanho da tela
		tam_plataforma.x = tamanho_da_tela_x*0.35f;
		espaco_vazio_x = static_cast<float>((tamanho_da_tela_x*0.3)/3);
	}
	else if(n_plataformas == 3){

		//25% do tamanho da tela
		tam_plataforma.x = tamanho_da_tela_x*0.25f;
		espaco_vazio_x = static_cast<float>((tamanho_da_tela_x*0.25)/4);
	}
	else if(n_plataformas == 4){

		//15% do tamanho da tela
		tam_plataforma.x = tamanho_da_tela_x*0.15f;
		espaco_vazio_x = static_cast<float>((tamanho_da_tela_x*0.4)/5);
	}
	else {

		tam_plataforma.x = 0.0;
		espaco_vazio_x = 0.0;
	}
}

void Fases::Fase_1::seta_Num_Plataformas(){

	if (num_plataformas_totais < 5) {
		num_plataformas_totais = 5;
	}

	std::cout << "numero de plataformas "<< num_plataformas_totais << std::endl;

	int plataformas = 0;
	int plataformas_restantes = num_plataformas_totais;

	tam_plataforma.x = 0.f;

	//pode ter andares vazios, des que sejam os ultimos.
	int num_min_plataformas_andar = 1;

	for (i = 0; i<num_max_andares;i++) {

		//verifica se ainda tem plataformas para por
		if(plataformas_restantes > 0) {

			plataformas = num_min_plataformas_andar + (rand() % 3);

			//verifica se as plataformas que for por não são maiores do que as permitidas
			if(plataformas >= plataformas_restantes) {

				plataformas = plataformas_restantes; 
			}
			
		}
		else {
			//zera todos os valores do vetor então.
			plataformas = 0;
		}

		num_plataformas_por_andar.push_back(plataformas);
		plataformas_restantes -= plataformas;
	}


}

void Fases::Fase_1::Posiciona_plataforma() {

    seta_Num_Plataformas();

	sf::Vector2f pos_plataforma;
	float posicao_da_ultima_plataforma = 0.f;
	
	for(i=0; i < num_max_andares; i++) {

		for (j = 0; j < num_plataformas_por_andar[i]; j++){

			seta_Tamanho_Plataformas(num_plataformas_por_andar[i]);

			pos_plataforma.y = pos_Piso.y - ((i + 1)* 180.f);
			pos_plataforma.x = posicao_da_ultima_plataforma + espaco_vazio_x;
			posicao_da_ultima_plataforma = pos_plataforma.x + tam_plataforma.x;


			std::cout << "andar : " << i << " " <<"Criando plataforma: " << pos_plataforma.x << " " << pos_plataforma.y << std::endl;

			Cria_Plataforma(tam_plataforma.y, tam_plataforma.x, pos_plataforma.x, pos_plataforma.y);

			cria_Inimigos_Nas_Plataformas(pos_plataforma.x, (pos_plataforma.x + tam_plataforma.x), pos_plataforma);
			cria_Caixas_na_Plataforma(tam_plataforma,pos_plataforma);

			gerenciador_colisoes.Incluir_Obstaculo(static_cast<Obstaculo*>(plataforma));
			lista_Entidades.adicionar(static_cast<Entidade*>(plataforma));


		}

		pos_plataforma.x = 0.f;
		posicao_da_ultima_plataforma = 0.f;
		
	}
	

}

void Fases::Fase_1::Cria_Piso() {

	piso = new Plataforma;
	piso->seta_Obstaculo(tam_Piso_Fase.y, tam_Piso_Fase.x, pos_Piso.x, pos_Piso.y,"Assets/Imagens/Plataforma.png");
	piso->determinar_chao();

	gerenciador_colisoes.Incluir_Obstaculo(static_cast<Obstaculo*>(piso));
	lista_Entidades.adicionar(static_cast<Entidade*>(piso));
}

void Fases::Fase_1::cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat){

	int gerar_ou_nao = (rand() % 100);
	int gerar_esq_ou_pirata = (rand() % 100);


	//50% de chance
	int gerar_esq = 70;

	//70% de chance
	if(gerar_ou_nao<= 80) {

		//gera cap
		if(gerar_esq_ou_pirata < gerar_esq && num_restante_esqueletos > 0) {

			//precisa ser a posição a direita da plataforma, para que o inimigo possa ser gerado dentro dela.
			Cria_Esqueletos(pos_plat.x + ((ponta_dir_plataforma - ponta_esq_plataforma)/2), pos_plat.y, ponta_esq_plataforma, ponta_dir_plataforma);
			num_restante_esqueletos--;
		}
		//gera pirata
		else if(gerar_esq_ou_pirata >= gerar_esq && num_restante_piratas > 0){

			//precisa ser a posição a direita da plataforma, para que o inimigo possa ser gerado dentro dela.
			Cria_Pirata(pos_plat.x + ((ponta_dir_plataforma - ponta_esq_plataforma)/2), pos_plat.y, ponta_esq_plataforma, ponta_dir_plataforma);
			num_restante_piratas--;
		}
	}
}

void Fases::Fase_1::Cria_Caixas(float pos_embaixo_plat_y, float tam_plat_x){

	Caixa* caixas;
	caixas = new Caixa;

	caixas->seta_Caixa(pos_embaixo_plat_y, tam_plat_x);
	lista_caixa.push_back(caixas);
	gerenciador_colisoes.Incluir_Obstaculo(caixas);
	lista_Entidades.adicionar(static_cast<Entidade*>(caixas));
	std::cout << "criou caixas" << std::endl;
}

void Fases::Fase_1::cria_Caixas_na_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat){

		if(num_restante_caixas > 0) {
				Cria_Caixas(100,tam_plat.x - 400);
				num_restante_caixas--;
		}

}