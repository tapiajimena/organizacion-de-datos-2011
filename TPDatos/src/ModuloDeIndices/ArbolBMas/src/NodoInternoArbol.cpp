#include "NodoInternoArbol.h"

NodoInternoArbol::NodoInternoArbol() {

}

int NodoInternoArbol::insertar(string clave)
{

}

void NodoInternoArbol::partir(NodoArbol* hermano, int sizeBloque, string clavePromovida, int idNodoPromovido)
{

}

int NodoInternoArbol::eliminar(Dato* dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int cantidadNodosLibres)
{

}


void NodoInternoArbol::agregarClaveHijo(string clave, int idHijo)
{
	string claveActual;
	list<int>::iterator itHijos 	= this->hijos.begin();
	list<string>::iterator itClaves;

	for (itClaves =claves.begin(); itClaves!=claves.end(); ++itClaves)
	{
		claveActual = (string) *itClaves;
		if (strcmp(clave.c_str(),claveActual.c_str()))//TODO ver que devuelve si 1 o -1
			break;

		itHijos++;
	}

	itHijos++;
	hijos.insert(itHijos, idHijo);
	claves.insert(itClaves, clave);
}


uint32_t NodoInternoArbol::buscarClave(string clave)
{
	string claveActual;
	uint32_t rdo = 0;
	list<int>::iterator itHijos 	= hijos.begin();
	list<string>::iterator itClaves;

	if (!claves.empty())
	{
		for (itClaves =claves.begin(); itClaves!=claves.end(); ++itClaves)
		{
			if (strcmp(clave.c_str(),claveActual.c_str())== 0)
				claveActual = (string) *itClaves;
			itHijos++;
		}
	}
	rdo = (uint32_t)claveActual.length();
	return rdo;
}

bool NodoInternoArbol::isOverflowded(int blockSize)
{
	cout<<" redefinido";
	return true;
}

bool NodoInternoArbol::isUnderflowded(int blockSize)
{
	cout<<" redefinido";
	return true;
}


void NodoInternoArbol::setClaves(list<string> claves) {
	this->claves = claves;
}

void NodoInternoArbol::setHijos(list<int> hijos) {
	this->hijos = hijos;
}

list<string> NodoInternoArbol::getClaves() const{
	return this->claves;
}

list<int> NodoInternoArbol::getHijos() const{
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
