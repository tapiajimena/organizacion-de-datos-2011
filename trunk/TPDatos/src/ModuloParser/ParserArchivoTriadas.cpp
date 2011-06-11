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
	ParserAuxiliar(token) {
	this->triadas = new list<DatoTriada*> ();
	this->it = this->triadas->begin();
	this->contadorLinea = 0;
	this->datoNuevo = new DatoTriada();
}

list<DatoTriada*>* ParserArchivoTriadas::getTriadas(fstream* archivo) {
	return this->triadas;
}

list<DatoTriada*>* ParserArchivoTriadas::getTriadas(fstream* archivo, uint32_t id) {
	return this->triadas;
}

void ParserArchivoTriadas::leerArchivo(fstream* archivo, uint32_t id) {
	char  buffer[CONTROL_LENGTH];

	if (GetSizeArchivo(*archivo) > 0) {
		if (archivo->is_open()) {
			Logger::log("parserArchivoTriadas", "leerArchivo",
					"Se comienza a leer el archivo de control");
			this->it = this->triadas->begin();
			//archivo->seek(id);
			//archivo->get(buffer,MAX_SIZE_TRIADA,SEPARADOR_TRIADA);
			cargarEstructura(buffer);
			this->contadorLinea++;
			this->it++;
		} else {
			Logger::log("parserArchivoTriadas", "leerArchivo",
					"El archivo no esta abierto.");
		}
	} else {
		Logger::log("parserArchivoTriadas", "leerArchivo",
				"El archivo esta vacio o no existe.");
	}
}

void ParserArchivoTriadas::leerArchivo(fstream* archivo) {
	char  buffer[CONTROL_LENGTH];

	if (GetSizeArchivo(*archivo) > 0) {
		if (archivo->is_open()) {
			Logger::log("parserArchivoTriadas", "leerArchivo",
					"Se comienza a leer el archivo de control");
			this->it = this->triadas->begin();
			do {
				//archivo->getline(buffer, SEPARADOR_TRIADA);
				cargarEstructura(buffer);
				this->contadorLinea++;
				this->it++;
			} while (!archivo->eof());
		} else {
			Logger::log("parserArchivoTriadas", "leerArchivo",
					"El archivo no esta abierto.");
		}
	} else {
		Logger::log("parserArchivoTriadas", "leerArchivo",
				"El archivo esta vacio o no existe.");
	}
}

void ParserArchivoTriadas::cargarEstructura(string dato) {
	vector<string> datos = ServiceClass::obtenerListaPalabras(dato,
			CONTROL_TOKEN);

	/* Dado que el orden de los datos es id|espacioLibre|indice */

	//id_Libro, espacioLibre, indexado, offset
//	this->datoNuevo->setEspacioLibre(
//			ServiceClass::convertirAUint32(datos.at(1)));
//	this->datoNuevo->setId_Libro(ServiceClass::convertirAUint32(datos.at(0)));
//	setTipoIndice(datos);
//	this->datoNuevo->setOffset(this->contadorLinea);

	//setTipoIndice(datos);

	Logger::log("parserArchivoControl", "cargarEstructura",
			"Se obtiene el dato de control.");

	//DatoControlTriada* d = new DatoControlTriada(this->datoNuevo);

//	this->triadas->insert(pair<uint32_t, DatoControlTriada*> (
	//		ServiceClass::convertirAUint32(datos.at(0)), d));

	Logger::log("parserArchivoControl", "cargarEstructura",
			"Se le agrega al map un nuevo dato.");
}

ParserArchivoTriadas::~ParserArchivoTriadas() {
	// TODO Auto-generated destructor stub
}
