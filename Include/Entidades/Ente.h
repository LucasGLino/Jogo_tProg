#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"

#include <iostream>
#include <string>

//using namespace std;
//using namespace Gerenciadores;

class Ente
{
protected:
	int id;
	static int id_contador;

	//acesso a biblioteca graf (eveitar includes redundantes)
	Gerenciadores::Gerenciador_Grafico* pGG;

	//todo Ente possu� uma figura retangular
	sf::RectangleShape* pFigura;


	Ente(int semente);
	virtual ~Ente();
	virtual void executar() = 0;
	void desenhar();
	
public:
	int getId() const;
	void operator++();
	void operator--();

};
