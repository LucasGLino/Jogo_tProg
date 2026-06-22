#include "Fases/Fase_1.h"

using namespace Entidades;
using namespace Personagens;
using namespace Fases;
using namespace Obstaculos;

Fases::Fase_1::Fase_1()
{
	// entre 3 e 10
	num_esqueletos = (rand() % 7) + 3;

	// entre 3 a 5
	num_caixas = (rand()%3) + 3;

	num_restante_esqueletos = num_esqueletos;
	num_restante_caixas = num_caixas;

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

	esqueleto->setar_Pos(x, y - esqueleto->get_Altura());
	esqueleto->setar_Patrulha(patrulha_ate_a, patrula_ate_b);

	lista_id_inimigos.push_front(esqueleto->getId());
	gerenciador_colisoes.Incluir_Inimigo(esqueleto);
	lista_Entidades.adicionar(static_cast<Entidade*>(esqueleto));
}

void Fases::Fase_1::cria_Inimigos_Nas_Plataformas(float ponta_esq_plataforma, float ponta_dir_plataforma, sf::Vector2f pos_plat)
{
	int gerar_ou_nao = (rand() % 100);
	int gerar_esq_ou_pirata = (rand() % 100);
	float pos_inimigo_x = 0.f;
	float limite_esquerdo = ponta_esq_plataforma + 10.f;
	float limite_direito = ponta_dir_plataforma - 35.f;

	//70% de chance
	int gerar_esq = 70;

	if(limite_direito > limite_esquerdo){
		pos_inimigo_x = limite_esquerdo + (rand() % static_cast<int>(limite_direito - limite_esquerdo));
	}
	else{
		pos_inimigo_x = pos_plat.x + ((ponta_dir_plataforma - ponta_esq_plataforma)/2);
	}

	//80% de chance
	if(gerar_ou_nao<= 80) {
		if(gerar_esq_ou_pirata < gerar_esq && num_restante_esqueletos > 0) {
			Cria_Esqueletos(pos_inimigo_x, pos_plat.y, ponta_esq_plataforma, ponta_dir_plataforma);
			num_restante_esqueletos--;
		}
		else if(gerar_esq_ou_pirata >= gerar_esq && num_restante_piratas > 0){
			Cria_Pirata(pos_inimigo_x, pos_plat.y, ponta_esq_plataforma, ponta_dir_plataforma);
			num_restante_piratas--;
		}
		else if(num_restante_esqueletos > 0) {
			Cria_Esqueletos(pos_inimigo_x, pos_plat.y, ponta_esq_plataforma, ponta_dir_plataforma);
			num_restante_esqueletos--;
		}
		else if(num_restante_piratas > 0) {
			Cria_Pirata(pos_inimigo_x, pos_plat.y, ponta_esq_plataforma, ponta_dir_plataforma);
			num_restante_piratas--;
		}
	}
}

void Fases::Fase_1::Cria_Caixas(float pos_caixa_x, float pos_caixa_y)
{
	Caixa* caixas = new Caixa;

	caixas->seta_Caixa(pos_caixa_x, pos_caixa_y);
	gerenciador_colisoes.Incluir_Obstaculo(caixas);
	lista_Entidades.adicionar(static_cast<Entidade*>(caixas));
}

void Fases::Fase_1::Cria_Caixas_Restantes()
{
	sf::Vector2f aux;

	for(int i = 0; i < num_restante_caixas; i++){
		aux.x = pos_Piso.x + (rand() % static_cast<int>(tam_Piso_Fase.x));
		aux.y = pos_Piso.y;

		Cria_Caixas(aux.x, aux.y - 64.0f);
	}

	num_restante_caixas = 0;
}

void Fases::Fase_1::cria_Caixas_na_Plataforma(sf::Vector2f tam_plat, sf::Vector2f pos_plat)
{
	int gerar_ou_nao = rand() % 100;
	float pos_na_plataforma = 0.f;

	if(num_restante_caixas > 0) {
		if(gerar_ou_nao < 60) {
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
}
