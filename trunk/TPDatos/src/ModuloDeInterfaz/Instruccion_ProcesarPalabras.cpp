/*
 * Instruccion_ProcesarPalabras.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ProcesarPalabras.h"

Instruccion_ProcesarPalabras::Instruccion_ProcesarPalabras(char id) : Instruccion(id) {
	// TODO Auto-generated constructor stub

}

void Instruccion_ProcesarPalabras::ejecutar(){
	Indexador* indexador = new Indexador();

	indexador->indexar(INDICE_PALABRAS);

	cout<<"Se indexan nuevos registros indice de palabras."<<endl;
	Logger::log("Instruccion_ProcesarPalabras", "ejecutar",
			"Se indexa por palabras.");

	delete(indexador);
}

Instruccion_ProcesarPalabras::~Instruccion_ProcesarPalabras() {
	// TODO Auto-generated destructor stub
}
