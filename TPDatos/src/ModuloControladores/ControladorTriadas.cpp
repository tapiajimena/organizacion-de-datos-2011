/*
 * ControladorTriadas.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ControladorTriadas.h"

ControladorTriadas::ControladorTriadas(){

}

ControladorTriadas::ControladorTriadas(string pathArchivoTriadas,
		string pathControlTriadas) {

	arcTriadas = new ArchivoTriadas(pathArchivoTriadas);
	arcControl = new ArchivoControlTriadas(pathControlTriadas);

	Logger::log("ControladorTriadas", "ControladorTriadas",
			"Se cargan los libros.");
}

bool ControladorTriadas::eliminarLibro(uint32_t offset) {
	/* Actualiza el estado del archivo de control */
	arcControl->eliminarLibro(offset);

	arcControl->actualizarArchivo();

	Logger::log("ControladorTriadas", "eliminarLibro",
			"Se actualiza el archivo de control.");
}

void ControladorTriadas::actualizarArchivoDeControl() {
	arcControl->actualizarArchivo();
}

ControladorTriadas::~ControladorTriadas() {
	// TODO Auto-generated destructor stub
}
