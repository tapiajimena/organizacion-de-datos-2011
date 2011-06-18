/*
 * ParserTriadas.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ParserTriadas.h"

ParserTriadas::ParserTriadas(string token) :
	ParserAuxiliar(token) {
	this->triadas = new list<Dato*> ();
	this->it = this->triadas->begin();
	this->contadorLinea = 0;
}

list<Dato*>* ParserTriadas::getTriadas(fstream* archivo) {
	return this->triadas;
}

list<Dato*>* ParserTriadas::getTriadas(fstream* archivo, uint32_t id) {
	return this->triadas;
}

void ParserTriadas::leerArchivo(fstream* archivo) {
	char buffer[CONTROL_LENGTH];

	if (GetSizeArchivo(*archivo) > 0) {
		if (archivo->is_open()) {
			Logger::log("ParserTriadas", "leerArchivo",
					"Se comienza a leer el archivo de control");
			this->it = this->triadas->begin();
			do {
				//archivo->getline(buffer, SEPARADOR_TRIADA);
				cargarEstructura(buffer);
				cout<<"BUFFER: "<<buffer<<endl;
				this->contadorLinea++;
				this->it++;
			} while (!archivo->eof());
		} else {
			Logger::log("ParserTriadas", "leerArchivo",
					"El archivo no esta abierto.");
		}
	} else {
		Logger::log("ParserTriadas", "leerArchivo",
				"El archivo esta vacio o no existe.");
	}
}


ParserTriadas::~ParserTriadas() {
	// TODO Auto-generated destructor stub
}
