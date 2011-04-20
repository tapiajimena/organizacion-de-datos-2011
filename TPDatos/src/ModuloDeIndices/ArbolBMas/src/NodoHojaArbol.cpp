#include "NodoHojaArbol.h"

NodoHojaArbol::NodoHojaArbol() {
	this->idLibros = new list<uint32_t>();
	this->tipoNodo = 'H';

}

NodoHojaArbol::NodoHojaArbol(list<uint32_t> idLibros, int idSiguienteHoja)
{
}

int NodoHojaArbol::insertar(Dato* dato)
{
	return 0;
}


void NodoHojaArbol::partir(NodoArbol* hermano, int sizeBloque, string clavePromovida, int idNodoPromovido)
{
	return;
}

int NodoHojaArbol::eliminar(Dato* dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int cantidadNodosLibres)
{
	return 0;

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



list<uint32_t>* NodoHojaArbol::getIdLibros() const
{
    return idLibros;
}

uint32_t NodoHojaArbol::getIdSiguienteHoja() const
{
    return idSiguienteHoja;
}

void NodoHojaArbol::setIdLibros(list<uint32_t>* idLibros)
{
    this->idLibros = idLibros;
}

void NodoHojaArbol::setIdSiguienteHoja(uint32_t idSiguienteHoja)
{
    this->idSiguienteHoja = idSiguienteHoja;
}

NodoHojaArbol::~NodoHojaArbol() {

	// TODO ELIMINAR LO QUE ESTA DENTRO DE LA LISTA
	delete (this->idLibros);
}
