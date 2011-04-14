#include "ArbolBMas.h"

ArbolBMas::ArbolBMas() {
	// TODO Auto-generated constructor stub
	setMinCantidadClaves();
	setMaxCantidadHijos();
	//setOrden();
}

int ArbolBMas::getMaxCantidadHijos() const {
	return maxCantidadHijos;
}

int ArbolBMas::getMinCantidadClaves() const {
	NodoInternoArbol nI;
	int a =nI.getId();
	return minCantidadClaves;
}

int ArbolBMas::getOrden() const {
	return orden;
}

void ArbolBMas::setMaxCantidadHijos() {
	this->maxCantidadHijos = (this->orden + 1);
}

void ArbolBMas::setMinCantidadClaves() {
	this->minCantidadClaves = this->orden/2;
}

void ArbolBMas::setOrden(int orden) {
	this->orden = orden;
}

ArbolBMas::~ArbolBMas() {
	// TODO Auto-generated destructor stub
}
