#include "NodoHojaArbol.h"

NodoHojaArbol::NodoHojaArbol() {
	// TODO Auto-generated constructor stub

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
}


void NodoHojaArbol::setTipoNodo(char tipoNodo)
{
}

void NodoHojaArbol::setId(int id)
{
}

int NodoHojaArbol::getId() const
{
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
	// TODO Auto-generated destructor stub
}
