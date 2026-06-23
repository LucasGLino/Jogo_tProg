#include "Fases/Fase_2.h"

using namespace Entidades;
using namespace Personagens;
using namespace Fases;
using namespace Obstaculos;
using namespace Gerenciadores;

Fases::Fase_2::Fase_2()
{
	// entre 4 e 6
	num_capitoes = (rand() % 3) + 4;

	// entre 3 a 7
	num_espinhos = (rand()%5) + 3;

	num_restante_capitoes = num_capitoes;
	num_restante_espinhos = num_espinhos;
	num_capitoes_em_plataformas = 0;
	lista_cap.clear();
	
	setar_Camera_Fase();
	ajustar_Fundo_A_Camera();
	Cria_Obstaculos();
	Cria_Inimigos();
}

Fases::Fase_2::~Fase_2()
{
	lista_cap.clear();
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

void Fases::Fase_2::Cria_Inimigos_Especificos()
{
	sf::Vector2f aux;

	for(int i = 0; i < num_restante_capitoes; i++){
		aux.x = pos_Piso.x + (rand() % static_cast<int>(tam_Piso_Fase.x));
		aux.y = pos_Piso.y;

		Cria_Capitao(aux.x, aux.y);
	}

	num_restante_capitoes = 0;
}

void Fases::Fase_2::criar_Entidades_em_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat, float ponta_esq, float ponta_dir)
{
	cria_Inimigos_Nas_Plataformas(ponta_esq, ponta_dir, pos_plat);
	cria_Espinhos_na_Plataforma(tam_plat, pos_plat);
}

void Fases::Fase_2::Cria_Obstaculos_Restantes()
{
	Cria_Espinhos_Restantes();
}

void Fases::Fase_2::executar_Antes_Entidades()
{
	verifica_Projeteis_Destroidos();
}

void Fases::Fase_2::executar_Depois_Entidades()
{
	for (int i = 0; i < lista_cap.size(); i++) {
		if (lista_cap[i]->get_Disparou() && !(lista_cap[i]->get_Eliminado())) {
			lista_cap[i]->incluir_Projetil(Cria_Projetil());
		}
	}
}

void Fase_2::Cria_Capitao(float x, float y)
{
	Capitao* capitao = new Capitao;
	float x_spawn = ajustar_X_Spawn(x, y);

	capitao->setar_Pos(x_spawn, y - capitao->get_Altura());
	gerenciador_colisoes.Incluir_Inimigo(capitao);
	lista_Entidades.adicionar(static_cast<Entidade*>(capitao));
	lista_cap.push_back(capitao);
	lista_id_inimigos.push_front(capitao->getId());
}

Projetil* Fases::Fase_2::Cria_Projetil()
{
	Projetil* proj = new Projetil;
	
	lista_Entidades.adicionar(static_cast<Entidade*>(proj));
	gerenciador_colisoes.Incluir_Projetil(proj);

	return proj;
}

void Fases::Fase_2::verifica_Projeteis_Destroidos()
{
	Projetil* projetil_deletado;

	for(int i = 0; i < lista_cap.size(); i++) {
		for(int j = 0; j < lista_cap[i]->get_Vetor_De_Projetis()->size(); j++) {
			if (!((*lista_cap[i]->get_Vetor_De_Projetis())[j]->get_Ativo())) {
				projetil_deletado = (*(lista_cap[i]->get_Vetor_De_Projetis()))[j];

				if (projetil_deletado) {
					gerenciador_colisoes.projetil_Destruido(projetil_deletado);
				}
				else {
					std::cout << "Erro ao remover projetil (Gerenciador_colisoes)" << std::endl;
				}

				if (projetil_deletado) {
					lista_cap[i]->remover_Projetil(projetil_deletado);
				}
				else {
					std::cout << "Erro ao remover projetil (Capitao)" << std::endl;
				}

				if (projetil_deletado) {
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

void Fases::Fase_2::Cria_Espinhos(float pos_plat_x, float pos_plat_y)
{
	Espinho* espinhos = new Espinho;

	espinhos->seta_Obstaculo(32.0, 80.0, pos_plat_x, pos_plat_y, "Assets/Imagens/Espinhos.png");
	float x_spawn = ajustar_X_Spawn(pos_plat_x, pos_plat_y + espinhos->get_Altura());
	espinhos->setar_Pos(x_spawn, pos_plat_y);

	gerenciador_colisoes.Incluir_Obstaculo(espinhos);
	lista_Entidades.adicionar(static_cast<Entidade*>(espinhos));
}

void Fases::Fase_2::Cria_Espinhos_Restantes()
{
	sf::Vector2f aux;
	const int max_espinhos_no_chao = 2;
	int espinhos_no_chao = num_restante_espinhos;

	if (espinhos_no_chao > max_espinhos_no_chao) {
		espinhos_no_chao = max_espinhos_no_chao;
	}

	for(int i = 0; i < espinhos_no_chao; i++){
		aux.x = pos_Piso.x + (rand() % static_cast<int>(tam_Piso_Fase.x));
		aux.y = pos_Piso.y;

		Cria_Espinhos(aux.x, aux.y - 32.0f);
	}

	num_restante_espinhos = 0;
}

void Fases::Fase_2::cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat)
{
	const int max_inimigos_por_tipo_em_plataformas = 4;
	const int max_inimigos_por_plataforma = 2;
	int inimigos_criados = 0;
	float pos_inimigo_x = 0.f;
	float limite_esquerdo = ponta_esq_plataforma + 10.f;
	float limite_direito = ponta_dir_plataforma - 35.f;
	bool precisa_criar_pirata;
	bool precisa_criar_capitao;

	while (inimigos_criados < max_inimigos_por_plataforma) {
		precisa_criar_pirata = (num_piratas_em_plataformas < max_inimigos_por_tipo_em_plataformas && num_restante_piratas > 0);
		precisa_criar_capitao = (num_capitoes_em_plataformas < max_inimigos_por_tipo_em_plataformas && num_restante_capitoes > 0);

		if (!precisa_criar_pirata && !precisa_criar_capitao) {
			return;
		}

		if(limite_direito > limite_esquerdo){
			pos_inimigo_x = limite_esquerdo + (rand() % static_cast<int>(limite_direito - limite_esquerdo));
		}
		else{
			pos_inimigo_x = pos_plat.x + ((ponta_dir_plataforma - ponta_esq_plataforma)/2);
		}

		if(precisa_criar_pirata && (num_piratas_em_plataformas <= num_capitoes_em_plataformas || !precisa_criar_capitao)){
			Cria_Pirata(pos_inimigo_x, pos_plat.y, ponta_esq_plataforma, ponta_dir_plataforma);
			num_restante_piratas--;
			num_piratas_em_plataformas++;
		}
		else if(precisa_criar_capitao) {
			Cria_Capitao(pos_inimigo_x, pos_plat.y);
			num_restante_capitoes--;
			num_capitoes_em_plataformas++;
		}

		inimigos_criados++;
	}
}

void Fases::Fase_2::cria_Espinhos_na_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat)
{
	const int minimo_espinhos_no_chao = 2;

	if (!pode_Criar_Na_Plataforma(num_restante_espinhos, minimo_espinhos_no_chao)) {
		return;
	}

	float pos_na_plataforma = 0.f;

	if(num_restante_espinhos > 0) {
		pos_na_plataforma = ((tam_plat.x/(rand() % 5 + 2) ));

		if(pos_na_plataforma <= 30.0f){
			pos_na_plataforma = 30.0f;
		}
		else if(pos_na_plataforma >= (pos_plat.x+tam_plat.x)){
			pos_na_plataforma -= 80.0f;
		}
		
		Cria_Espinhos((pos_plat.x + pos_na_plataforma),(pos_plat.y-32.0f));
		num_restante_espinhos--;
	}
}
