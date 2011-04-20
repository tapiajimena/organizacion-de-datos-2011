/*
 * Instruccion_ListarArchivosTomados.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ListarArchivosTomados.h"

Instruccion_ListarArchivosTomados::Instruccion_ListarArchivosTomados(char id) : Instruccion(id) {
	// TODO Auto-generated constructor stub

}

void Instruccion_ListarArchivosTomados::ejecutar(){
	Logger::log("Instruccion_ListarArchivosTomados", "ejecutar",
			"Se muestran los libros guardados.");
}

Instruccion_ListarArchivosTomados::~Instruccion_ListarArchivosTomados() {
	// TODO Auto-generated destructor stub
}
