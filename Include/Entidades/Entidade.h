#pragma once

#include "Entidades/Ente.h"

namespace Entidades 
{
	class Entidade: public Ente
	{
	protected:
		// Tamanho logico usado para configurar a figura.
		sf::Vector2f tamanho;

		// Textura aplicada na figura da entidade.
		sf::Texture textura;

		// Posicao atual da entidade no mundo.
		sf::Vector2f pos;

		// Velocidade usada por movimento e gravidade.
		sf::Vector2f velocidade;

		// Limite de queda usado pela gravidade.
		float gravidade;

		// Constantes para padronizar os lados de colisao.
		const int direita, cima, esquerda, baixo;

	public:
		Entidade(int semente, sf::Vector2f p, sf::Vector2f tam);
		virtual ~Entidade();

		// Aplica queda vertical limitada pela gravidade.
		virtual void executar_Gravidade();

		// Retorna o ponto central da entidade.
		sf::Vector2f get_Centro();

		// Retorna as dimensoes atuais da figura.
		float get_Largura();
		float get_Altura();

		// Retorna os limites inferior e direito da entidade.
		float get_Comprimento_A();
		float get_Comprimento_L();

		// Retorna as coordenadas atuais da entidade.
		float get_X() const;
		float get_Y() const;

		// Atualiza a posicao logica e a posicao da figura.
		void setar_Pos(float pos_x, float pos_y);
		void setar_Pos(sf::Vector2f p);

		// Define a velocidade base da entidade.
		void setar_velocidade(float vel_x, float vel_y);

		// Salva o estado especifico de cada entidade filha.
		virtual void salvar() = 0;

		// Executa o comportamento especifico de cada entidade filha.
		virtual void executar() = 0;
	};
}
