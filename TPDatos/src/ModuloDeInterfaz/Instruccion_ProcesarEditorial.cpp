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

}

void Instruccion_ProcesarEditorial::ejecutar(){
	Indexador* indexador = new Indexador();

	indexador->indexar(INDICE_EDITORIAL);

	cout<<"Se indexan nuevos registros indice de editorial."<<endl;
	Logger::log("Instruccion_ProcesarEditorial", "ejecutar",
			"Se indexa por editorial.");

	delete(indexador);
}

Instruccion_ProcesarEditorial::~Instruccion_ProcesarEditorial() {

}
