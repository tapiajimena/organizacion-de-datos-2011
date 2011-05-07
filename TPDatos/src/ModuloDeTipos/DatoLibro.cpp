/*
 * DatoLibro.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 */

#include "DatoLibro.h"

DatoLibro::DatoLibro() :
	Dato() {
	// TODO Auto-generated constructor stub

}

DatoLibro::DatoLibro(const DatoLibro & d) :
	Dato(d) {
	// TODO Auto-generated constructor stub

}

DatoLibro::DatoLibro(char* c) :
	Dato(c) {

}

DatoLibro::DatoLibro(string s) :
	Dato(s) {

}

bool DatoLibro::agregar(const Dato & d, unsigned int posicion) {
	//si el offset (corrimiento) supera el tamano de los dato => false
	if (posicion > this->dato.str().length())
		return false;
	else {
		//TODO revisar bien que solo serviria para char* o string
		this->dato.str().insert(posicion, d.toString());
		return true;
	}

}

bool DatoLibro::agregarAlFinal(const Dato & d) {
	this->agregar(d, this->dato.str().length());
	return true;
}

DatoLibro::~DatoLibro() {
	this->dato.clear();
	this->dato.str("");
}
