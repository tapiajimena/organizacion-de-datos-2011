#include "NodoInternoArbol.h"

NodoInternoArbol::NodoInternoArbol()
{
	this->tipoNodo = 'I';

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


void NodoInternoArbol::serializar(iostream* s)
{
	/* Se serializara:
	 * <IdNodo><Nivel><TipoNodo><CantidadClaves>[<SizeClave><Clave>]...[<SizeClave><Clave>]<idHijo>...<idHijo>
	 * */
	int hijoAux = 0;
	int sizeClave = 0;
	int cantidadClaves = this->claves.size();
	string claveAux;

	s->write(reinterpret_cast<char *>(&(id)), sizeof(id));//idNodo
	s->write(reinterpret_cast<char *>(&(nivel)), sizeof(nivel));//nivel
	s->write(reinterpret_cast<char *>(&(tipoNodo)), sizeof(tipoNodo));//tipoNodo
	s->write(reinterpret_cast<char *>(&cantidadClaves), sizeof(cantidadClaves));//cantidadClaves

	//se serializan las claves
	list<string> claves = this->claves;
	for (list<string>::const_iterator ci = claves.begin(); ci != claves.end(); ++ci)
	{
		claveAux = *ci;
		sizeClave = claveAux.size();
		s->write(reinterpret_cast<char *>(&sizeClave), sizeof(sizeClave));//sizeClave
		s->write(claveAux.c_str(), sizeClave);//clave
	}

	//se serializan los hijos TODO -5 encapsular cada for
	list<int> hijos = this->hijos;
	for (list<int>::const_iterator ci = hijos.begin(); ci != hijos.end(); ++ci)
	{
		hijoAux = *ci;
		s->write(reinterpret_cast<char *>(&hijoAux), sizeof(hijoAux));//hijo
	}

}


void NodoInternoArbol::hidratar(iostream* s)
{
	/* Se serializara:
	 * <IdNodo><Nivel><TipoNodo><CantidadClaves>[<SizeClave><Clave>]...[<SizeClave><Clave>]<idHijo>...<idHijo>
	 * */
	int sizeClave =0, cantidadClaves = 0, hijo= 0;
	char* claveAux = (char*)malloc(0);
	string clave;



	s->read(reinterpret_cast<char *>(&(id)), sizeof(id));//idNodo
	s->read(reinterpret_cast<char *>(&(nivel)), sizeof(nivel));//nivel
	s->read(reinterpret_cast<char *>(&(tipoNodo)), sizeof(tipoNodo));//tipoNodo
	s->read(reinterpret_cast<char *>(&cantidadClaves), sizeof(cantidadClaves));//cantidadClaves

	for(int i =0; i < cantidadClaves; i++)
	{
		s->read(reinterpret_cast<char *>(&sizeClave), sizeof(sizeClave));//sizeClave
		claveAux= (char*)realloc(claveAux, sizeClave);
		s->read(claveAux, sizeClave);//clave

		clave = claveAux;
		clave = clave.substr(0,sizeClave);

		agregarClave(clave);
	}

	for(int i =0; i <= cantidadClaves; i++)
	{
		s->read(reinterpret_cast<char *>(&hijo), sizeof(hijo));//sizeClave
		agregarHijo(hijo);
	}



}


void NodoInternoArbol::agregarClave(string clave) {
	this->claves.push_back(clave);
}

void NodoInternoArbol::agregarHijo(int idHijo) {
	this->hijos.push_back(idHijo);
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

list<string> NodoInternoArbol::getClaves(){
	return this->claves;
}

list<int> NodoInternoArbol::getHijos(){
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

}
