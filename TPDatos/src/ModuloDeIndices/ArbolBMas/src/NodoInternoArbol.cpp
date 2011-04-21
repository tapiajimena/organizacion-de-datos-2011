#include "NodoInternoArbol.h"

NodoInternoArbol::NodoInternoArbol() {
	// TODO Auto-generated constructor stub
}


int NodoInternoArbol::insertar(Dato* dato)
{

}

void NodoInternoArbol::partir(NodoArbol* hermano, int sizeBloque, string clavePromovida, int idNodoPromovido)
{

}

int NodoInternoArbol::eliminar(Dato* dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int cantidadNodosLibres)
{

}


bool NodoInternoArbol::isOverflowded(int blockSize){
	cout<<" redefinido";
	return true;
}

bool NodoInternoArbol::isUnderflowded(int blockSize){
	cout<<" redefinido";
	return true;
}


void NodoInternoArbol::setClaves(list<string>* claves) {
	this->claves = claves;
}

void NodoInternoArbol::setHijos(list<int>* hijos) {
	this->hijos = hijos;
}

list<string>* NodoInternoArbol::getClaves() const{
	return this->claves;
}

list<int>* NodoInternoArbol::getHijos() const{
	return hijos;
}

char NodoInternoArbol::getTipoNodo() const
{
	return this->tipoNodo;
}

void NodoInternoArbol::setTipoNodo(char tipoNodo)
{
	this->tipoNodo = tipoNodo;
}

void NodoInternoArbol::setId(int id)
{
	this->id  = id;
}

int NodoInternoArbol::getId() const
{
	return this->id;
}

int NodoInternoArbol::getNivel() const
{
    return nivel;
}

void NodoInternoArbol::setNivel(int nivel)
{
    this->nivel = nivel;
}


NodoInternoArbol::~NodoInternoArbol() {
	// TODO Auto-generated destructor stub
}
