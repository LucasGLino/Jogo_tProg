#pragma once

#include "Entidades/Personagens/Jogador/Jogador.h"
#include "Entidades/Personagens/Inimigos/Inimigo.h"
#include "Entidades/Obstaculos/Obstaculo.h"
#include "Entidades/Projetil.h"
#include <iostream>
#include <vector>
#include <list>
#include <set>


namespace Gerenciadores {
	class Gerenciador_colisoes
	{
	private:
		std::vector<Entidades::Personagens::Inimigo*> lista_Inimigos;
		std::list<Entidades::Obstaculos::Obstaculo*> lista_Obstaculos;
		std::set<Entidades::Projetil*> lista_Projeteis;
		Entidades::Personagens::Jogador* pJogador1;
		Entidades::Personagens::Jogador* pJogador2;

		float empurrao;


		// contador setado, pra evitar ser criado varias vezes durante a execuçao do programa.
		const int direita, cima, esquerda, baixo;

	private:

		void tratar_Colisoes_Projeteis();
		void tratar_Colisoes_Inimigos();
		void tratar_Colisoes_Obstaculo_Obstaculo();
		void tratar_Colisoes_Inimigo_Obstaculo(Entidades::Entidade* pEntidadeRef);
		void tratar_Colisoes_Jogador_Inimigos(Entidades::Personagens::Jogador* p_Jogador, Entidades::Personagens::Inimigo* pInimigo);
		void tratar_Colisoes_Jogador_Obstaculo(Entidades::Personagens::Jogador* p_Jogador);
		void tratar_Colisoes_Jogador_Projeteis(Entidades::Personagens::Jogador* p_Jogador);
		

		const int verifica_Tipo_De_Colisao(Entidades::Entidade* pEntidade_Ref, Entidades::Entidade* pEntidade2);
		const bool verifica_Mesma_Pos(Entidades::Entidade* pEntidade_Ref, Entidades::Entidade* pEntidade2);
		const bool verifica_Colisao_Cima (Entidades::Entidade* pEntidade_Ref, Entidades::Entidade* pEntidade2);
		const bool verifica_Colisao_Esquerda (Entidades::Entidade* pEntidade_Ref, Entidades::Entidade* pEntidade2);
		const bool verifica_Colisao_Baixo (Entidades::Entidade* pEntidade_Ref, Entidades::Entidade* pEntidade2);
		const bool verifica_Colisao_Direita (Entidades::Entidade* pEntidade_Ref, Entidades::Entidade* pEntidade2);

	public:

		Gerenciador_colisoes();
		~Gerenciador_colisoes();

		void Incluir_Obstaculo(Entidades::Obstaculos::Obstaculo* p_Obstaculo);
		void Incluir_Inimigo(Entidades::Personagens::Inimigo* p_Inimigo);
		void Incluir_Projetil(Entidades::Projetil* p_Projetil);
		void Setar_Jogador(Entidades::Personagens::Jogador* p_Jogador1, Entidades::Personagens::Jogador* p_Jogador2);

		void projetil_Destruido(Entidades::Projetil* pProj);
		Entidades::Entidade* Inimigo_neutralizado(Entidades::Personagens::Inimigo* inimigo_eliminado);
		bool verifica_Lista_Inimigos_Vazia();

		void Executar();

	};
}

