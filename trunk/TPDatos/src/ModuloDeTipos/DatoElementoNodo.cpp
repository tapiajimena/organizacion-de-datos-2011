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

DatoElementoNodo::DatoElementoNodo(string clave) {
	this->clave = clave;
}

DatoElementoNodo::DatoElementoNodo(string clave, uint32_t idLibro) {
	this->clave = clave;
	this->idLibros.push_back(idLibro);
}

DatoElementoNodo::DatoElementoNodo(string clave, list<uint32_t> idLibros) {
	this->clave = clave;
	this->idLibros = idLibros;
}

void DatoElementoNodo::serializar(iostream* stream) {

	int tamanioClave = clave.length();
	int cantidadLibros = idLibros.size();
	uint32_t idLibro = 0;

	stream->write(reinterpret_cast<char *> (&tamanioClave),
			sizeof(tamanioClave));
	stream->write(clave.c_str(), tamanioClave);
	stream->write(reinterpret_cast<char *> (&cantidadLibros),
			sizeof(cantidadLibros));

	list<uint32_t>::iterator it;
	for (it = idLibros.begin(); it != idLibros.end(); ++it) {
		idLibro = *it;
		stream->write(reinterpret_cast<char *> (&idLibro), sizeof(idLibro));
	}
}

void DatoElementoNodo::hidratar(iostream* stream) {

	int tamanioClave = 0;
	int cantidadLibros = 0;
	uint32_t aux = 0;
	char* buffer;

	stream->read(reinterpret_cast<char *> (&tamanioClave), sizeof(tamanioClave));
	buffer = new char[tamanioClave];
	stream->read(buffer, tamanioClave);
	stream->read(reinterpret_cast<char *> (&cantidadLibros),
			sizeof(cantidadLibros));

	clave.append(buffer, tamanioClave);

	for (int i = 0; i < cantidadLibros; i++) {
		stream->read(reinterpret_cast<char *> (&aux), sizeof(aux));
		idLibros.push_back(aux);
	}

	delete[] buffer;
}

DatoElementoNodo* DatoElementoNodo::clonar() {
	DatoElementoNodo* aux = new DatoElementoNodo(this->clave, this->idLibros);
	//stringstream ss(ios_base::in | ios_base::out);
	/*

	 ss.write(this->data,this->dataSize);
	 aux->edit(this->clave,&ss);
	 */
	return aux;
}

void DatoElementoNodo::editar(string clave, iostream* ios) {
	//TODO terminar edicion
	/*
	 this->clave = clave;
	 this->dato = NULL;



	 this->dataSize = 0;
	 while(!ios->eof())
	 {
	 this->data = (char*)realloc(this->data,this->dataSize + 0x000f);
	 ios->read(this->data + this->dataSize, 0x000f);
	 this->dataSize += ios->gcount();
	 }
	 */
}

int DatoElementoNodo::getSize() {
	/*
	 * cuanto ocupa en disco
	 * cuando està persistido
	 */

	int size = 0;
	size += sizeof(int);//tamanioClave
	size += this->clave.length();
	size += sizeof(int);//cantidadLibros
	size += (sizeof(uint32_t) * (this->idLibros.size()));

	return size;
}

void DatoElementoNodo::setClave(string clave) {
	this->clave = clave;
}

int DatoElementoNodo::comparar(DatoElementoNodo* ele) {
	string aux = ele->getClave();
	return strcmp(this->clave.c_str(), aux.c_str());
}

int DatoElementoNodo::comparar(string clave) {
	return strcmp(this->clave.c_str(), clave.c_str());
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
	this->idLibros.sort();
	this->idLibros.unique();
}

void DatoElementoNodo::quitarLibro(uint32_t idLibro) {

	this->idLibros.remove(idLibro);

	//	this->it = this->idLibros.begin();
	//	while(this->it!=this->idLibros.end())
	//	{
	//		if((*it) == idLibro)
	//		{
	//			this->idLibros.erase(it);
	//		}
	//		++it;
	//	}

}

void DatoElementoNodo::toString(iostream* ios, int rootLevel) {
	string tabs = setTabs(rootLevel + 1);
	this->it = this->idLibros.begin();

	(*ios) << tabs << "|----- [elemento" << " KEY= [" << getClave() << "] LIBROS= [";
	while(this->it!=this->idLibros.end())
	{
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

DatoElementoNodo::~DatoElementoNodo() {

}
