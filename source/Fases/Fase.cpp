#include "Fases/Fase.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace Fases;
using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;

int Fases::Fase::base_Id = 0;

// Inicializa os dados gerais da fase, incluindo sorteios, camera, piso e fundo.
Fase::Fase(): Ente(base_Id)
{
	static bool sorteio_iniciado = false;
	if (!sorteio_iniciado) {
		srand(static_cast<unsigned int>(time(0)));
		sorteio_iniciado = true;
	}

	ganhou = false;
	chao = nullptr;
	lista_id_inimigos.clear();
	posicoes_spawn_usadas.clear();


	num_plataformas_totais = rand() % 10;

	// Cada fase sempre comeca com 4 a 6 piratas.
	num_piratas = (rand() % 3) + 4;


	num_restante_piratas = num_piratas;
	num_max_andares = 4;
	num_piratas_em_plataformas = 0;

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

// Libera as estruturas auxiliares que a fase mantem.
Fase::~Fase()
{
	num_plataformas_por_andar.clear();
	posicoes_spawn_usadas.clear();
	chao = nullptr;
}

// Registra os jogadores nos sistemas da fase e posiciona eles no chao.
void Fases::Fase::Setar_Jogadores(Jogador* p_jogador1,Jogador* p_jogador2)
{
	Setar_Jogadores_Colisoes(p_jogador1, p_jogador2);
	Setar_Jogadores_Inimigos(p_jogador1, p_jogador2);
	
	// Os jogadores sempre iniciam sobre o chao da fase.
	if (p_jogador1 != nullptr) {
		p_jogador1->setar_Pos(25.f, pos_Piso.y - p_jogador1->get_Altura());
	}
	if (p_jogador2 != nullptr) {
		p_jogador2->setar_Pos(25.f, pos_Piso.y - p_jogador2->get_Altura());
	}
}

// Envia os jogadores para o gerenciador de colisoes.
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

// Atualiza os alvos dos inimigos ja criados.
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

// Permite que fases derivadas removam inimigos de listas auxiliares proprias.
void Fases::Fase::remover_Inimigo_Das_Listas_Auxiliares(Inimigo* pInimigo)
{
	(void)pInimigo;
}

// Permite que fases derivadas criem obstaculos depois do chao e das plataformas.
void Fases::Fase::Cria_Obstaculos_Restantes()
{
}

// Gancho usado por fases derivadas antes da lista de entidades executar.
void Fases::Fase::executar_Antes_Entidades()
{
}

// Gancho usado por fases derivadas depois da lista de entidades executar.
void Fases::Fase::executar_Depois_Entidades()
{
}

// Verifica se uma posicao de spawn ja foi usada por outra entidade.
bool Fases::Fase::posicao_Spawn_Ja_Usada(float x, float y_referencia)
{
	const float tolerancia = 1.0f;
	float diferenca_x;
	float diferenca_y;

	for (int i = 0; i < static_cast<int>(posicoes_spawn_usadas.size()); i++) {
		diferenca_x = posicoes_spawn_usadas[i].x - x;
		diferenca_y = posicoes_spawn_usadas[i].y - y_referencia;

		if (diferenca_x < 0.f) {
			diferenca_x *= -1.f;
		}
		if (diferenca_y < 0.f) {
			diferenca_y *= -1.f;
		}

		if (diferenca_x <= tolerancia && diferenca_y <= tolerancia) {
			return true;
		}
	}

	return false;
}

// Guarda uma posicao usada para os proximos spawns conseguirem desviar dela.
void Fases::Fase::registrar_Posicao_Spawn(float x, float y_referencia)
{
	posicoes_spawn_usadas.push_back(sf::Vector2f(x, y_referencia));
}

// Ajusta o x do spawn para evitar duas entidades exatamente no mesmo lugar.
float Fases::Fase::ajustar_X_Spawn(float x, float y_referencia)
{
	const int max_tentativas = 10;
	const float deslocamento = 40.f;

	float x_spawn = x;
	int tentativa = 0;

	while (posicao_Spawn_Ja_Usada(x_spawn, y_referencia) && tentativa < max_tentativas) {
		x_spawn += deslocamento;
		tentativa++;
	}

	while (posicao_Spawn_Ja_Usada(x_spawn, y_referencia)) {
		x_spawn += 3.f;
	}

	registrar_Posicao_Spawn(x_spawn, y_referencia);
	return x_spawn;
}

// Decide se ainda pode criar uma entidade na plataforma sem esvaziar o chao.
bool Fases::Fase::pode_Criar_Na_Plataforma(int total_restante, int minimo_no_chao)
{
	return total_restante > minimo_no_chao;
}

// Cria um pirata, define sua patrulha e registra ele na fase.
void Fases::Fase::Cria_Pirata(float x, float y, float patrulha_ate_a, float patrulha_ate_b)
{
	Pirata* pirata = new Pirata;
	float x_spawn = ajustar_X_Spawn(x, y);

	pirata->setar_Pos(x_spawn, y - pirata->get_Altura());
	pirata->setar_Patrulha(patrulha_ate_a, patrulha_ate_b);

	lista_id_inimigos.push_front(pirata->getId());
	gerenciador_colisoes.Incluir_Inimigo(pirata);
	lista_Entidades.adicionar(static_cast<Entidade*>(pirata));
}

// Cria no chao os piratas que nao foram colocados em plataformas.
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

// Instancia uma plataforma e devolve o ponteiro para registro na fase.
Plataforma* Fases::Fase::Cria_Plataforma(float alt, float larg, float origem_x, float origem_y)
{
	Plataforma* pPlataforma = new Plataforma;
	pPlataforma->seta_Obstaculo(alt, larg, origem_x, origem_y,"Assets/Imagens/Plataforma.png");
	pPlataforma->seta_Origem(origem_x,origem_y);

	return pPlataforma;
}

// Retorna se todos os inimigos da fase ja foram neutralizados.
bool Fases::Fase::get_Ganhou() const
{
	return ganhou;
}

// Executa a fase enquanto ela ainda nao foi vencida.
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

// Cria o chao e registra ele na lista de entidades e nas colisoes.
void Fases::Fase::Cria_Piso()
{
	chao = new Chao;
	chao->configurar_Chao(tam_Piso_Fase.y, tam_Piso_Fase.x, pos_Piso.x, pos_Piso.y, "Assets/Imagens/Chao.png");
	chao->setar_Limite_Abismo(pos_Piso.y + tam_Piso_Fase.y);

	gerenciador_colisoes.Incluir_Chao(chao);
	lista_Entidades.adicionar(static_cast<Entidade*>(chao));
}

// Cria os inimigos especificos da fase e completa os piratas restantes.
void Fases::Fase::Cria_Inimigos()
{
	Cria_Inimigos_Especificos();
	Cria_Piratas_Restantes();
}

// Cria chao, plataformas e depois os obstaculos proprios da fase.
void Fases::Fase::Cria_Obstaculos()
{
	Cria_Piso();
	Posiciona_plataforma();
	Cria_Obstaculos_Restantes();
}

// Ajusta o fundo para cobrir a area atual da camera.
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

// Atualiza a posicao da camera usada pela fase.
void Fases::Fase::atualiza_Camera_Fase(Jogador* p_jogador1, Jogador* p_jogador2)
{
	(void)p_jogador1;
	(void)p_jogador2;

	sf::Vector2f pos_camera;

	pos_camera.x = tam_Piso_Fase.x/2;
	pos_camera.y = -tam_Piso_Fase.y/3;

	pGG->getCamera()->setCenter(pos_camera);
	ajustar_Fundo_A_Camera();
}

// Aplica o zoom base da fase na camera.
void Fases::Fase::setar_Camera_Fase()
{
	pGG->getCamera()->zoom(zoom_camera);
}

// Define tamanho e espacamento horizontal das plataformas de um andar.
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

// Sorteia e distribui a quantidade total de plataformas entre os andares.
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

// Posiciona as plataformas e chama a fase derivada para preencher cada uma.
void Fases::Fase::Posiciona_plataforma()
{
	seta_Num_Plataformas();

	sf::Vector2f pos_plataforma;
	Plataforma* pPlataforma;
	float posicao_da_ultima_plataforma = 0.f;
	
	for(int i = 0; i < num_max_andares; i++) {
		for (int j = 0; j < num_plataformas_por_andar[i]; j++){
			seta_Tamanho_Plataformas(num_plataformas_por_andar[i]);

			pos_plataforma.y = pos_Piso.y - ((i + 1)* 180.f);
			pos_plataforma.x = posicao_da_ultima_plataforma + espaco_vazio_x;
			posicao_da_ultima_plataforma = pos_plataforma.x + tam_plataforma.x;

			pPlataforma = Cria_Plataforma(tam_plataforma.y, tam_plataforma.x, pos_plataforma.x, pos_plataforma.y);
			criar_Entidades_em_Plataforma(tam_plataforma, pos_plataforma, pos_plataforma.x, pos_plataforma.x + tam_plataforma.x);

			gerenciador_colisoes.Incluir_Obstaculo(static_cast<Obstaculo*>(pPlataforma));
			lista_Entidades.adicionar(static_cast<Entidade*>(pPlataforma));
		}

		pos_plataforma.x = 0.f;
		posicao_da_ultima_plataforma = 0.f;
	}
}

// Remove inimigos derrotados e pune os que cairem no abismo.
void Fases::Fase::verifica_Inimigos_Neutralizados()
{
	std::list<int>::iterator itr = lista_id_inimigos.begin();

    while (itr != lista_id_inimigos.end()) {
        int id = *itr;
        Entidade* pEntidade = lista_Entidades.get_Entidade_Por_Id(id);

        if (pEntidade == nullptr) {
            itr = lista_id_inimigos.erase(itr);
            continue;
        }

        Inimigo* pInimigo = dynamic_cast<Inimigo*>(pEntidade);
        if (pInimigo == nullptr) {
            ++itr;
            continue;
        }

		if(verifica_Se_Caiu_No_Abismo(static_cast<Entidade*>(pInimigo))){
			pInimigo->diminuir_Vitalidade(200);
		}

        if (pInimigo->get_Eliminado()) {
			remover_Inimigo_Das_Listas_Auxiliares(pInimigo);
			gerenciador_colisoes.Inimigo_neutralizado(pInimigo);
            lista_Entidades.remover(pEntidade);
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

// Pergunta ao chao se uma entidade passou do limite do abismo.
bool Fases::Fase::verifica_Se_Caiu_No_Abismo(Entidade* pEntidade)
{
	if (chao == nullptr || pEntidade == nullptr) {
		return false;
	}

	return chao->entidade_Caiu_No_Abismo(pEntidade);
}
