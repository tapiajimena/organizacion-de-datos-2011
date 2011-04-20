/*
 * Instruccion_QuitarArchivo.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_QuitarArchivo.h"

Instruccion_QuitarArchivo::Instruccion_QuitarArchivo(char id) :
	Instruccion(id) {
	// TODO Auto-generated constructor stub

}

void Instruccion_QuitarArchivo::ejecutar() {
	Logger::log("Instruccion_QuitarArchivo", "ejecutar",
			"Se elimina el archivo.");
}

Instruccion_QuitarArchivo::~Instruccion_QuitarArchivo() {
	// TODO Auto-generated destructor stub
}
