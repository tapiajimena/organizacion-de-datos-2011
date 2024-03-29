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

}

void Instruccion_ProcesarAutor::ejecutar(){
	Indexador* indexador = new Indexador();

	indexador->indexar(INDICE_AUTOR);

	cout<<"Se indexan nuevos registros indice de autor."<<endl;
	Logger::log("Instruccion_ProcesarAutor", "ejecutar",
			"Se indexa por autor.");

	delete(indexador);
}

Instruccion_ProcesarAutor::~Instruccion_ProcesarAutor() {

}
