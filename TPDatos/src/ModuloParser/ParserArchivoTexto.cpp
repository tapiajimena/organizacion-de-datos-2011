/*
 * ParserArchivoTexto.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ParserArchivoTexto.h"

ParserArchivoTexto::ParserArchivoTexto(string token) {
	this->separador = token;
	this->listaPalabras = new set<string> ();
	this->it = listaPalabras->begin();
}

void ParserArchivoTexto::leerArchivo(fstream* archivo) {
	char buffer[STOPWORDS_LENGTH];

	if (archivo->is_open()) {
		//METER LOGGER(parserArchivoTexto,leerArchivo,"Se comienza a leer el archivo de stopwords");
		do {
			archivo->getline(buffer, STOPWORDS_LENGTH);
			cargarEstructura(getDato(buffer));
		} while (!archivo->eof());
	} else {
		//METER LOGGER(parserArchivoTexto,leerArchivo,"No se pudo abrir el archivo de stopworkds");
	}

}

string ParserArchivoTexto::getDato(string buffer) {
	return string(buffer.substr(0, buffer.size()));
}

set<string>* ParserArchivoTexto::getLista() {
	return this->listaPalabras;
}

void ParserArchivoTexto::cargarEstructura(string palabra) {
	if (palabra != STOPWORDS_TOKEN)
		this->listaPalabras->insert(palabra);
}

ParserArchivoTexto::~ParserArchivoTexto() {
	this->listaPalabras->clear();
	delete (this->listaPalabras);
}
