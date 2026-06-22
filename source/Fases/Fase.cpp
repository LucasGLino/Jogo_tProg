#include "Fases/Fase.h"

using namespace Fases;
using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;

int Fases::Fase::base_Id = 0;

Fase::Fase(): Ente(base_Id) {

	//srand(static_cast<unsigned int>(time(0)));
	static bool sorteio_iniciado = false;
	if (!sorteio_iniciado) {
		srand(static_cast<unsigned int>(time(0)));
		sorteio_iniciado = true;
	}
	num_plataformas_totais = rand() % 7;

	//srand(static_cast<unsigned int>(time(0)));
	num_inimigos = rand() % 8;

	lista_id_inimigos.clear();

	ganhou = false;
	perdeu = false;

	piso = nullptr;
	plataforma = nullptr;

	tam_Piso_Fase.x = 2500.f;
	tam_Piso_Fase.y = 100.f;
	pos_Piso.x = -100.f;
	pos_Piso.y = 200.f;

	tam_plataforma.x = 150.f;
	tam_plataforma.y = 30.f;

	pos_original.x = 10;
	pos_original.y = 80;
	
}

Fase::~Fase() {

	//delete plataforma;
	//delete piso;
	plataforma = nullptr;
	piso = nullptr;
}


void Fases::Fase::Setar_Jogadores(Jogador* p_jogador1,Jogador* p_jogador2)
{
	std::cout << "entrou no Setar_Jogadores" << std::endl;
	Setar_Jogadores_Colisoes(p_jogador1, p_jogador2);
	Setar_Jogadores_Inimigos(p_jogador1, p_jogador2);
	
	//p_jogador1->setar_Pos(pos_Piso.x, pos_Piso.y - p_jogador1->get_Altura());
	//p_jogador2->setar_Pos(pos_Piso.x, pos_Piso.y - p_jogador2->get_Altura());
	if (p_jogador1 != nullptr) {
		p_jogador1->setar_Pos(25.f, pos_Piso.y - p_jogador1->get_Altura());
	}
	if (p_jogador2 != nullptr) {
		p_jogador2->setar_Pos(25.f, pos_Piso.y - p_jogador2->get_Altura());
	}

}

void Fases::Fase::Setar_Jogadores_Colisoes(Jogador* p_jogador1, Jogador* p_jogador2){

	if ((p_jogador1 != nullptr) && (p_jogador2 == nullptr)) {

		gerenciador_colisoes.Setar_Jogador(p_jogador1, nullptr);
	}
	else if ((p_jogador1 !=nullptr) && (p_jogador2 != nullptr)) {

		gerenciador_colisoes.Setar_Jogador(p_jogador1, p_jogador2);
	}

	else {
		std::cout << "ERRO, SEM REF DE JOGADOR fase1.cpp" << std::endl;
		//system("pause");
	}
}

void Fases::Fase::Setar_Jogadores_Inimigos(Jogador* p_jogador1, Jogador* p_jogador2)
{
	std::list<int>::iterator itr;

	itr = lista_id_inimigos.begin();

	while (itr != lista_id_inimigos.end()) {
		
		//static_cast<Inimigo*>(lista_Entidades.get_Entidade_Por_Id(*itr))->setar_Jogador_No_Inimigo(p_jogador1, p_jogador2);
		Entidade* pEntidade = lista_Entidades.get_Entidade_Por_Id(*itr);
		Inimigo* pInimigo = dynamic_cast<Inimigo*>(pEntidade);

		if (pInimigo != nullptr) {
			pInimigo->setar_Jogador_No_Inimigo(p_jogador1, p_jogador2);
		}

		itr++;
	}

}

void Fases::Fase::Cria_Pirata(float x, float y, float patrulha_ate_a, float patrula_ate_b){
	Pirata* pirata;

	pirata = new Pirata;
	pirata->setar_Pos(x, y - pirata->get_Altura());
	pirata->setar_Patrulha(patrulha_ate_a, patrula_ate_b);

	lista_id_inimigos.push_front(pirata->getId());
	gerenciador_colisoes.Incluir_Inimigo(pirata);
	lista_Entidades.adicionar(static_cast<Entidade*>(pirata));

}

void Fases::Fase::Cria_Plataforma(float alt, float larg, float origem_x, float origem_y)
{
	plataforma = new Plataforma;
	plataforma->seta_Obstaculo(alt, larg, origem_x, origem_y,"Assets/Imagens/Plataforma.png");
}
bool Fases::Fase::get_Ganhou()
{
	return ganhou;
}


void Fases::Fase::criar_cenario()
{


}

void Fases::Fase::ajustar_Fundo_A_Camera()
{
	std::cout << "entrou noajustar_Fundo_A_Camera" << std::endl;
	
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

void Fases::Fase::atualiza_Camera_Fase(Jogador* p_jogador1, Jogador* p_jogador2)
{
	
	
	sf::Vector2f pos_camera;

	pos_camera.x = tam_Piso_Fase.x/2;
	pos_camera.y = -tam_Piso_Fase.y/3;

	//trava a camera;
	pGG->getCamera()->setCenter(pos_camera);
	ajustar_Fundo_A_Camera();

}


void Fases::Fase::verifica_Inimigos_Neutralizados() {

	auto itr = lista_id_inimigos.begin();

    while (itr != lista_id_inimigos.end() && !(lista_id_inimigos.empty())) {

        int id = *itr;
        Entidade* ent = lista_Entidades.get_Entidade_Por_Id(id);

        // id inv�lido -> remover da lista de ids
        if (ent == nullptr) {
            itr = lista_id_inimigos.erase(itr);
            continue;
        }

        // garantir que � um inimigo (mais seguro que static_cast)
        Inimigo* inim = dynamic_cast<Inimigo*>(ent);
        if (inim == nullptr) {
            ++itr;
            continue;
        }

		if(verifica_Se_Caiu_No_Abismo(static_cast<Entidade*>(inim))){
			inim->diminuir_Vitalidade(200);
		}

        if (inim->get_Eliminado()) {

            // remove entidade do gerenciador/lista de entidades
            //lista_Entidades.remover(ent);
			//gerenciador_colisoes.Inimigo_neutralizado(inim);
			remover_Inimigo_Das_Listas_Auxiliares(inim);
			gerenciador_colisoes.Inimigo_neutralizado(inim);
            lista_Entidades.remover(ent);

            // tamb�m remover o id da lista de inimigos para n�o iterar sobre ele novamente
            itr = lista_id_inimigos.erase(itr);
        } else {
            ++itr;
        }
    }

    if (gerenciador_colisoes.verifica_Lista_Inimigos_Vazia() && lista_id_inimigos.empty()) {
        std::cout << "todos os inimigos foram eliminados!" << std::endl;
        ganhou = true;
    }
}

void Fases::Fase::remover_Inimigo_Das_Listas_Auxiliares(Inimigo* pInimigo)
{
}

void Fases::Fase::executar()
{
	verifica_Inimigos_Neutralizados();
	gerenciador_colisoes.Executar();
	lista_Entidades.percorrer();
	
}

bool Fases::Fase::verifica_Se_Caiu_No_Abismo(Entidade* pEntidade){

	if(pEntidade->get_Y() > (pos_Piso.y * 2)) {
		return true;
	}
	else {
		return false;
	}
}