/*
 * Instruccion_QuitarArchivo.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_QuitarArchivo.h"

Instruccion_QuitarArchivo::Instruccion_QuitarArchivo(char id,
		uint32_t idArchivo) :
	Instruccion(id) {
	this->idArchivo = idArchivo;
	cout << "idArchivo: " << idArchivo << endl;
}

void Instruccion_QuitarArchivo::ejecutar()
{
	Indexador* indexador = new Indexador();

	//se lo elimina de los indices y biblioteca
	indexador->eliminarIndexado(idArchivo);

	Logger::log("Instruccion_QuitarArchivo", "ejecutar","Se elimina el archivo.");
	delete(indexador);

}

Instruccion_QuitarArchivo::~Instruccion_QuitarArchivo()
{

}
