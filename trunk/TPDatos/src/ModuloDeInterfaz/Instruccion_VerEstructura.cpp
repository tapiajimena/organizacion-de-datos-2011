/*
 * Instruccion_VerEstructura.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_VerEstructura.h"

Instruccion_VerEstructura::Instruccion_VerEstructura(char id, string argvs[]) : Instruccion(id) {
	// TODO Auto-generated constructor stub
}

void Instruccion_VerEstructura::ejecutar(){
	Logger::log("Instruccion_VerEstructura","ejecutar","Se muestra la estructura.");
}

Instruccion_VerEstructura::~Instruccion_VerEstructura() {
	// TODO Auto-generated destructor stub
}
