/*
 * Diccionario.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 */

#include "Diccionario.h"

Diccionario::Diccionario(string nombreArchivo) {
	this->nombreArchivo = nombreArchivo;
	this->parser = new ParserArchivoTexto(STOPWORDS_TOKEN);
	cargarDiccionario();

	Logger::log("Diccionario","diccionario","se crea el diccionario.");
}

void Diccionario::cargarDiccionario() {
	//ESTO DEBERIA ESTAR EN MANEJADOR ARCHIVO
	fstream archivoStopWords;
	archivoStopWords.open(this->nombreArchivo.c_str());

	parser->leerArchivo(&archivoStopWords);
	Logger::log("Diccionario","cargarDiccionario","carga de palabras dentro del diccionario.");
	this->diccionario = parser->getLista();
}

void Diccionario::mostrar() {
	set<string>::iterator it;
	cout << "Contenido:";
	for (it = diccionario->begin(); it != diccionario->end(); it++) {
		cout << *it << endl;
	}
}

bool Diccionario::existePalabra(string palabra) {
	set<string>::iterator it = this->diccionario->find(palabra);
	Logger::log("Diccionario","existePalabra","se chequea la existencia de la palabra en el diccionario.");

	/* Si recorrio el diccionario y encontro la palabra buscada
	 * entonces no llego al final de la estructura.
	 */
	if (it != this->diccionario->end()) return true;
	return false;
}

Diccionario::~Diccionario() {
	// TODO Auto-generated destructor stub
}
