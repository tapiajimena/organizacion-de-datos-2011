/*
 * ParserArchivoTriadas.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ParserArchivoTriadas.h"

ParserArchivoTriadas::ParserArchivoTriadas(string token) :
	ParserTriadas(token) {
	this->datoNuevo = new DatoTriada();
}

void ParserArchivoTriadas::cargarEstructura(string dato) {
	vector<string> datos = ServiceClass::obtenerListaPalabras(dato,
			CONTROL_TOKEN);

	/* Dado que el orden de los datos es id_Libro|idTermino|posicionRelativa */

	this->datoNuevo->setIdLibro(ServiceClass::convertirAUint32(datos.at(0)));
	this->datoNuevo->setIdTermino(ServiceClass::convertirAUint32(datos.at(1)));
	this->datoNuevo->setPosicion(2);

	Logger::log("parserArchivoControl", "cargarEstructura",
			"Se obtiene el dato de control.");

	DatoTriada* d = new DatoTriada(this->datoNuevo);

	this->triadas->push_back(d);

	Logger::log("parserArchivoControl", "cargarEstructura",
			"Se le agrega al map un nuevo dato.");
}

ParserArchivoTriadas::~ParserArchivoTriadas() {
	// TODO Auto-generated destructor stub
}
