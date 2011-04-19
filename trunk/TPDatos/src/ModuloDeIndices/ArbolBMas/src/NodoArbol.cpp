#include "NodoArbol.h"

NodoArbol::NodoArbol() {
	// TODO Auto-generated constructor stub

}


int NodoArbol::getId() const {
	return id;
}

void NodoArbol::setId(int id) {
	this->id = id;
}


char NodoArbol::getTipoNodo() const
{
    return tipoNodo;
}

void NodoArbol::setTipoNodo(char tipoNodo)
{
    this->tipoNodo = tipoNodo;
}

NodoArbol::~NodoArbol()
{
	// TODO Auto-generated destructor stub
}
