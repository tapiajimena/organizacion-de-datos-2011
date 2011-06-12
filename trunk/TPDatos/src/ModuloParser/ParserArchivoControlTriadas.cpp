/*
 * ParserArchivoControlTriadas.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ParserArchivoControlTriadas.h"

ParserArchivoControlTriadas::ParserArchivoControlTriadas(string token) :
	ParserTriadas(token) {
	this->datoNuevo = new DatoControlTriada();
}

void ParserArchivoControlTriadas::cargarEstructura(string dato) {
	vector<string> datos = ServiceClass::obtenerListaPalabras(dato,
			CONTROL_TOKEN);

	/* Dado que el orden de los datos es idLibro|IdTriadaInicial|IdTriadaFinal|eliminado */

	this->datoNuevo->setIdLibro(ServiceClass::convertirAUint32(datos.at(0)));
	this->datoNuevo->setIdTriadaInicial(ServiceClass::convertirAUint32(datos.at(1)));
	this->datoNuevo->setIdTriadaFinal(ServiceClass::convertirAUint32(datos.at(2)));
	this->datoNuevo->setEliminado(determinarEliminado());


	Logger::log("parserArchivoControlTriada", "cargarEstructura",
			"Se obtiene el dato de control.");

	DatoControlTriada* d = new DatoControlTriada(this->datoNuevo);

	this->triadas->push_back(d);

	Logger::log("parserArchivoControlTriada", "cargarEstructura",
			"Se le agrega al map un nuevo dato.");
}

bool ParserArchivoControlTriadas::determinarEliminado() {
	//TODO implementar;
}

ParserArchivoControlTriadas::~ParserArchivoControlTriadas() {
	// TODO Auto-generated destructor stub
}
