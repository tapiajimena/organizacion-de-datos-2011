/*
 * DatoTriada.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "DatoTriada.h"

DatoTriada::DatoTriada() {
	// TODO Auto-generated constructor stub
}

DatoTriada::DatoTriada(DatoTriada* d) {
	this->idLibro = d->idLibro;
	this->idTermino = d->idTermino;
	this->posicion = d->posicion;
}

uint32_t DatoTriada::getId() const {
	return id;
}

uint32_t DatoTriada::getIdLibro() const {
	return idLibro;
}

uint32_t DatoTriada::getIdTermino() const {
	return idTermino;
}

long DatoTriada::getPosicion() const {
	return posicion;
}

void DatoTriada::setId(uint32_t id) {
	this->id = id;
}

void DatoTriada::setIdLibro(uint32_t idLibro) {
	this->idLibro = idLibro;
}

void DatoTriada::setIdTermino(uint32_t idTermino) {
	this->idTermino = idTermino;
}

void DatoTriada::setPosicion(long posicion) {
	this->posicion = posicion;
}

DatoTriada::~DatoTriada() {
	// TODO Auto-generated destructor stub
}
