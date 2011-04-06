/*
 * String.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "String.h"

String::String(): Dato() {
	// TODO Auto-generated constructor stub

}

String::String(char* s) {
	this->dato = (string) s;
}

String::String(string s) {
	this->dato = s;
}

String::String(const String & s) {
	this->dato = s.dato;
}

string String::toString() const {
	return this->dato;
}

String::~String() {
	// TODO Auto-generated destructor stub
}
