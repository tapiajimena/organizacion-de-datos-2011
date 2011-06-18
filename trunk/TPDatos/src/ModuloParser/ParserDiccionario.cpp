/*
 * ParserDiccionario.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ParserDiccionario.h"

ParserDiccionario::ParserDiccionario(string token) :
	ParserAuxiliar(token) {
	this->separador = token;
	this->listaPalabras = new set<string> ();
	this->it = listaPalabras->begin();
}

string ParserDiccionario::getDato(string buffer) {
	return string(buffer.substr(0, buffer.size()-1));
}

void ParserDiccionario::leerArchivo(fstream* archivo) {
	char buffer[STOPWORDS_LENGTH];

	if (archivo->is_open()) {
		Logger::log("parserDiccionario", "leerArchivo",
				"Se comienza a leer el archivo de stopwords");
		do {
			archivo->getline(buffer, STOPWORDS_LENGTH);
			cargarEstructura(getDato(buffer));
		} while (!archivo->eof());
	} else {
		Logger::log("parserDiccionario", "leerArchivo",
				"No se pudo abrir el archivo de stopworkds");
	}
}

set<string>* ParserDiccionario::getLista() {
	return this->listaPalabras;
}

void ParserDiccionario::cargarEstructura(string palabra) {
	if (palabra != STOPWORDS_TOKEN) {
		//Se pasa la palabra a minúsculas
		palabra = ServiceClass::toDowncase(palabra);
		this->listaPalabras->insert(palabra);
	}
}

ParserDiccionario::~ParserDiccionario() {
	this->listaPalabras->clear();
	delete (this->listaPalabras);
}
