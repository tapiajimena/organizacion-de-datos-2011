/*
 * Instruccion_TomarTexto.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_TomarTexto.h"

Instruccion_TomarTexto::Instruccion_TomarTexto(char id, string pathLibro) :
	Instruccion(id) {
	this->libroNuevo = pathLibro;

}

void Instruccion_TomarTexto::ejecutar() {
	Configuracion* conf = Configuracion::GetInstancia();

	this->controladorBiblioteca = new ControladorBiblioteca(
			conf->getPathCarpetaTrabajo() + ARCHIVO_BIBLIOTECA + EXTENSION_ARCHIVO_INDICE,
			conf->getPathCarpetaTrabajo() + ARCHIVO_CONTROL_BIBLIOTECA);

	this->controladorBiblioteca->ingresarLibro(this->libroNuevo);

	Logger::log("Instruccion_TomarTexto", "ejecutar",
			"Se toma el archivo correspondiente.");
}

Instruccion_TomarTexto::~Instruccion_TomarTexto() {
	// TODO Auto-generated destructor stub
}
