#pragma once

#include "Entidades/Entidade.h"
#include <string>

namespace Entidades {
	class Chao : public Entidade
	{
	private:
		static const int id_base;
		float limite_abismo;

	public:
		Chao();
		~Chao();

		void configurar_Chao(float alt, float larg, float origem_x, float origem_y, std::string assets);
		void setar_Limite_Abismo(float limite);
		bool entidade_Caiu_No_Abismo(Entidades::Entidade* pEntidade);

		void executar();
		void salvar();
	};
}
