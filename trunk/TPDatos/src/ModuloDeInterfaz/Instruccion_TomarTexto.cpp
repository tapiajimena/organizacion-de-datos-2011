/*
 * Instruccion_TomarTexto.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_TomarTexto.h"

Instruccion_TomarTexto::Instruccion_TomarTexto(char id) :
	Instruccion(id) {
	// TODO Auto-generated constructor stub

}

void Instruccion_TomarTexto::ejecutar() {
	Logger::log("Instruccion_TomarTexto", "ejecutar",
			"Se toma el archivo correspondiente.");
}

Instruccion_TomarTexto::~Instruccion_TomarTexto() {
	// TODO Auto-generated destructor stub
}
