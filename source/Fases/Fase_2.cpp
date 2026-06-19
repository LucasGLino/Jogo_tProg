#include "Fases/Fase_2.h"

using namespace Entidades;
using namespace Personagens;
using namespace Fases;
using namespace Obstaculos;
using namespace Gerenciadores;

Fases::Fase_2::Fase_2() {

	//srand(static_cast<unsigned int>(time(0)));
	
	i = 0;
	j = 0;

	// entre 3 e 6
	num_capitoes = (rand() % 3) + 3;
	//num_capitoes = 1;

	//entre 3 e 8
	num_piratas = (rand() % 5) + 3;
	//num_piratas = 0;

	//entre 3 a 4
	num_espinhos = (rand()%1) + 3;
	//num_espinhos = 0;

	num_restante_capitoes = num_capitoes;
	num_restante_piratas = num_piratas;
	num_restante_espinhos = num_espinhos;

	zoom_camera = 1.3f;

	

	num_plataformas_totais = rand() % 10;

	num_max_andares = 4;

	tam_Piso_Fase.x = pGG->getCamera()->getSize().x * zoom_camera;
	tam_Piso_Fase.y = pGG->getCamera()->getSize().y / 3.f;

	pos_Piso.x = 0.f;
	pos_Piso.y = tam_Piso_Fase.y;


	lista_cap.clear();

	tamanho_da_tela_x = pGG->getCamera()->getSize().x * zoom_camera;
	espaco_vazio_x = 0;

	num_max_plataformas = 10;

	fundo_carregado = false;
	if (!textura_fundo.loadFromFile("Imagens/Fundo_fase2.png")) {
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

void Fases::Fase_2::ajustar_Fundo_A_Camera()
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

Fases::Fase_2::~Fase_2(){

	lista_cap.clear();
	num_plataformas_por_andar.clear();
}

void Fases::Fase_2::remover_Inimigo_Das_Listas_Auxiliares(Inimigo* pInimigo)
{
	for (std::vector<Capitao*>::iterator itr = lista_cap.begin(); itr != lista_cap.end();) {
		if (static_cast<Inimigo*>(*itr) == pInimigo) {
			itr = lista_cap.erase(itr);
		}
		else {
			itr++;
		}
	}
}


void Fases::Fase_2::Cria_Obstaculos(){

	Cria_Piso();
	Posiciona_plataforma();
}

void Fases::Fase_2::executar(){

	verifica_Inimigos_Neutralizados();

	if (!ganhou) {
		if (fundo_carregado) {
			pGG->getJanela()->draw(fundo);
		}

		verifica_Projeteis_Destroidos();
		gerenciador_colisoes.Executar();
		lista_Entidades.percorrer();

		for (i = 0; i < lista_cap.size(); i++) {

			if (lista_cap[i]->get_Disparou() && !(lista_cap[i]->get_Eliminado())) {

				lista_cap[i]->incluir_Projetil(Cria_Projetil());
			}
		}

	}

}

void Fases::Fase_2::Cria_Inimigos(){


	sf::Vector2f aux;
	Capitao aux_cap;
	Pirata aux_pirat;

	for(i=0;i<num_restante_capitoes;i++){

		aux.x = pos_Piso.x + (rand() % static_cast<int>(tam_Piso_Fase.x));
		aux.y = pos_Piso.y;

		Cria_Capitao(aux.x, aux.y);
	}

	for(i = 0; i<num_restante_piratas; i++){

		aux.x = pos_Piso.x + (rand() % static_cast<int>(tam_Piso_Fase.x));
		aux.y = pos_Piso.y;

		Cria_Pirata(aux.x, aux.y, pos_Piso.x, tam_Piso_Fase.x);
	}
}

//cria o inimigo dificil (Boss)
void Fase_2::Cria_Capitao(float x, float y){

	Capitao* capitao;
	capitao = new Capitao;

	capitao->setar_Pos(x, y - capitao->get_Altura());
	gerenciador_colisoes.Incluir_Inimigo(capitao);
	lista_Entidades.adicionar(static_cast<Entidade*>(capitao));
	lista_cap.push_back(capitao);
	lista_id_inimigos.push_front(capitao->getId());
}

//auto explicativo
Projetil* Fases::Fase_2::Cria_Projetil()
{

	Projetil* proj;
	proj = new Projetil;
	
	lista_Entidades.adicionar(static_cast<Entidade*>(proj));
	gerenciador_colisoes.Incluir_Projetil(proj);

	return proj;
}

void Fases::Fase_2::verifica_Projeteis_Destroidos()
{
	
	Projetil* projetil_deletado;

	for(i=0;i<lista_cap.size(); i++) {

		for(j = 0; j < lista_cap[i]->get_Vetor_De_Projetis()->size(); j++) {


			// conteudo apontado pelo ponteiro do vetor de projeteis do capitao
			if (!((*lista_cap[i]->get_Vetor_De_Projetis())[j]->get_Ativo())) {

				projetil_deletado = (*(lista_cap[i]->get_Vetor_De_Projetis()))[j];


				if (projetil_deletado) {
					//remove da lista de colisões
					gerenciador_colisoes.projetil_Destruido(projetil_deletado);

				}
				else {
					std::cout << "Erro ao remover projetil (Gerenciador_colisoes)" << std::endl;
				}

				if (projetil_deletado) {
					//remove do capitão
					lista_cap[i]->remover_Projetil(projetil_deletado);
				}
				else {
					std::cout << "Erro ao remover projetil (Capitao)" << std::endl;
				}

				if (projetil_deletado) {
					//remove da lista de entidades
					lista_Entidades.remover(static_cast<Entidade*>(projetil_deletado));
				}
				else {
					std::cout << "Erro ao remover projetil (Lista_Entidades)" << std::endl;
				}

			}
		}

		projetil_deletado = nullptr;
	}

	

}

void Fases::Fase_2::setar_Camera_Fase()
{
	pGG->getCamera()->zoom(zoom_camera);
}

void Fases::Fase_2::atualiza_Camera_Fase(Jogador* p_jogador1, Jogador* p_jogador2)
{
	sf::Vector2f pos_camera;

	pos_camera.x = tam_Piso_Fase.x/2;
	pos_camera.y = -tam_Piso_Fase.y/3;

	//trava a camera;
	pGG->getCamera()->setCenter(pos_camera);
	ajustar_Fundo_A_Camera();

}

void Fases::Fase_2::seta_Tamanho_Plataformas(int n_plataformas) {

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

void Fases::Fase_2::seta_Num_Plataformas(){

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

void Fases::Fase_2::Posiciona_plataforma() {

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
			cria_Espinhos_na_Plataforma(tam_plataforma,pos_plataforma);

			gerenciador_colisoes.Incluir_Obstaculo(static_cast<Obstaculo*>(plataforma));
			lista_Entidades.adicionar(static_cast<Entidade*>(plataforma));


		}

		pos_plataforma.x = 0.f;
		posicao_da_ultima_plataforma = 0.f;
		
	}
	

}

void Fases::Fase_2::Cria_Piso() {

	piso = new Plataforma;
	piso->seta_Obstaculo(tam_Piso_Fase.y, tam_Piso_Fase.x, pos_Piso.x, pos_Piso.y,"Imagens/Plataforma.png");

	gerenciador_colisoes.Incluir_Obstaculo(static_cast<Obstaculo*>(piso));
	lista_Entidades.adicionar(static_cast<Entidade*>(piso));
}

void Fases::Fase_2::cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat){

	int gerar_ou_nao = (rand() % 100);
	int gerar_cap_ou_pirata = (rand() % 100);


	//50% de chance
	int gerar_cap = 50;

	//70% de chance
	if(gerar_ou_nao<= 70) {

		//gera cap
		if(gerar_cap_ou_pirata < gerar_cap && num_restante_capitoes > 0) {

			//precisa ser a posição a direita da plataforma, para que o inimigo possa ser gerado dentro dela.
			Cria_Capitao(pos_plat.x + ((ponta_dir_plataforma - ponta_esq_plataforma)/2), pos_plat.y);
			num_restante_capitoes--;
		}
		//gera pirata
		else if(gerar_cap_ou_pirata >= gerar_cap && num_restante_piratas > 0){

			//precisa ser a posição a direita da plataforma, para que o inimigo possa ser gerado dentro dela.
			Cria_Pirata(pos_plat.x + ((ponta_dir_plataforma - ponta_esq_plataforma)/2), pos_plat.y, ponta_esq_plataforma, ponta_dir_plataforma);
			num_restante_piratas--;
		}
	}
}

void Fases::Fase_2::Cria_Espinhos(float pos_plat_x, float pos_embaixo_plat_y, float tam_plat_x){

	Espinho* espinhos;
	espinhos = new Espinho;

	espinhos->seta_Obstaculo(32.0, pos_plat_x, pos_embaixo_plat_y, tam_plat_x, "Assets/Imagens/Espinhos.png");
	lista_espinhos.push_back(espinhos);
	gerenciador_colisoes.Incluir_Obstaculo(espinhos);
	lista_Entidades.adicionar(static_cast<Entidade*>(espinhos));
}

void Fases::Fase_2::cria_Espinhos_na_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat){

	int gerar_ou_nao = rand() % 100;
	int chance = 100;

	if(num_restante_espinhos > 0) {

		if(gerar_ou_nao < 60){

			Cria_Espinhos(pos_plat.x,(pos_plat.y-32.f),tam_plat.x);
			num_restante_espinhos--;
		}
	}
}
