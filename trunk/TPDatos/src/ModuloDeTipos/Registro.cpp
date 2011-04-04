#include "Registro.h"

Registro::Registro(const Datos& dato) {
	this->dato = dato;
	this->eliminado = false;
}

Registro::~Registro() {

}

void Registro::setDato(const Datos& dato) {
	this->dato = dato;
}

Datos Registro::getDato() const {
	return this->dato;
}

void Registro::setId(const uint32_t & id) {
	this->id = id;
}

uint32_t Registro::getId() const {
	return this->id;
}

void Registro::eliminar() {

	this->eliminado = true;
}

