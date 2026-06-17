#include"Obstaculo.h"


namespace Entidades {
	namespace Obstaculos {
		class Baril : public Obstaculo
		{
		private:
            bool ativa;
            
            int dano_explisivo;

		public:

			Baril();
			~Baril();

			void Executar();
			void obstacular(Entidades::Personagens::Jogador* p, int lado);
			void Salvar();

		};
	}
}