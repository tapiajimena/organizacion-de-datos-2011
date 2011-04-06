/*
 * Dato.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Dato.h"

Dato::Dato() {
	// TODO Auto-generated constructor stub

}

bool Dato::vacio() {
	//devuelve tipo bool
	return this->dato.empty();
}

void Dato::vaciar() {
	this->dato.clear();
}

bool Dato::agregar(const Dato & d, unsigned int posicion) {

	//si el offset (corrimiento) supera al tamanio de los datos => false
	if (posicion > this->dato.length())
		return false;
	else {
		this->dato.insert(posicion, d.toString());
		return true;
	}
}

bool Dato::agregarAlFinal(const Dato & d) {
	this->agregar(d, this->dato.length());
	return true;
}

char* Dato::toCharPointer() {
	return (char*) this->dato.c_str();;
}

string Dato::getDato() {
	return this->dato;
}

long int Dato::getSize() {
	return this->dato.length();
}

void Dato::setDato(string valor) {
	this->dato = valor;
}

Dato::~Dato() {
	// TODO Auto-generated destructor stub
}
