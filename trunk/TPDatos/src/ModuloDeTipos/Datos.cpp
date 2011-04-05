/*
 * Datos.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "Datos.h"


Datos::Datos() {
	// TODO Auto-generated constructor stub

}


Datos:: Datos(char* d)
{
	this->datos = (string)d;
}

Datos::Datos(const Datos & d)
{
	this->datos = d.datos;

}

Datos::Datos(string s)
{
	this->datos = s;
}


bool Datos::agregar(const Datos & d,unsigned int posicion)
{
	//si el offset (corrimiento) supera el tamano de los datos => false
	if (posicion > this->datos.length())
		return false;
	else
	{
		this->datos.insert(posicion,d.toString());
		return true;
	}
}

void Datos::vaciar()
{
	this->datos.clear();
}

bool Datos::vacio()
{
	return this->datos.empty();//devuelve tipo bool
}

bool Datos::agregarAlFinal(const Datos & d)
{
	this->agregar(d, this->datos.length());
	return  true;
}

string Datos::toString() const{

	return this->datos;
}


char* Datos::toCharPointer()
{
	return (char*) this->datos.c_str();;
}



string Datos::getDatos()
{
	return this->datos;
}

void Datos::setDatos(string datos)
{
    this->datos = datos;
}


long int Datos::getSize()
{
	return this->datos.length();
}

Datos::~Datos() {
	// TODO Auto-generated destructor stub
}
