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

int NodoInternoArbol::remover(Dato* dato, uint32_t offset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter)
{

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


bool NodoInternoArbol::isOverflowded(int blockSize){
	cout<<" redefinido";
	return true;
}

bool NodoInternoArbol::isUnderflowded(int blockSize){
	cout<<" redefinido";
	return true;
}


NodoInternoArbol::~NodoInternoArbol() {
	// TODO Auto-generated destructor stub
}
