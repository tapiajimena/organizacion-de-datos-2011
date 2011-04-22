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

void NodoHojaArbol::serializar(){
	/*
	 * Se serializa en el siguiente orden
	 * <IdNodo><Nivel><TipoNodo><CantidadDatoElementoNodo><TamanioDatoElementoNodo><DatoElementoNodo>...<TamanioDatoElementoNodo><DatoElementoNodo><SiguienteHoja>
	 */
	int cantidadElementos 	= this->elementos.size();
	string mensaje = "Se serializa la hoja con ";
	mensaje +=ServiceClass::toString(cantidadElementos);
	mensaje +=" elementos.";
	Logger::log("NodoHojaArbol", "serializar", mensaje);
	long int tamanioElementoNodo = 0;

	this->dato.write(reinterpret_cast<char *>(&(this->id)), sizeof(this->id));//idNodo
	this->dato.write(reinterpret_cast<char *>(&(this->nivel)), sizeof(this->nivel));//nivel
	this->dato.write(reinterpret_cast<char *>(&(this->tipoNodo)), sizeof(this->tipoNodo));//tipoNodo
	this->dato.write(reinterpret_cast<char *>(&cantidadElementos), sizeof(cantidadElementos));//cantidadElementos

	DatoElementoNodo* elemento;
	for (list<DatoElementoNodo*>::const_iterator ci = this->elementos.begin(); ci != this->elementos.end(); ++ci)
	{
		elemento = *ci;
		mensaje = "Se va a serializar el elemento de clave: ";
		mensaje += (*ci)->getClave();
		Logger::log("NodoHojaArbol", "serializar", mensaje);
		elemento->serializar();
		tamanioElementoNodo = elemento->getSize();
		this->dato.write(reinterpret_cast<char *>(&tamanioElementoNodo), sizeof(tamanioElementoNodo));//tamanioElementoNodo
		this->dato.write(elemento->getDato().c_str(),tamanioElementoNodo);
	}


}

void NodoHojaArbol::hidratar(string nodoHojaArbol){
	stringstream hoja(nodoHojaArbol);

	int cantidadElementos = 0;
	long int tamanioElementoNodo = 0;

	hoja.seekp(0, ios::beg);
	hoja.read(reinterpret_cast<char *>(&(this->id)), sizeof(this->id));
	hoja.read(reinterpret_cast<char *>(&(this->nivel)), sizeof(this->nivel));
	hoja.read(reinterpret_cast<char *>(&(this->tipoNodo)), sizeof(this->tipoNodo));
	hoja.read(reinterpret_cast<char *>(&(cantidadElementos)), sizeof(cantidadElementos));

	DatoElementoNodo* elemento;
	char* elementoAux;
	string aux;
	for (int i = 0; i<cantidadElementos; i++)
	{
		hoja.read(reinterpret_cast<char *>(&tamanioElementoNodo),sizeof(tamanioElementoNodo));
		hoja.read(elementoAux,tamanioElementoNodo);
		elemento = new DatoElementoNodo();
		aux=elementoAux;
		elemento->hidratar(aux.substr(0,tamanioElementoNodo));
		elementos.push_back(elemento);
	}
}


NodoHojaArbol::~NodoHojaArbol()
{
}
