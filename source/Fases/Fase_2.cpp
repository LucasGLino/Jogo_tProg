#include "Fases/Fase_2.h"
#include "Entidades/Obstaculos/Espinho.h"
#include "Entidades/Personagens/Inimigos/Capitao.h"
#include "Entidades/Projetil.h"
#include <cstdlib>

using namespace Entidades;
using namespace Personagens;
using namespace Fases;
using namespace Obstaculos;

// Sorteia as quantidades da fase 2 e monta chao, plataformas, obstaculos e inimigos.
Fases::Fase_2::Fase_2()
{
	// Entre 4 e 6 capitaes.
	num_capitoes = (rand() % 3) + 4;

	// Entre 3 e 7 espinhos.
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

// Limpa a lista auxiliar de capitaes.
Fases::Fase_2::~Fase_2()
{
	lista_cap.clear();
}

// Remove um capitao da lista auxiliar quando ele e neutralizado.
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

// Cria no chao os capitaes que nao foram colocados em plataformas.
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

// Preenche uma plataforma com inimigos e espinhos da fase 2.
void Fases::Fase_2::criar_Entidades_em_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat, float ponta_esq, float ponta_dir)
{
	cria_Inimigos_Nas_Plataformas(ponta_esq, ponta_dir, pos_plat);
	cria_Espinhos_na_Plataforma(tam_plat, pos_plat);
}

// Cria os espinhos que precisam ficar no chao.
void Fases::Fase_2::Cria_Obstaculos_Restantes()
{
	Cria_Espinhos_Restantes();
}

// Limpa projeteis inativos antes das entidades executarem.
void Fases::Fase_2::executar_Antes_Entidades()
{
	verifica_Projeteis_Destroidos();
}

// Cria projeteis novos para capitaes que terminaram a recarga.
void Fases::Fase_2::executar_Depois_Entidades()
{
	for (int i = 0; i < static_cast<int>(lista_cap.size()); i++) {
		if (lista_cap[i]->get_Disparou() && !(lista_cap[i]->get_Eliminado())) {
			lista_cap[i]->incluir_Projetil(Cria_Projetil());
		}
	}
}

// Cria um capitao e registra ele nas listas da fase.
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

// Cria um projetil e registra ele na lista principal e nas colisoes.
Projetil* Fases::Fase_2::Cria_Projetil()
{
	Projetil* proj = new Projetil;
	
	lista_Entidades.adicionar(static_cast<Entidade*>(proj));
	gerenciador_colisoes.Incluir_Projetil(proj);

	return proj;
}

// Remove projeteis inativos sem pular itens quando o vetor muda de tamanho.
void Fases::Fase_2::verifica_Projeteis_Destroidos()
{
	Projetil* projetil_deletado;
	std::vector<Projetil*>* pProjeteis;

	for(int i = 0; i < static_cast<int>(lista_cap.size()); i++) {
		pProjeteis = lista_cap[i]->get_Vetor_De_Projetis();

		for(int j = 0; j < static_cast<int>(pProjeteis->size());) {
			projetil_deletado = (*pProjeteis)[j];

			if (projetil_deletado != nullptr && !projetil_deletado->get_Ativo()) {
				// Nao incrementa o indice depois de remover, pois o vetor desloca os itens.
				gerenciador_colisoes.projetil_Destruido(projetil_deletado);
				lista_cap[i]->remover_Projetil(projetil_deletado);
				lista_Entidades.remover(static_cast<Entidade*>(projetil_deletado));
			}
			else {
				j++;
			}
		}

		projetil_deletado = nullptr;
	}
}

// Cria um espinho, ajusta o spawn e registra ele nas colisoes.
void Fases::Fase_2::Cria_Espinhos(float pos_plat_x, float pos_plat_y)
{
	Espinho* espinho = new Espinho;

	espinho->seta_Obstaculo(32.0, 80.0, pos_plat_x, pos_plat_y, "Assets/Imagens/Espinhos.png");
	float x_spawn = ajustar_X_Spawn(pos_plat_x, pos_plat_y + espinho->get_Altura());
	espinho->setar_Pos(x_spawn, pos_plat_y);

	gerenciador_colisoes.Incluir_Obstaculo(espinho);
	lista_Entidades.adicionar(static_cast<Entidade*>(espinho));
}

// Deixa no maximo dois espinhos no chao e zera o restante depois da criacao.
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

// Distribui ate dois inimigos por plataforma, priorizando completar 4 de cada tipo.
void Fases::Fase_2::cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat)
{
	const int max_inimigos_por_tipo_em_plataformas = 4;
	const int max_inimigos_por_plataforma = 2;
	int inimigos_criados = 0;
	int intervalo_spawn = 0;
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

		intervalo_spawn = static_cast<int>(limite_direito - limite_esquerdo);
		if(intervalo_spawn > 0){
			pos_inimigo_x = limite_esquerdo + (rand() % intervalo_spawn);
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

// Cria espinhos nas plataformas enquanto ainda sobram espinhos alem do minimo do chao.
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
		else if(pos_na_plataforma >= tam_plat.x - 80.0f){
			pos_na_plataforma = tam_plat.x - 80.0f;
		}
		
		Cria_Espinhos((pos_plat.x + pos_na_plataforma),(pos_plat.y-32.0f));
		num_restante_espinhos--;
	}
}
