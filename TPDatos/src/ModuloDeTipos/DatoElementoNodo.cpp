/*
 * DatoElementoNodo.cpp
 *
 *  Created on: 21/04/2011
 *      Author: paulo
 */

#include "DatoElementoNodo.h"

DatoElementoNodo::DatoElementoNodo() {
	// TODO Auto-generated constructor stub

}

void DatoElementoNodo::serializar() {
	int tamanioClave = clave.length();
	int cantidadLibros = idLibros.size();

	this->dato.write(reinterpret_cast<char *> (&tamanioClave),sizeof(tamanioClave));
	this->dato.write(clave.c_str(), tamanioClave);
	this->dato.write(reinterpret_cast<char *> (&cantidadLibros),sizeof(cantidadLibros));

	for (list<uint32_t>::const_iterator ci = idLibros.begin(); ci
			!= idLibros.end(); ++ci) {
		uint32_t idLibro = *ci;
		this->dato.write(reinterpret_cast<char *> (&idLibro), sizeof(idLibro));
	}
}

void DatoElementoNodo::hidratar(string dato) {
	stringstream datoElementoNodo(dato);
	int tamanioClave = 0;
	int cantidadLibros = 0;
	char* claveAux;

	datoElementoNodo.seekp(0, ios::beg);
	datoElementoNodo.read(reinterpret_cast<char *> (&tamanioClave),sizeof(tamanioClave));
	datoElementoNodo.read(claveAux, tamanioClave);
	datoElementoNodo.read(reinterpret_cast<char *> (&cantidadLibros),sizeof(cantidadLibros));

	clave = claveAux;
	clave = clave.substr(0,tamanioClave);

	for (int i = 0; i < cantidadLibros; i++) {
		uint32_t aux;
		datoElementoNodo.read(reinterpret_cast<char *> (&aux), sizeof(aux));
		idLibros.push_back(aux);
	}
}

void DatoElementoNodo::setClave(string clave) {
	this->clave = clave;
}

string DatoElementoNodo::getClave() {
	return this->clave;
}
list<uint32_t> DatoElementoNodo::getLibros() {
	return this->idLibros;
}
void DatoElementoNodo::agregarLibro(uint32_t idLibro) {
	this->idLibros.push_back(idLibro);
}

DatoElementoNodo::~DatoElementoNodo() {
	// TODO Auto-generated destructor stub
}
