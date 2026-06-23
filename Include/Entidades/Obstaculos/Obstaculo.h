#pragma once
#include "Entidades/Entidade.h"
#include "Entidades/Personagens/Jogador/Jogador.h"
#include <string>

namespace Entidades {

	namespace Obstaculos {

		class Obstaculo : public Entidade
		{
			protected:
				// Id base dos obstaculos.
				static const int id_base;

				// Usados para decidir qual obstaculo empurra o outro.
				float massa;
				float densidade_superficial;

			public:
				Obstaculo();
				virtual ~Obstaculo();

				// Configura tamanho, posicao, textura e massa do obstaculo.
				void seta_Obstaculo(float alt, float larg, float origem_x, float origem_y, const std::string& assets);

				// Testa se um ponto fica dentro da forma da figura.
				bool pontoDentroDoPoligono(const sf::Shape& figura, sf::Vector2f ponto);

				// Aproxima a area da figura para calcular massa.
				float calcula_Densidade_de_Area(const sf::Shape& figura, int divisoesHorizontais, int divisoesVerticais);
				
				// Retorna a massa usada nas colisoes entre obstaculos.
				float get_Massa() const;

				virtual void salvar() = 0;
				virtual void executar() = 0;
				virtual void obstacular(Entidades::Personagens::Jogador* p, int lado) = 0;
		};
	}
}
