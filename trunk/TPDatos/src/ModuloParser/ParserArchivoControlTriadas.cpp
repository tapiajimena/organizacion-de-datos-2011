/*
 * ParserArchivoControlTriadas.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ParserArchivoControlTriadas.h"

ParserArchivoControlTriadas::ParserArchivoControlTriadas(string token) {
	this->datoNuevo = new DatoControlTriada();
	this->datosControl = new map<uint32_t,DatoControlTriada*>;
	this->separador = token;
}

void ParserArchivoControlTriadas::cargarEstructura(string dato) {
	vector<string> datos = ServiceClass::obtenerListaPalabras(dato,
			CONTROL_TOKEN);

	/* Dado que el orden de los datos es idLibro|IdTriadaInicial|IdTriadaFinal|eliminado */

	this->datoNuevo->setIdLibro(ServiceClass::convertirAUint32(datos.at(0)));
	this->datoNuevo->setIdTriadaInicial(ServiceClass::convertirAUint32(
			datos.at(1)));
	this->datoNuevo->setIdTriadaFinal(ServiceClass::convertirAUint32(
			datos.at(2)));
	this->datoNuevo->setEliminado(determinarEliminado(
			(ServiceClass::convertirAUint32(datos.at(3)))));

	Logger::log("parserArchivoControlTriada", "cargarEstructura",
			"Se obtiene el dato de control.");

	DatoControlTriada* d = new DatoControlTriada(this->datoNuevo);

	this->datosControl->insert(pair<uint32_t, DatoControlTriada*> (
			ServiceClass::convertirAUint32(datos.at(0)), d));

	Logger::log("parserArchivoControlTriada", "cargarEstructura",
			"Se le agrega al map un nuevo dato.");
}

map<uint32_t, DatoControlTriada*>* ParserArchivoControlTriadas::getDatosControl(
		fstream* archivo) {
	IrAlInicio(*archivo);
	leerArchivo(archivo);
	return this->datosControl;
}

void ParserArchivoControlTriadas::leerArchivo(fstream* archivo) {
	char buffer[CONTROL_LENGTH];

	if (GetSizeArchivo(*archivo) > 0) {
		if (archivo->is_open()) {
			Logger::log("parserArchivoControlTriadas", "leerArchivo",
					"Se comienza a leer el archivo de control");
			this->it = this->datosControl->begin();

			do {
				archivo->getline(buffer, CONTROL_LENGTH);
				cargarEstructura(buffer);
				this->contadorLinea++;
				this->it++;
			} while (!archivo->eof());
		} else {
			Logger::log("parserArchivoControlTriadas", "leerArchivo",
					"El archivo no esta abierto.");
		}
	} else {
		Logger::log("parserArchivoControlTriadas", "leerArchivo",
				"El archivo esta vacio o no existe.");
	}
}

bool ParserArchivoControlTriadas::determinarEliminado(uint32_t eliminado) {
	bool estaEliminado = true;

	if (eliminado == 0)
		estaEliminado = false;

	return estaEliminado;
}

ParserArchivoControlTriadas::~ParserArchivoControlTriadas() {
	// TODO Auto-generated destructor stub
}
