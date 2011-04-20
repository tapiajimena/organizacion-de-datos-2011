/*
 * Instruccion_ProcesarAutor.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ProcesarAutor.h"

Instruccion_ProcesarAutor::Instruccion_ProcesarAutor(char id) : Instruccion(id) {
	// TODO Auto-generated constructor stub

}

void Instruccion_ProcesarAutor::ejecutar(){
	Logger::log("Instruccion_ProcesarAutor", "ejecutar",
			"Se indexa por autor.");
}

Instruccion_ProcesarAutor::~Instruccion_ProcesarAutor() {
	// TODO Auto-generated destructor stub
}
