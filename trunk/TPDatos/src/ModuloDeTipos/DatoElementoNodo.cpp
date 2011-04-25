/*
 * NodoHojaArbol.h
 *
 *    Autor   	 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 *	Clase utilizada para la representacion de los nodos hoja del arbol.
 *
 */

#include "DatoElementoNodo.h"

DatoElementoNodo::DatoElementoNodo() {
	this->clave = "";
}

void DatoElementoNodo::serializar(iostream* stream) {

	int tamanioClave = clave.length();
	int cantidadLibros = idLibros.size();
	uint32_t idLibro = 0;

	stream->write(reinterpret_cast<char *> (&tamanioClave),sizeof(tamanioClave));
	stream->write(clave.c_str(), tamanioClave);
	stream->write(reinterpret_cast<char *> (&cantidadLibros),sizeof(cantidadLibros));


	list<uint32_t>::iterator it;
	for (it = idLibros.begin(); it	!= idLibros.end(); ++it) {
		idLibro = *it;
		stream->write(reinterpret_cast<char *> (&idLibro), sizeof(idLibro));
	}
}

void DatoElementoNodo::hidratar(iostream* stream) {

	int tamanioClave = 0;
	int cantidadLibros = 0;
	uint32_t aux = 0;
	char* buffer;

	stream->read(reinterpret_cast<char *> (&tamanioClave),sizeof(tamanioClave));
	buffer = new char [tamanioClave];
	stream->read(buffer, tamanioClave);
	stream->read(reinterpret_cast<char *> (&cantidadLibros),sizeof(cantidadLibros));

	clave.append( buffer,tamanioClave);

	for (int i = 0; i < cantidadLibros; i++) {
		stream->read(reinterpret_cast<char *> (&aux), sizeof(aux));
		idLibros.push_back(aux);
	}

	delete[] buffer;
}

void DatoElementoNodo::setClave(string clave) {
	this->clave = clave;
}


int DatoElementoNodo::comparar(DatoElementoNodo* ele)
{
	return strcmp(this->clave.c_str(), ele->getClave().c_str());
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

}
