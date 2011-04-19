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

DatoNodo::DatoNodo(const NodoInternoArbol* nodo){

	this->cantidad_hijos = nodo->getHijos()->size();
	this->hijos = nodo->getHijos();

	list<string>* claves = nodo->getClaves();
	for (list<string>::const_iterator ci = claves->begin(); ci != claves->end(); ++ci)
	{
		this->claves += *ci+"|";
	}

	//size()-1 es para no guardar el último separador
	this->size_claves = this->claves.size()-1;

	this->dato.write(reinterpret_cast<char *>(&this->offset_continuacion), sizeof(this->offset_continuacion));
	this->dato.write(reinterpret_cast<char *>(&this->cantidad_hijos), sizeof(this->cantidad_hijos));
	for(list<int>::const_iterator it = hijos->begin(); it!=hijos->end(); ++it)
	{
		this->dato.write(reinterpret_cast<const char *>(&(*it)),sizeof(*it));
	}
	this->dato.write(reinterpret_cast<char *>(&this->size_claves), sizeof(this->size_claves));
	this->dato.write(reinterpret_cast<char *>(&this->claves), sizeof(this->claves));

}

DatoNodo::DatoNodo(const NodoHojaArbol* nodo)
{
	/*
	 * <IdNodo><TipoNodo><CantidadLibros><Libro1>....<LibroN><SiguienteHoja>
	 */
	cantidad_libros = nodo->getIdLibros()->size();

	this->dato.write(reinterpret_cast<char *>(nodo->getId()), sizeof(nodo->getId()));//idNodo
	this->dato.write(reinterpret_cast<char *>(nodo->getTipoNodo()), sizeof(nodo->getTipoNodo()));//tipoNodo
	this->dato.write(reinterpret_cast<char *>(&cantidad_libros), sizeof(cantidad_libros));//cantidadLibros

	idLibros = nodo->getIdLibros();
	for (list<uint32_t>::const_iterator ci = idLibros->begin(); ci != idLibros->end(); ++ci)
	{
		this->dato.write(reinterpret_cast<char *>(*ci), sizeof(*ci));//cantidadLibros
	}
}


DatoNodo::~DatoNodo() {
	// TODO Auto-generated destructor stub
}
