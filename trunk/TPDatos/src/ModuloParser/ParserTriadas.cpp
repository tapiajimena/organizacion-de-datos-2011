/*
 * ParserTriadas.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ParserTriadas.h"

ParserTriadas::ParserTriadas(string token) {
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

ParserTriadas::~ParserTriadas() {
	delete(this->triada);

	//elimina cada dato dentro de triadas
	list<DatoTriada*>::iterator itTriadas;
	for(itTriadas= this->triadas->begin(); itTriadas != triadas->end();itTriadas++)
		delete(*itTriadas);
	delete(triadas);

	Logger::log("ParserArchivoControlTriadas", "~ParserArchivoControlTriadas",
			"Se elimina el ParserArchivoControlTriadas.");
}
