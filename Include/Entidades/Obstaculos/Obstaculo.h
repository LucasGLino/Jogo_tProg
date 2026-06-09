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

				sf::Vector2f tamanho;

			public:
				Obstaculo();
				~Obstaculo();

				virtual void executar_Gravidade();
				virtual void salvar();
				virtual void executar();
				virtual void Salvar() = 0;
				virtual void Executar() = 0;
				virtual void obstacular(Entidades::Personagens::Jogador* p, int lado) = 0;
		};
	}
}
