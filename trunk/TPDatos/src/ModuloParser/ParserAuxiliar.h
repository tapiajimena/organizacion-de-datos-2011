/*
 * ParserAuxiliar.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#ifndef PARSERAUXILIAR_H_
#define PARSERAUXILIAR_H_

#include <fstream>
#include <iostream>

#include "../Common/Utilitarios/ServiceClass.h" //Para pasar a minúsculas las palabras que se cargan.
#include "../Common/Utilitarios/Logger.h"
#include "../../Common/Constantes.h"

using namespace std;

class ParserAuxiliar {
protected:
	string separador;
public:
	ParserAuxiliar(string token);

	virtual void leerArchivo(fstream* archivo) = 0;
	virtual void cargarEstructura(string palabra) = 0;

	virtual ~ParserAuxiliar();
};

#endif /* PARSERAUXILIAR_H_ */
