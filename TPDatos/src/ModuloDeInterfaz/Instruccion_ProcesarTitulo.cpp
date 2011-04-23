/*
 * Instruccion_ProcesarTitulo.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ProcesarTitulo.h"

Instruccion_ProcesarTitulo::Instruccion_ProcesarTitulo(char id) :
	Instruccion(id) {
	// TODO Auto-generated constructor stub

}

void Instruccion_ProcesarTitulo::ejecutar() {
	Logger::log("Instruccion_ProcesarTitulo", "ejecutar",
			"Se indexa por titulo.");
}

Instruccion_ProcesarTitulo::~Instruccion_ProcesarTitulo() {
	// TODO Auto-generated destructor stub
}