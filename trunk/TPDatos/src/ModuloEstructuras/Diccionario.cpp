/*
 * Diccionario.cpp
 *
 *  Created on: Apr 9, 2011
 *      Author: jimena
 */

#include "Diccionario.h"

Diccionario::Diccionario(string nombreArchivo) {
	this->nombreArchivo = nombreArchivo;
	this->parser = new ParserArchivoTexto(STOPWORDS_TOKEN);
	cargarDiccionario();
}

void Diccionario::cargarDiccionario() {
	//ESTO DEBERIA ESTAR EN MANEJADOR ARCHIVO
	fstream archivoStopWords;
	archivoStopWords.open(this->nombreArchivo.c_str());

	parser->leerArchivo(&archivoStopWords);
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

	/* Si recorrio el diccionario y encontro la palabra buscada
	 * entonces no llego al final de la estructura.
	 */
	if (it != this->diccionario->end()) return true;
	return false;
}

Diccionario::~Diccionario() {
	// TODO Auto-generated destructor stub
}
