#pragma once

#include "Entidades/Entidade.h"
#include <string>

namespace Entidades {
	class Chao : public Entidade
	{
	private:
		// Id base separado para o chao.
		static const int id_base;

		// Abaixo desse Y, a entidade ja caiu fora da fase.
		float limite_abismo;

	public:
		Chao();
		virtual ~Chao();

		// Monta tamanho, textura e posicao do piso.
		void configurar_Chao(float alt, float larg, float origem_x, float origem_y, const std::string& assets);

		// Permite ajustar onde comeca o abismo.
		void setar_Limite_Abismo(float limite);

		// Diz se a entidade passou do limite inferior da fase.
		bool entidade_Caiu_No_Abismo(Entidades::Entidade* pEntidade);

		// Desenha o chao.
		void executar();

		// Salvar ainda nao foi implementado para chao.
		void salvar();
	};
}
