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
	this->setDatoNodo(nodo);
}

void DatoNodo::setDatoNodo(const NodoInternoArbol* nodo)
{

}

void DatoNodo::setDatoNodo(const NodoHojaArbol* nodo)
{
	/*
	 * Se serializa en el siguiente orden:
	 * <IdNodo><Nivel><TipoNodo><CantidadLibros><Libro1>....<LibroN><SiguienteHoja>
	 */
	int id 			= nodo->getId();
	int nivel		= nodo->getNivel();
	char tipo		= nodo->getTipoNodo();

	cantidad_libros = nodo->getIdLibros()->size();


	this->dato.write(reinterpret_cast<char *>(&id), sizeof(id));//idNodo
	this->dato.write(reinterpret_cast<char *>(&nivel), sizeof(nivel));//nivel
	this->dato.write(reinterpret_cast<char *>(&tipo), sizeof(tipo));//tipoNodo
	this->dato.write(reinterpret_cast<char *>(&cantidad_libros), sizeof(cantidad_libros));//cantidadLibros

	list<uint32_t>* aux = nodo->getIdLibros();
	for (list<uint32_t>::const_iterator ci = aux->begin(); ci != aux->end(); ++ci)
	{
		uint32_t idLibro = *ci;
		this->dato.write(reinterpret_cast<char *>(&idLibro), sizeof(idLibro));//cantidadLibros
	}
}


void  DatoNodo::hidratar(NodoHojaArbol* nodoHoja)
{
	/*
	 * Se hidrata en el siguiente orden:
	 * <IdNodo><Nivel><TipoNodo><CantidadLibros><Libro1>....<LibroN><SiguienteHoja>
	 */
	int		idNodo, nivel, cantidadLibros;
	char	tipoNodo;
	uint32_t idLibro;

	this->dato.seekp(0,ios::beg);
	this->dato.read(reinterpret_cast<char *>(&idNodo), sizeof(idNodo));
	this->dato.read(reinterpret_cast<char *>(&nivel), sizeof(nivel));
	this->dato.read(reinterpret_cast<char *>(&tipoNodo), sizeof(tipoNodo));
	this->dato.read(reinterpret_cast<char *>(&cantidadLibros), sizeof(cantidadLibros));

	nodoHoja->setId(idNodo);
	nodoHoja->setTipoNodo(tipoNodo);

	for (int i = 0; i < cantidadLibros; ++i)
	{
		this->dato.read(reinterpret_cast<char *>(&idLibro), sizeof(idLibro));
		nodoHoja->agregarLibro(idLibro);
	}
}

void  DatoNodo::hidratar(NodoInternoArbol* nodoInterno)
{

}

long int DatoNodo::getSize()
{
	return Dato::getSize();
}

DatoNodo::~DatoNodo()
{
	// TODO Auto-generated destructor stub
}
