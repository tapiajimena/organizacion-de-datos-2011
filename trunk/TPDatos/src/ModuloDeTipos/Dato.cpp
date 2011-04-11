/*
 * Dato.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "Dato.h"

Dato::Dato() {
	// TODO Auto-generated constructor stub

}


Dato::Dato(char* d)
{
	this->dato << (string)d;
}

Dato::Dato(const Dato & d)
{
	this->dato << d.dato;
}

Dato::Dato(string s)
{
	this->dato << s;
}


void Dato::vaciar()
{
	this->dato.clear();
	this->dato.str( "" );
}

bool Dato::estaVacio()
{
	return this->dato.str().empty();//devuelve tipo bool
}



string Dato::toString() const
{
	return this->dato.str();
}


char* Dato::toCharPointer()
{
	string aux = this->dato.str();
	return (char*) aux.c_str();
}

string Dato::getDato()
{
	return this->dato.str();
}


void Dato::setDato(stringstream dato)
{
	this->vaciar();
    this->dato << dato;
}

void Dato::setDato(char* dato)
{
	this->vaciar();
	this->dato << (string)dato;
}

void Dato::setDato(string dato)
{
	this->vaciar();
	this->dato << dato;
}

long int Dato::getSize()
{
	string aux = dato.str();
	return aux.length();
}

Dato::~Dato() {
	// TODO Auto-generated destructor stub
}
