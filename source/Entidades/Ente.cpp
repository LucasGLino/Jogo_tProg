#include "Entidades/Ente.h"


// Contador compartilhado por todos os entes criados.
int Ente::id_contador = 1;

// Inicializa o id, o gerenciador grafico e a figura base do ente.
Ente::Ente(int semente):id(semente + (id_contador++))
{
	pGG = Gerenciadores::Gerenciador_Grafico::getInstancia();
	pFigura = new sf::RectangleShape;
}

// Libera a figura alocada pelo ente.
Ente::~Ente()
{
	if(pFigura) {
		delete pFigura;
	}
}

// Envia a figura base para o gerenciador grafico desenhar.
void Ente::desenhar()
{
	pGG->desenhar(pFigura);
}

// Retorna o id usado para localizar o ente nas listas.
int Ente::getId() const
{
	return id;
}
