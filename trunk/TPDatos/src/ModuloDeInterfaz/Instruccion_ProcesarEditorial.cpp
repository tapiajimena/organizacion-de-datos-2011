/*
 * Instruccion_ProcesarEditorial.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ProcesarEditorial.h"

Instruccion_ProcesarEditorial::Instruccion_ProcesarEditorial(char id) : Instruccion(id) {
	// TODO Auto-generated constructor stub

}

void Instruccion_ProcesarEditorial::ejecutar(){
	Logger::log("Instruccion_ProcesarEditorial", "ejecutar",
			"Se indexa por editorial.");
}

Instruccion_ProcesarEditorial::~Instruccion_ProcesarEditorial() {
	// TODO Auto-generated destructor stub
}
