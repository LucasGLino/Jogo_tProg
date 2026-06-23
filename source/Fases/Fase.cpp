#include "Fases/Fase.h"

using namespace Fases;
using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;

int Fases::Fase::base_Id = 0;

Fase::Fase(): Ente(base_Id)
{
	static bool sorteio_iniciado = false;
	if (!sorteio_iniciado) {
		srand(static_cast<unsigned int>(time(0)));
		sorteio_iniciado = true;
	}

	ganhou = false;
	chao = nullptr;
	plataforma = nullptr;
	lista_id_inimigos.clear();

	num_plataformas_totais = rand() % 10;
	num_piratas = (rand() % 5) + 3;
	num_restante_piratas = num_piratas;
	num_max_andares = 4;

	zoom_camera = 1.3f;
	tamanho_da_tela_x = pGG->getCamera()->getSize().x * zoom_camera;
	espaco_vazio_x = 0.f;

	tam_Piso_Fase.x = pGG->getCamera()->getSize().x * zoom_camera;
	tam_Piso_Fase.y = pGG->getCamera()->getSize().y / 3.f;
	pos_Piso.x = 0.f;
	pos_Piso.y = tam_Piso_Fase.y;

	tam_plataforma.x = 150.f;
	tam_plataforma.y = 30.f;

	fundo_carregado = false;
	if (!textura_fundo.loadFromFile("Assets/Imagens/Fundo_fase2.png")) {
		std::cout << "Erro ao carregar textura do fundo da fase." << std::endl;
	}
	else {
		fundo.setTexture(textura_fundo);
		fundo_carregado = true;
	}
}

Fase::~Fase()
{
	num_plataformas_por_andar.clear();
	plataforma = nullptr;
	chao = nullptr;
}

void Fases::Fase::Setar_Jogadores(Jogador* p_jogador1,Jogador* p_jogador2)
{
	Setar_Jogadores_Colisoes(p_jogador1, p_jogador2);
	Setar_Jogadores_Inimigos(p_jogador1, p_jogador2);
	
	if (p_jogador1 != nullptr) {
		p_jogador1->setar_Pos(25.f, pos_Piso.y - p_jogador1->get_Altura());
	}
	if (p_jogador2 != nullptr) {
		p_jogador2->setar_Pos(25.f, pos_Piso.y - p_jogador2->get_Altura());
	}
}

void Fases::Fase::Setar_Jogadores_Colisoes(Jogador* p_jogador1, Jogador* p_jogador2)
{
	if ((p_jogador1 != nullptr) && (p_jogador2 == nullptr)) {
		gerenciador_colisoes.Setar_Jogador(p_jogador1, nullptr);
	}
	else if ((p_jogador1 !=nullptr) && (p_jogador2 != nullptr)) {
		gerenciador_colisoes.Setar_Jogador(p_jogador1, p_jogador2);
	}
	else {
		std::cout << "ERRO, SEM REF DE JOGADOR fase.cpp" << std::endl;
	}
}

void Fases::Fase::Setar_Jogadores_Inimigos(Jogador* p_jogador1, Jogador* p_jogador2)
{
	std::list<int>::iterator itr = lista_id_inimigos.begin();

	while (itr != lista_id_inimigos.end()) {
		Entidade* pEntidade = lista_Entidades.get_Entidade_Por_Id(*itr);
		Inimigo* pInimigo = dynamic_cast<Inimigo*>(pEntidade);

		if (pInimigo != nullptr) {
			pInimigo->setar_Jogador_No_Inimigo(p_jogador1, p_jogador2);
		}

		itr++;
	}
}

void Fases::Fase::Cria_Pirata(float x, float y, float patrulha_ate_a, float patrula_ate_b)
{
	Pirata* pirata = new Pirata;
	pirata->setar_Pos(x, y - pirata->get_Altura());
	pirata->setar_Patrulha(patrulha_ate_a, patrula_ate_b);

	lista_id_inimigos.push_front(pirata->getId());
	gerenciador_colisoes.Incluir_Inimigo(pirata);
	lista_Entidades.adicionar(static_cast<Entidade*>(pirata));
}

void Fases::Fase::Cria_Piratas_Restantes()
{
	sf::Vector2f aux;

	for(int i = 0; i < num_restante_piratas; i++){
		aux.x = pos_Piso.x + (rand() % static_cast<int>(tam_Piso_Fase.x));
		aux.y = pos_Piso.y;

		Cria_Pirata(aux.x, aux.y, pos_Piso.x, pos_Piso.x + tam_Piso_Fase.x);
	}

	num_restante_piratas = 0;
}

void Fases::Fase::Cria_Plataforma(float alt, float larg, float origem_x, float origem_y)
{
	plataforma = new Plataforma;
	plataforma->seta_Obstaculo(alt, larg, origem_x, origem_y,"Assets/Imagens/Plataforma.png");
	plataforma->seta_Origem(origem_x,origem_y);
}

bool Fases::Fase::get_Ganhou()
{
	return ganhou;
}

void Fases::Fase::executar()
{
	verifica_Inimigos_Neutralizados();

	if (!ganhou) {
		if (fundo_carregado) {
			pGG->getJanela()->draw(fundo);
		}

		executar_Antes_Entidades();
		gerenciador_colisoes.Executar();
		lista_Entidades.percorrer();
		executar_Depois_Entidades();
	}
}

void Fases::Fase::Cria_Piso()
{
	chao = new Chao;
	chao->configurar_Chao(tam_Piso_Fase.y, tam_Piso_Fase.x, pos_Piso.x, pos_Piso.y, "Assets/Imagens/Chao.png");
	chao->setar_Limite_Abismo(pos_Piso.y + tam_Piso_Fase.y);

	std::cout << "tamanho do chao:" << tam_Piso_Fase.x << "," << tam_Piso_Fase.y << std::endl;

	gerenciador_colisoes.Incluir_Chao(chao);
	lista_Entidades.adicionar(static_cast<Entidade*>(chao));
}

void Fases::Fase::Cria_Inimigos()
{
	Cria_Inimigos_Especificos();
	Cria_Piratas_Restantes();
}

void Fases::Fase::Cria_Obstaculos()
{
	Cria_Piso();
	Posiciona_plataforma();
	Cria_Obstaculos_Restantes();
}

void Fases::Fase::ajustar_Fundo_A_Camera()
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

void Fases::Fase::atualiza_Camera_Fase(Jogador* p_jogador1, Jogador* p_jogador2)
{
	sf::Vector2f pos_camera;

	pos_camera.x = tam_Piso_Fase.x/2;
	pos_camera.y = -tam_Piso_Fase.y/3;

	pGG->getCamera()->setCenter(pos_camera);
	ajustar_Fundo_A_Camera();
}

void Fases::Fase::setar_Camera_Fase()
{
	pGG->getCamera()->zoom(zoom_camera);
}

void Fases::Fase::seta_Tamanho_Plataformas(int n_plataformas)
{
	if(n_plataformas == 1){
		tam_plataforma.x = tamanho_da_tela_x*0.7f;
		espaco_vazio_x = static_cast<float>((tamanho_da_tela_x*0.3)/2);
	}
	else if(n_plataformas == 2){
		tam_plataforma.x = tamanho_da_tela_x*0.35f;
		espaco_vazio_x = static_cast<float>((tamanho_da_tela_x*0.3)/3);
	}
	else if(n_plataformas == 3){
		tam_plataforma.x = tamanho_da_tela_x*0.25f;
		espaco_vazio_x = static_cast<float>((tamanho_da_tela_x*0.25)/4);
	}
	else if(n_plataformas == 4){
		tam_plataforma.x = tamanho_da_tela_x*0.15f;
		espaco_vazio_x = static_cast<float>((tamanho_da_tela_x*0.4)/5);
	}
	else {
		tam_plataforma.x = 0.0;
		espaco_vazio_x = 0.0;
	}
}

void Fases::Fase::seta_Num_Plataformas()
{
	if (num_plataformas_totais < 5) {
		num_plataformas_totais = 5;
	}

	int plataformas = 0;
	int plataformas_restantes = num_plataformas_totais;
	tam_plataforma.x = 0.f;

	const int num_min_plataformas_andar = 1;

	for (int i = 0; i < num_max_andares; i++) {
		if(plataformas_restantes > 0) {
			plataformas = num_min_plataformas_andar + (rand() % 3);

			if(plataformas >= plataformas_restantes) {
				plataformas = plataformas_restantes; 
			}
		}
		else {
			plataformas = 0;
		}

		num_plataformas_por_andar.push_back(plataformas);
		plataformas_restantes -= plataformas;
	}
}

void Fases::Fase::Posiciona_plataforma()
{
	seta_Num_Plataformas();

	sf::Vector2f pos_plataforma;
	float posicao_da_ultima_plataforma = 0.f;
	
	for(int i = 0; i < num_max_andares; i++) {
		for (int j = 0; j < num_plataformas_por_andar[i]; j++){
			seta_Tamanho_Plataformas(num_plataformas_por_andar[i]);

			pos_plataforma.y = pos_Piso.y - ((i + 1)* 180.f);
			pos_plataforma.x = posicao_da_ultima_plataforma + espaco_vazio_x;
			posicao_da_ultima_plataforma = pos_plataforma.x + tam_plataforma.x;

			Cria_Plataforma(tam_plataforma.y, tam_plataforma.x, pos_plataforma.x, pos_plataforma.y);
			criar_Entidades_em_Plataforma(tam_plataforma, pos_plataforma, pos_plataforma.x, pos_plataforma.x + tam_plataforma.x);

			gerenciador_colisoes.Incluir_Obstaculo(static_cast<Obstaculo*>(plataforma));
			lista_Entidades.adicionar(static_cast<Entidade*>(plataforma));
		}

		pos_plataforma.x = 0.f;
		posicao_da_ultima_plataforma = 0.f;
	}
}

void Fases::Fase::verifica_Inimigos_Neutralizados()
{
	std::list<int>::iterator itr = lista_id_inimigos.begin();

    while (itr != lista_id_inimigos.end() && !(lista_id_inimigos.empty())) {
        int id = *itr;
        Entidade* ent = lista_Entidades.get_Entidade_Por_Id(id);

        if (ent == nullptr) {
            itr = lista_id_inimigos.erase(itr);
            continue;
        }

        Inimigo* inim = dynamic_cast<Inimigo*>(ent);
        if (inim == nullptr) {
            ++itr;
            continue;
        }

		if(verifica_Se_Caiu_No_Abismo(static_cast<Entidade*>(inim))){
			inim->diminuir_Vitalidade(200);
		}

        if (inim->get_Eliminado()) {
			remover_Inimigo_Das_Listas_Auxiliares(inim);
			gerenciador_colisoes.Inimigo_neutralizado(inim);
            lista_Entidades.remover(ent);
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

void Fases::Fase::Cria_Obstaculos_Restantes()
{
}

void Fases::Fase::executar_Antes_Entidades()
{
}

void Fases::Fase::executar_Depois_Entidades()
{
}

bool Fases::Fase::verifica_Se_Caiu_No_Abismo(Entidade* pEntidade)
{
	if (chao == nullptr || pEntidade == nullptr) {
		return false;
	}

	return chao->entidade_Caiu_No_Abismo(pEntidade);
}
