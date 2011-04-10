/*
 * Dato.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Dato (75.06) - FIUBA
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


bool Dato::agregar(const Dato & d,unsigned int posicion)
{
	//si el offset (corrimiento) supera el tamano de los dato => false
	if (posicion > this->dato.str().length())
		return false;
	else
	{
		//TODO revisar bien que solo serviria para char* o string
		this->dato.str().insert(posicion,d.toString());
		return true;
	}

}

void Dato::vaciar()
{
	this->dato.clear();
}

bool Dato::vacio()
{
	return this->dato.str().empty();//devuelve tipo bool
}

bool Dato::agregarAlFinal(const Dato & d)
{
	this->agregar(d, this->dato.str().length());
	return  true;
}

string Dato::toString() const
{
	return this->dato.str();
}


char* Dato::toCharPointer()
{
	return (char*) this->dato.str().c_str();
}


string Dato::getDatos()
{
	return this->dato.str();
}

void Dato::setDatos(stringstream dato)
{
	this->vaciar();
    this->dato << dato;
}

void Dato::setDatos(char* dato)
{
    this->dato.str() = (string)dato;
}

long int Dato::getSize()
{
	return this->dato.str().length();
}

Dato::~Dato() {
	// TODO Auto-generated destructor stub
}
