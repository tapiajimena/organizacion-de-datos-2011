#include "NodoHojaArbol.h"

NodoHojaArbol::NodoHojaArbol() {
	this->tipoNodo = 'H';

}

NodoHojaArbol::NodoHojaArbol(list<uint32_t> idLibros, int idSiguienteHoja)
{
}

int NodoHojaArbol::insertar(string clave)
{
	//this->setClave(clave);
	return OVERFLOWDED;
}


void NodoHojaArbol::partir(NodoArbol* hermano, int sizeBloque, string clavePromovida, int idNodoPromovido)
{
	return;
}

int NodoHojaArbol::eliminar(Dato *dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int nodosLibres)
{
	return 0;

}

list<DatoElementoNodo*> NodoHojaArbol::getElementos() const
{
    return elementos;
}

void NodoHojaArbol::setElementos(list<DatoElementoNodo*> elementos)
{
    this->elementos = elementos;
}



int NodoHojaArbol::remover(Dato* dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int cantidadNodosLibres)
{
	return 0;
}


bool NodoHojaArbol::isOverflowded(int blockSize){
	cout<<" redefinido";
	return true;
}

bool NodoHojaArbol::isUnderflowded(int blockSize){
	cout<<" redefinido";
	return true;
}


Dato *NodoHojaArbol::buscar(Dato *dato)
{
}

bool NodoHojaArbol::agregarElemento(DatoElementoNodo* elemento)
{
	this->elementos.push_back(elemento);
}

int NodoHojaArbol::modificar(Dato *dato)
{
}

char NodoHojaArbol::getTipoNodo() const
{
	return this->tipoNodo;
}

void NodoHojaArbol::setTipoNodo(char tipoNodo)
{
	this->tipoNodo = tipoNodo;
}

void NodoHojaArbol::setId(int id)
{
	this->id  = id;
}

int NodoHojaArbol::getId() const
{
	return this->id;
}




uint32_t NodoHojaArbol::getIdSiguienteHoja() const
{
    return idSiguienteHoja;
}


void NodoHojaArbol::setIdSiguienteHoja(uint32_t idSiguienteHoja)
{
    this->idSiguienteHoja = idSiguienteHoja;
}

int NodoHojaArbol::getNivel() const
{
    return nivel;
}

void NodoHojaArbol::setNivel(int nivel)
{
    this->nivel = nivel;
}



NodoHojaArbol::~NodoHojaArbol()
{
}
