#include "Fases/Fase_1.h"

using namespace Entidades;
using namespace Personagens;
using namespace Fases;
using namespace Obstaculos;

Fases::Fase_1::Fase_1()
{
	// entre 4 e 6
	num_esqueletos = (rand() % 3) + 4;

	// entre 3 a 7
	num_caixas = (rand()%5) + 3;

	num_restante_esqueletos = num_esqueletos;
	num_restante_caixas = num_caixas;
	num_esqueletos_em_plataformas = 0;

	setar_Camera_Fase();
	ajustar_Fundo_A_Camera();
	Cria_Obstaculos();
	Cria_Inimigos();
}

Fases::Fase_1::~Fase_1()
{
}

void Fases::Fase_1::Cria_Inimigos_Especificos()
{
	sf::Vector2f aux;

	for(int i = 0; i < num_restante_esqueletos; i++){
		aux.x = pos_Piso.x + (rand() % static_cast<int>(tam_Piso_Fase.x));
		aux.y = pos_Piso.y;

		Cria_Esqueletos(aux.x, aux.y, pos_Piso.x, pos_Piso.x + tam_Piso_Fase.x);
	}

	num_restante_esqueletos = 0;
}

void Fases::Fase_1::criar_Entidades_em_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat, float ponta_esq, float ponta_dir)
{
	cria_Inimigos_Nas_Plataformas(ponta_esq, ponta_dir, pos_plat);
	cria_Caixas_na_Plataforma(tam_plat, pos_plat);
}

void Fases::Fase_1::Cria_Obstaculos_Restantes()
{
	Cria_Caixas_Restantes();
}

void Fases::Fase_1::Cria_Esqueletos(float x, float y,float patrulha_ate_a, float patrula_ate_b)
{
	Esqueleto* esqueleto = new Esqueleto;
	float x_spawn = ajustar_X_Spawn(x, y);

	esqueleto->setar_Pos(x_spawn, y - esqueleto->get_Altura());
	esqueleto->setar_Patrulha(patrulha_ate_a, patrula_ate_b);

	lista_id_inimigos.push_front(esqueleto->getId());
	gerenciador_colisoes.Incluir_Inimigo(esqueleto);
	lista_Entidades.adicionar(static_cast<Entidade*>(esqueleto));
}

void Fases::Fase_1::Cria_Caixas(float pos_caixa_x, float pos_caixa_y)
{
	Caixa* caixas = new Caixa;

	caixas->seta_Caixa(pos_caixa_x, pos_caixa_y);
	float x_spawn = ajustar_X_Spawn(pos_caixa_x, pos_caixa_y + caixas->get_Altura());
	caixas->setar_Pos(x_spawn, pos_caixa_y);

	gerenciador_colisoes.Incluir_Obstaculo(caixas);
	lista_Entidades.adicionar(static_cast<Entidade*>(caixas));
}

void Fases::Fase_1::Cria_Caixas_Restantes()
{
	sf::Vector2f aux;
	const int max_caixas_no_chao = 2;
	int caixas_no_chao = num_restante_caixas;

	if (caixas_no_chao > max_caixas_no_chao) {
		caixas_no_chao = max_caixas_no_chao;
	}

	for(int i = 0; i < caixas_no_chao; i++){
		aux.x = pos_Piso.x + (rand() % static_cast<int>(tam_Piso_Fase.x));
		aux.y = pos_Piso.y;

		Cria_Caixas(aux.x, aux.y - 64.0f);
	}

	num_restante_caixas = 0;
}

void Fases::Fase_1::cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat)
{
	const int max_inimigos_por_tipo_em_plataformas = 4;
	const int max_inimigos_por_plataforma = 2;
	int inimigos_criados = 0;
	float pos_inimigo_x = 0.f;
	float limite_esquerdo = ponta_esq_plataforma + 10.f;
	float limite_direito = ponta_dir_plataforma - 35.f;
	bool precisa_criar_pirata;
	bool precisa_criar_esqueleto;

	while (inimigos_criados < max_inimigos_por_plataforma) {
		precisa_criar_pirata = (num_piratas_em_plataformas < max_inimigos_por_tipo_em_plataformas && num_restante_piratas > 0);
		precisa_criar_esqueleto = (num_esqueletos_em_plataformas < max_inimigos_por_tipo_em_plataformas && num_restante_esqueletos > 0);

		if (!precisa_criar_pirata && !precisa_criar_esqueleto) {
			return;
		}

		if(limite_direito > limite_esquerdo){
			pos_inimigo_x = limite_esquerdo + (rand() % static_cast<int>(limite_direito - limite_esquerdo));
		}
		else{
			pos_inimigo_x = pos_plat.x + ((ponta_dir_plataforma - ponta_esq_plataforma)/2);
		}

		if(precisa_criar_pirata && (num_piratas_em_plataformas <= num_esqueletos_em_plataformas || !precisa_criar_esqueleto)){
			Cria_Pirata(pos_inimigo_x, pos_plat.y, ponta_esq_plataforma, ponta_dir_plataforma);
			num_restante_piratas--;
			num_piratas_em_plataformas++;
		}
		else if(precisa_criar_esqueleto) {
			Cria_Esqueletos(pos_inimigo_x, pos_plat.y, ponta_esq_plataforma, ponta_dir_plataforma);
			num_restante_esqueletos--;
			num_esqueletos_em_plataformas++;
		}

		inimigos_criados++;
	}
}

void Fases::Fase_1::cria_Caixas_na_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat)
{
	const int minimo_caixas_no_chao = 2;

	if (!pode_Criar_Na_Plataforma(num_restante_caixas, minimo_caixas_no_chao)) {
		return;
	}

	float pos_na_plataforma = 0.f;

	if(num_restante_caixas > 0) {
		pos_na_plataforma = (tam_plat.x/(rand() % 5 + 2));

		if(pos_na_plataforma <= 30.0f){
			pos_na_plataforma = 30.0f;
		}
		else if(pos_na_plataforma >= tam_plat.x - 64.0f){
			pos_na_plataforma = tam_plat.x - 64.0f;
		}

		Cria_Caixas((pos_plat.x + pos_na_plataforma),(pos_plat.y - 64.0f));
		num_restante_caixas--;
	}
}
