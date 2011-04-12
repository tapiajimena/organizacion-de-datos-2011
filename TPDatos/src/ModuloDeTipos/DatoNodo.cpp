/*
 * DatoNodo.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "DatoNodo.h"

DatoNodo::DatoNodo() {
	// TODO Auto-generated constructor stub

}

DatoNodo::DatoNodo(NodoInternoArbol* nodo){

	this->cantidad_hijos = nodo->getHijos().size();
	this->hijos = nodo->getHijos();

	const list<string> claves = nodo->getClaves();
	for (list<string>::const_iterator ci = claves.begin(); ci != claves.end(); ++ci)
	{
		this->claves += *ci+"|";
	}

	//size()-1 es para no guardar el último separador
	this->size_claves = claves.size()-1;

	this->dato.write(reinterpret_cast<char *>(&this->offset_continuacion), sizeof(this->offset_continuacion));
	this->dato.write(reinterpret_cast<char *>(&this->cantidad_hijos), sizeof(this->cantidad_hijos));
	for(list<int>::const_iterator it = hijos.begin(); it!=hijos.end(); ++it)
	{
		this->dato.write(reinterpret_cast<const char *>(&(*it)),sizeof(*it));
	}
	this->dato.write(reinterpret_cast<char *>(&this->size_claves), sizeof(this->size_claves));
	this->dato.write(reinterpret_cast<char *>(&this->claves), sizeof(this->claves));

}


DatoNodo::~DatoNodo() {
	// TODO Auto-generated destructor stub
}
