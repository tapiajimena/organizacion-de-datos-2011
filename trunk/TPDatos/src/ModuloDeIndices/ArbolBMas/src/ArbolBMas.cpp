/*
 * ArbolBMas.cpp
 *
 *    Autor   	 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 *	Clase que representa la estructura del arbol.
 *
 */


#include "ArbolBMas.h"

ArbolBMas::ArbolBMas()
{
	setMinCantidadClaves();
	setMaxCantidadHijos();
}


ArbolBMas::ArbolBMas(string pathIndice, int sizeBloque)
{
	setSizeBloque(sizeBloque);
	setPathArcIndice(pathIndice);
	setSizeMetaDataControl(2*sizeof(uint32_t));//sizeBloque, cantidadBloques

	//si no existe se crea y se inserta una raiz
	if(CrearSiNoExiste(pathIndice.c_str(),this->arcIndice))
	{
		string pathAux =getPathArcIndice()+"NodosLibres";
		Crear(pathAux.c_str(), arcNodosLibres, true);

		this->cantidadBloques = 1;
		this->cantidadBloquesLibres = 0;
		this->setMetaDataControl();

		raiz = new NodoHojaArbol();
		raiz->setId(0);
		raiz->setNivel(0);

		this->setDatoNodo((NodoHojaArbol*)raiz);
	}
	else //el archivo ya existe
	{
		Abrir(pathIndice.c_str(), arcNodosLibres, true);
		raiz = leerNodo(0);	//lee y carga la raiz, del primer bloque del archivo
	}
}

int ArbolBMas::insertarDatoRecursivo(string clave, NodoArbol* nodoActual, string clavePromovida, int idNodoPromovido)
{
	int rdo;
	NodoArbol* nodoAInsertar;

	if (nodoActual->getTipoNodo() == 'H')
	{
		rdo = ((NodoHojaArbol*)nodoActual)->insertar(clave);

		if (rdo == EXITO)
		{
			nodoAInsertar = new NodoHojaArbol();
			int aux = nodoActual->getId();
			aux++;
			nodoAInsertar->setId(aux);
			setDatoNodo((NodoHojaArbol*)nodoAInsertar);
		}
		else if (rdo == OVERFLOWDED)
		{
			nodoAInsertar = new NodoHojaArbol();

			//NodeFactory::assignNodeId(newNode,&nodeCounter,&freeNodeCounter,&freeNodesFile);
			nodoActual->partir(nodoAInsertar, SIZE_BLOQUE, clavePromovida, idNodoPromovido);

			int aux = nodoActual->getId();
			aux++;
			nodoAInsertar->setId(aux);

			setDatoNodo(nodoActual);
			setDatoNodo(nodoAInsertar);

			delete(nodoAInsertar);
			return OVERFLOWDED;
		}
		else if (rdo == 2)//duplicado
			return rdo;

		return EXITO;//ok
	}
	else// Es un nodo interno
	{
		NodoInternoArbol* nodoInterno = (NodoInternoArbol*)nodoActual;
		uint32_t offsetNodo = nodoInterno->buscarClave(clave);

		NodoArbol* nodoSiguiente = leerNodo(offsetNodo);
		rdo = insertarDatoRecursivo(clave, nodoSiguiente, clavePromovida, idNodoPromovido);

		if (rdo == OVERFLOWDED)
		{
			nodoInterno->agregarClaveHijo(clavePromovida, idNodoPromovido);
			if (nodoInterno->isOverflowded(SIZE_BLOQUE))
			{
				// Si luego de insertar el "registrito" quedo en overflow
				nodoAInsertar = new NodoInternoArbol();
				nodoAInsertar->setNivel(nodoInterno->getNivel());
				//FabricaDeNodos::asignarId(nodoAInsertar, arcNodosLibres);
				int aux = nodoInterno->getId();
				nodoAInsertar->setId(++aux);
				nodoInterno->partir(nodoAInsertar,SIZE_BLOQUE, clavePromovida, idNodoPromovido);
				setDatoNodo(nodoInterno);
				setDatoNodo(nodoAInsertar);
				delete(nodoInterno);
				delete(nodoAInsertar);
				return OVERFLOWDED;
			}
			setDatoNodo(nodoInterno);
			delete(nodoSiguiente);
			return EXITO;
		}
		else
		{
			delete(nodoSiguiente);
			return rdo;
		}
		delete (nodoInterno);
	}
}



void ArbolBMas::setDatoNodo(NodoArbol* nodo)
{
	//TODO definir la metadata
	uint32_t offset;
	stringstream ssAux;
	offset 				= sizeMetaDataControl + (nodo->getId() * SIZE_BLOQUE);
	DatoNodo* datoNodo 	= new DatoNodo();

	if (nodo->getTipoNodo() == 'H')
		datoNodo->setDatoNodo((NodoHojaArbol*)nodo);
	else
		datoNodo->setDatoNodo((NodoInternoArbol*)nodo);

	string aux = datoNodo->getDato();
	ssAux.write(aux.c_str(), datoNodo->getSize());
	Escribir(arcIndice,&ssAux, offset);

	delete(datoNodo);
}


int ArbolBMas::setMetaDataControl()
{
	//TODO Definirla correctamente
	/* Meta data de control del arbol:
	 * <SizeBloque><CantidadBloques><CantidadBloquesLibres>? Va o no? Serviria?
	 *
	 */
	stringstream ss;
	ss.write(reinterpret_cast<char *>(&sizeBloque),sizeof(sizeBloque));
	ss.write(reinterpret_cast<char *>(&cantidadBloques),sizeof(cantidadBloques));

	IrAlInicio(arcIndice);
	if (Escribir(arcIndice,&ss))
		return 1;
	else
		return -1;
}


string ArbolBMas::getMetaDataControl()
{
	/* Meta data de control del arbol:
	 * <SizeBloque><CantidadBloques><CantidadBloquesLibres>? Va o no? Serviria?
	 *
	 */
	stringstream ss(ios_base::in| ios_base::out| ios_base::binary);
	RecuperarEstructura(arcIndice,ss,0,this->sizeMetaDataControl);

	ss.seekp(0, ios_base::beg);
	ss.read(reinterpret_cast<char *>(&sizeBloque), sizeof(sizeBloque));
	ss.read(reinterpret_cast<char *>(&cantidadBloques), sizeof(cantidadBloques));

	return ss.str();
}


int ArbolBMas::insertar(string clave)
{
	int rdo;
	int idNodoPromovido;
	string clavePromovida;


	if(clave.length() > MAX_SIZE_DATO)
		return ERROR;

	rdo = insertarDatoRecursivo(clave, raiz, clavePromovida, idNodoPromovido);

	if(rdo == OVERFLOWDED)
	{
		// Si se desborda la raiz...
		NodoInternoArbol* nuevaRaiz = new NodoInternoArbol();
		nuevaRaiz->setId(0);
		nuevaRaiz->setNivel(raiz->getNivel()+1);
		//FabricaDeNodos::asignarId(root,&nodeCounter,&freeNodeCounter,&freeNodesFile);

		nuevaRaiz->getHijos().push_back(raiz->getId()); //por orden se pone una despues de la otra
		nuevaRaiz->agregarClaveHijo(clavePromovida, idNodoPromovido);

		setDatoNodo(raiz);
 		setDatoNodo(nuevaRaiz);
 		delete this->raiz;
		this->raiz	=	nuevaRaiz;
		return EXITO;
	}

	return rdo;

}



NodoArbol* ArbolBMas::leerNodo(int idNodo)
{
	NodoArbol* nodo;
	DatoNodo* dNodo = new DatoNodo();
	stringstream ss;
	int nivel= 0;
	uint32_t offset = this->sizeMetaDataControl + (SIZE_BLOQUE *idNodo);

	RecuperarEstructura(arcIndice,ss,offset,SIZE_BLOQUE);

	ss.read(reinterpret_cast<char *> (&nivel), sizeof(int));
	dNodo->setDato(ss.str());
	if (nivel == 0)
	{
		nodo = new NodoHojaArbol();
		dNodo->hidratar((NodoHojaArbol*)nodo);
	}
	else
	{
		nodo = new NodoInternoArbol();
		nodo->setNivel(nivel);
		dNodo->hidratar((NodoInternoArbol*)nodo);
	}

	return nodo;
}

int ArbolBMas::getMaxCantidadHijos() const {
	return maxCantidadHijos;
}

int ArbolBMas::getMinCantidadClaves() const {
	return minCantidadClaves;
}

int ArbolBMas::getOrden() const {
	return orden;
}

void ArbolBMas::setMaxCantidadHijos() {
	this->maxCantidadHijos = (this->orden + 1);
}

void ArbolBMas::setMinCantidadClaves() {
	this->minCantidadClaves = this->orden/2;
}

void ArbolBMas::setOrden(int orden) {
	this->orden = orden;
}

uint32_t ArbolBMas::getOffsetRaiz() const
{
    return offsetRaiz;
}

string ArbolBMas::getPathArcIndice() const
{
    return pathArcIndice;
}

NodoArbol* ArbolBMas::getRaiz() const
{
    return raiz;
}

int ArbolBMas::getSizeBloque() const
{
    return sizeBloque;
}

void ArbolBMas::setOffsetRaiz(uint32_t offsetRaiz)
{
    this->offsetRaiz = offsetRaiz;
}

void ArbolBMas::setPathArcIndice(string pathArcIndice)
{
    this->pathArcIndice = pathArcIndice;
}

void ArbolBMas::setRaiz(NodoArbol *raiz)
{
    this->raiz = raiz;
}

void ArbolBMas::setSizeBloque(int sizeBloque)
{
    this->sizeBloque = sizeBloque;
}

int ArbolBMas::getSizeMetaDataControl() const
{
	return sizeMetaDataControl;
}

void ArbolBMas::setSizeMetaDataControl(int sizeMetaDataControl)
{
	this->sizeMetaDataControl = sizeMetaDataControl;
}


ArbolBMas::~ArbolBMas() {
	// TODO Auto-generated destructor stub
	delete(this->raiz);
	Cerrar(this->arcIndice);
	Cerrar(this->arcNodosLibres);
}
