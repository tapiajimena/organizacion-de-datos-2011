#include "NodoInternoArbol.h"

NodoInternoArbol::NodoInternoArbol() {
	// TODO Auto-generated constructor stub

}

list<int> NodoInternoArbol::getClaves() const {
	return claves;
}

list<int> NodoInternoArbol::getHijos() const {
	return hijos;
}

void NodoInternoArbol::setClaves(list<int> claves) {
	this->claves = claves;
}

void NodoInternoArbol::setHijos(list<int> hijos) {
	this->hijos = hijos;
}

NodoInternoArbol::~NodoInternoArbol() {
	// TODO Auto-generated destructor stub
}
