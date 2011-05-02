/*
 * Instruccion_ObtenerArchivo.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ObtenerArchivo.h"

Instruccion_ObtenerArchivo::Instruccion_ObtenerArchivo(char id, uint32_t idLibro) : Instruccion(id) {
	this->idLibro = idLibro;
}

void Instruccion_ObtenerArchivo::ejecutar(){
	Configuracion* conf = Configuracion::GetInstancia();
	this->controladorBiblioteca = new ControladorBiblioteca(
			conf->getPathCarpetaTrabajo() + "/" + ARCHIVO_BIBLIOTECA + EXTENSION_ARCHIVO_INDICE,
			conf->getPathCarpetaTrabajo() + "/" + ARCHIVO_CONTROL_BIBLIOTECA);

	cout << (this->controladorBiblioteca->recuperarLibro(this->idLibro)).getDato() << endl;

	Logger::log("Instruccion_ObtenerArchivo", "ejecutar",
			"Se levanta el archivo de texto.");
}

Instruccion_ObtenerArchivo::~Instruccion_ObtenerArchivo() {
	// TODO Auto-generated destructor stub
}
