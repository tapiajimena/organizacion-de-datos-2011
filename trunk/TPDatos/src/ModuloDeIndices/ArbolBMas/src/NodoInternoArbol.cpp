#include "NodoInternoArbol.h"

NodoInternoArbol::NodoInternoArbol() {
	// TODO Auto-generated constructor stub
}

list<string> NodoInternoArbol::getClaves() const {
	return this->claves;
}

list<int> NodoInternoArbol::getHijos() const {
	return this->hijos;
}

void NodoInternoArbol::setClaves(list<string> claves) {
	this->claves = claves;
}

void NodoInternoArbol::setHijos(list<int> hijos) {
	this->hijos = hijos;
}

bool NodoInternoArbol::isOverflowded(int blockSize){
	return true;
}


NodoInternoArbol::~NodoInternoArbol() {
	// TODO Auto-generated destructor stub
}
