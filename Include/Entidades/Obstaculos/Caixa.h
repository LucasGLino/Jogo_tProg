#include"Obstaculo.h"


namespace Entidades {
	namespace Obstaculos {
		class Caixa : public Obstaculo
		{
		private:
            bool ativa;
            
            int dano_explisivo;

			bool Mover_Esq;

			bool mover;

			

		public:

			Caixa();
			~Caixa();

			void Executar();
			void obstacular(Entidades::Personagens::Jogador* p, int lado);
			void Mover_Esquerda();
			void Mover_Direita();
			void Salvar();

		};
	}
}