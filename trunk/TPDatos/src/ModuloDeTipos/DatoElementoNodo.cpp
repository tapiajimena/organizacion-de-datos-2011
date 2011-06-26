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
	this->cantidadLetrasClaveAnterior = 0;
	this->cantidadLetrasClaveActual = 0;
}

DatoElementoNodo::DatoElementoNodo(string clave) {
	this->clave = clave;
	this->cantidadLetrasClaveAnterior = 0;
	this->cantidadLetrasClaveActual = clave.size();
}

DatoElementoNodo::DatoElementoNodo(string clave, uint32_t idLibro) {
	this->clave = clave;
	this->idLibros.push_back(idLibro);
	this->cantidadLetrasClaveAnterior = 0;
	this->cantidadLetrasClaveActual = clave.size();
}

DatoElementoNodo::DatoElementoNodo(string clave, list<uint32_t> idLibros) {
	this->clave = clave;
	this->idLibros = idLibros;
	this->cantidadLetrasClaveAnterior = 0;
	this->cantidadLetrasClaveActual = clave.size();
}

void DatoElementoNodo::serializar(iostream* stream) {

	char* cstrClave = new char[this->cantidadLetrasClaveActual + 1];
	strcpy(cstrClave, this->clave.c_str());
	int cantidadLibros = idLibros.size();
	uint32_t idLibro = 0;

	stream->write(
			reinterpret_cast<char *> (&(this->cantidadLetrasClaveAnterior)),
			sizeof(this->cantidadLetrasClaveAnterior));
	stream->write(
			reinterpret_cast<char *> (&(this->cantidadLetrasClaveActual)),
			sizeof(this->cantidadLetrasClaveActual));
	stream->write(cstrClave, (this->cantidadLetrasClaveActual));
	stream->write(reinterpret_cast<char *> (&cantidadLibros),
			sizeof(cantidadLibros));

	list<uint32_t>::iterator it;
	for (it = idLibros.begin(); it != idLibros.end(); ++it) {
		idLibro = *it;
		stream->write(reinterpret_cast<char *> (&idLibro), sizeof(idLibro));
	}

	delete[] cstrClave;
}

void DatoElementoNodo::hidratar(iostream* stream) {

	int cantidadLibros = 0;
	uint32_t aux = 0;
	char* buffer;

	stream->read(
			reinterpret_cast<char *> (&(this->cantidadLetrasClaveAnterior)),
			sizeof(this->cantidadLetrasClaveAnterior));
	stream->read(reinterpret_cast<char *> (&(this->cantidadLetrasClaveActual)),
			sizeof(this->cantidadLetrasClaveActual));

	buffer = new char[this->cantidadLetrasClaveActual];

	stream->read(buffer, this->cantidadLetrasClaveActual);
	stream->read(reinterpret_cast<char *> (&cantidadLibros),
			sizeof(cantidadLibros));

	this->clave.append(buffer, this->cantidadLetrasClaveActual);

	for (int i = 0; i < cantidadLibros; i++) {
		stream->read(reinterpret_cast<char *> (&aux), sizeof(aux));
		idLibros.push_back(aux);
	}

	delete[] buffer;
}

DatoElementoNodo* DatoElementoNodo::clonar() {
	DatoElementoNodo* aux = NULL;
	if (this != NULL)
		aux = new DatoElementoNodo(this->clave, this->idLibros);
	else
		Logger::log("DatoElementoNodo","clonar",
				"El dato que fue buscado no se encuentra en el arbol");
	return aux;
}

int DatoElementoNodo::getSize() {
	/*
	 * cuanto ocupa en disco
	 * cuando està persistido
	 */

	int size = 0;
	size += sizeof(this->cantidadLetrasClaveAnterior);
	size += sizeof(this->cantidadLetrasClaveActual);
	size += this->cantidadLetrasClaveActual;
	size += sizeof(int);//cantidadLibros
	size += (sizeof(uint32_t) * (this->idLibros.size()));

	return size;
}

void DatoElementoNodo::setClave(string clave) {
	this->clave = clave;
	this->cantidadLetrasClaveActual = clave.size();
}

int DatoElementoNodo::comparar(DatoElementoNodo* ele) {
	int resultado = 0;
	char* cstrThisClave;
	char* cstrThatClave;

	cstrThisClave = new char[this->clave.size() + 1];
	strcpy(cstrThisClave, this->clave.c_str());

	cstrThatClave = new char[ele->getClave().size() + 1];
	strcpy(cstrThatClave, ele->getClave().c_str());

	resultado = strcmp(cstrThisClave, cstrThatClave);

	delete[] cstrThisClave;
	delete[] cstrThatClave;

	return resultado;
}

string DatoElementoNodo::getClave() {
	return this->clave;
}
list<uint32_t> DatoElementoNodo::getLibros() {
	return this->idLibros;
}

int DatoElementoNodo::getCantidadLibros() {
	return this->idLibros.size();
}

void DatoElementoNodo::agregarLibro(uint32_t idLibro) {
	this->idLibros.push_back(idLibro);

	/*
	 * en caso de que se inserte repetido
	 */
	this->idLibros.sort();
	this->idLibros.unique();
}

void DatoElementoNodo::quitarLibro(uint32_t idLibro) {

	this->idLibros.remove(idLibro);
}

void DatoElementoNodo::toString(iostream* ios, int rootLevel) {
	string tabs = setTabs(rootLevel + 1);
	this->it = this->idLibros.begin();

	(*ios) << tabs << "|----- [elemento" << " KEY= [("
			<< this->cantidadLetrasClaveAnterior << ")("
			<< this->cantidadLetrasClaveActual << ")" << getClave()
			<< "] LIBROS= [";
	while (this->it != this->idLibros.end()) {
		(*ios) << "(" << *it << ")";
		++it;
	}
	(*ios) << "] sizeElemento=[" << this->getSize() << "] cantidadLibros=["
			<< this->idLibros.size() << "] ]" << endl;

}

string DatoElementoNodo::setTabs(int level) {
	string tabs = "";
	for (int i = 0; i < level; i++) {
		tabs += "| \t";
	}
	return tabs;
}

short int DatoElementoNodo::getCantidadLetrasClaveAnterior() {
	return this->cantidadLetrasClaveAnterior;
}

short int DatoElementoNodo::getCantidadLetrasClaveActual() {
	return this->cantidadLetrasClaveActual;
}

void DatoElementoNodo::setCantidadLetrasClaveAnterior(short int cant) {
	this->cantidadLetrasClaveAnterior = cant;
}

void DatoElementoNodo::setCantidadLetrasClaveActual(short int cant) {
	this->cantidadLetrasClaveActual = cant;
}

DatoElementoNodo::~DatoElementoNodo() {

}
