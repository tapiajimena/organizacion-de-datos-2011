/*
 * Instruccion_ObtenerArchivo.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ObtenerArchivo.h"

Instruccion_ObtenerArchivo::Instruccion_ObtenerArchivo(char id) : Instruccion(id) {
	// TODO Auto-generated constructor stub

}

void Instruccion_ObtenerArchivo::ejecutar(){
	Logger::log("Instruccion_ObtenerArchivo", "ejecutar",
			"Se levanta el archivo de texto.");
}

Instruccion_ObtenerArchivo::~Instruccion_ObtenerArchivo() {
	// TODO Auto-generated destructor stub
}
