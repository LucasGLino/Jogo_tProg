#pragma once
#include "Entidades/Entidade.h"
#include "Entidades/Personagens/Jogador/Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Obstaculo : public Entidade
		{
			protected:
				bool danoso;
				static const int id_base;

				float massa;
				float densidade_superficial;

				sf::Vector2f tamanho;

			public:
				Obstaculo();
				~Obstaculo();

				
				// virtual void executar_Gravidade();
				void seta_Obstaculo(float alt, float larg, float origem_x, float origem_y,std::string assets);
				bool pontoDentroDoPoligono(const sf::Shape& figura, sf::Vector2f ponto);
				float calcula_Densidade_de_Area(const sf::Shape& figura, int divisoesHorizontais, int divisoesVerticais);
				//void setar_Massa_Densidade(int aux_massa);
				
				float get_Massa();

				virtual void salvar() = 0;
				virtual void executar() = 0;
				virtual void obstacular(Entidades::Personagens::Jogador* p, int lado) = 0;
		};
	}
}
