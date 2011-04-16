/*
 * DatoControlLibro.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "DatoControlLibro.h"

DatoControlLibro::DatoControlLibro() {
	// TODO Auto-generated constructor stub
}

DatoControlLibro::DatoControlLibro(DatoControlLibro* d) {
	this->espacioLibre = d->espacioLibre;
	this->id_Libro = d->id_Libro;
	this->indexado = d->indexado;
	this->offset = d->offset;
}

DatoControlLibro::DatoControlLibro(uint32_t id_Libro, uint32_t espacioLibre,
		list<char>* indexado, uint32_t offset) {
	this->espacioLibre = espacioLibre;
	this->id_Libro = id_Libro;
	this->indexado = indexado;
	this->offset = offset;
	Logger::log("datoControlLibro", "DatoControlLibro",
			"Se crea un nuevo dato de control libro.");
}

uint32_t DatoControlLibro::getEspacioLibre() const {
	return espacioLibre;
}

uint32_t DatoControlLibro::getId_Libro() const {
	return id_Libro;
}

list<char> * DatoControlLibro::getIndexado() const {
	return indexado;
}

uint32_t DatoControlLibro::getOffset() const {
	return offset;
}

void DatoControlLibro::setEspacioLibre(uint32_t espacioLibre) {
	this->espacioLibre = espacioLibre;
}

void DatoControlLibro::setId_Libro(uint32_t id_Libro) {
	this->id_Libro = id_Libro;
}

void DatoControlLibro::setIndexado(list<char> *indexado) {
	this->indexado = indexado;
}

void DatoControlLibro::setOffset(uint32_t offset) {
	this->offset = offset;
}

DatoControlLibro::~DatoControlLibro() {
	// TODO Auto-generated destructor stub
}
