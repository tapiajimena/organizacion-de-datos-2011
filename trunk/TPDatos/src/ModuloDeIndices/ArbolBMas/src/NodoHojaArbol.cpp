#include "NodoHojaArbol.h"

NodoHojaArbol::NodoHojaArbol() {
	this->tipoNodo = 'H';
	this->idSiguienteHoja = 0;

}

NodoHojaArbol::NodoHojaArbol(list<uint32_t> idLibros, int idSiguienteHoja) {
}

int NodoHojaArbol::insertar(string clave) {
	//this->setClave(clave);
	return OVERFLOWDED;
}

void NodoHojaArbol::partir(NodoArbol* hermano, int sizeBloque,
		string clavePromovida, int idNodoPromovido) {
	return;
}

int NodoHojaArbol::eliminar(Dato *dato, uint32_t offset, fstream fs,
		unsigned int cantidadNodos, fstream arcLibros, unsigned int nodosLibres) {
	return 0;

}

list<DatoElementoNodo*> NodoHojaArbol::getElementos() const {
	return elementos;
}

void NodoHojaArbol::setElementos(list<DatoElementoNodo*> elementos) {
	this->elementos = elementos;
}

int NodoHojaArbol::remover(Dato* dato, uint32_t offset, fstream fs,
		unsigned int cantidadNodos, fstream arcLibros,
		unsigned int cantidadNodosLibres) {
	return 0;
}

bool NodoHojaArbol::isOverflowded(int blockSize) {
	cout << " redefinido";
	return true;
}

bool NodoHojaArbol::isUnderflowded(int blockSize) {
	cout << " redefinido";
	return true;
}

Dato *NodoHojaArbol::buscar(Dato *dato) {
}

bool NodoHojaArbol::agregarElemento(DatoElementoNodo* elemento) {
	this->elementos.push_back(elemento);
}

int NodoHojaArbol::modificar(Dato *dato) {
}

char NodoHojaArbol::getTipoNodo() const {
	return this->tipoNodo;
}

void NodoHojaArbol::setTipoNodo(char tipoNodo) {
	this->tipoNodo = tipoNodo;
}

void NodoHojaArbol::setId(int id) {
	this->id = id;
}

int NodoHojaArbol::getId() const {
	return this->id;
}

uint32_t NodoHojaArbol::getIdSiguienteHoja() const {
	return idSiguienteHoja;
}

void NodoHojaArbol::setIdSiguienteHoja(uint32_t idSiguienteHoja) {
	this->idSiguienteHoja = idSiguienteHoja;
}

int NodoHojaArbol::getNivel() const {
	return nivel;
}

void NodoHojaArbol::setNivel(int nivel) {
	this->nivel = nivel;
}

void NodoHojaArbol::serializar(iostream* stream) {
	/*
	 * Se serializa en el siguiente orden
	 * <IdNodo><Nivel><TipoNodo><CantidadDatoElementoNodo><DatoElementoNodo>...<DatoElementoNodo><SiguienteHoja>
	 */
	int cantidadElementos = this->elementos.size();

	string mensaje = "Se serializa la hoja con ";
	mensaje += ServiceClass::toString(cantidadElementos);
	mensaje += " elementos.";
	Logger::log("NodoHojaArbol", "serializar", mensaje);

	stream->write(reinterpret_cast<char *> (&(this->id)), sizeof(this->id));
	stream->write(reinterpret_cast<char *> (&(this->nivel)),sizeof(this->nivel));
	stream->write(reinterpret_cast<char *> (&(this->tipoNodo)),sizeof(this->tipoNodo));
	stream->write(reinterpret_cast<char *> (&cantidadElementos),sizeof(cantidadElementos));

	DatoElementoNodo* elemento;
	list<DatoElementoNodo*>::iterator it;
	for (it = this->elementos.begin(); it!= this->elementos.end(); ++it) {
		elemento = *it;

		mensaje = "Se va a serializar el elemento de clave: ";
		mensaje += (*it)->getClave();
		Logger::log("NodoHojaArbol", "serializar", mensaje);

		elemento->serializar(stream);
	}
	stream->write(reinterpret_cast<char *> (&(this->idSiguienteHoja)),sizeof(this->idSiguienteHoja));
}

void NodoHojaArbol::hidratar(iostream* stream) {

	int cantidadElementos = 0;

	stream->read(reinterpret_cast<char *> (&(this->id)),sizeof(this->id));
	stream->read(reinterpret_cast<char *> (&(this->nivel)),sizeof(this->nivel));
	stream->read(reinterpret_cast<char *> (&(this->tipoNodo)),sizeof(this->tipoNodo));
	stream->read(reinterpret_cast<char *> (&(cantidadElementos)),sizeof(cantidadElementos));

	string mensaje = "Se hidrata la hoja con ";
		mensaje += ServiceClass::toString(cantidadElementos);
		mensaje += " elementos.";
		Logger::log("NodoHojaArbol", "hidratar", mensaje);

	DatoElementoNodo* elemento;
	for (int i = 0; i < cantidadElementos; i++) {
		elemento = new DatoElementoNodo();
		elemento->hidratar(stream);
		elementos.push_back(elemento);
	}
	stream->read(reinterpret_cast<char *> (&(this->idSiguienteHoja)),sizeof(this->idSiguienteHoja));
}

NodoHojaArbol::~NodoHojaArbol() {
	list<DatoElementoNodo*>::iterator it;
	for(it=this->elementos.begin(); it!= this->elementos.end(); ++it)
	{
		delete(*it);
	}
}
