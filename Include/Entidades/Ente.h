#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"

class Ente
{
protected:
	// Guarda o identificador individual do objeto.
	int id;

	// Gera ids crescentes para os novos entes.
	static int id_contador;

	// Acesso compartilhado ao gerenciador grafico.
	Gerenciadores::Gerenciador_Grafico* pGG;

	// Figura base usada para desenhar o ente.
	sf::RectangleShape* pFigura;

	Ente(int semente);

	// Desenha a figura base do ente na janela.
	void desenhar();

public:
	// Permite destruir objetos derivados por ponteiro de Ente.
	virtual ~Ente();

	// Executa o comportamento especifico de cada classe filha.
	virtual void executar() = 0;

	// Retorna o identificador do ente.
	int getId() const;
};
