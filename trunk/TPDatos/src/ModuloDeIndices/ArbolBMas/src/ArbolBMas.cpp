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


// TODO Auto-generated constructor stub
	setMinCantidadClaves();
	setMaxCantidadHijos();
	//setOrden();
}


ArbolBMas::ArbolBMas(string pathIndice, int sizeBloque)
{
	setSizeBloque(sizeBloque);
	setPathArcIndice(pathIndice);
	setSizeMetaDataControl(2*sizeof(long int) );//sizeBloque, cantidadBloques

	if (CrearSiNoExiste(pathIndice.c_str(),this->arcIndice))
	{
		string pathAux =getPathArcIndice()+"NodosLibres";
		Crear(pathAux.c_str(), arcNodosLibres, true);
		this->cantidadBloques = 1;
		this->cantidadBloquesLibres = 0;

		this->raiz = new NodoHojaArbol();
		this->raiz->setId(0);
		this->setMetaDataControl();
	}



}

int ArbolBMas::insertarDatoRecursivo(Dato* dato, NodoArbol* nodoActual, string clavePromovida, int idNodoPromovido)
{
	NodoArbol* nodoAInsertar;

	if (nodoActual->getTipoNodo() == 'H')
	{
		int rdo = nodoActual->insertar(dato);

		if (rdo == 1)
		{
			nodoAInsertar = new NodoHojaArbol();

			setDatoNodo((NodoHojaArbol*)nodoAInsertar);
		}
		/*
		else if (rdo == OVERFLOWDED)
		{
			nodoAInsertar = new NodoHojaArbol();

			//NodeFactory::assignNodeId(newNode,&nodeCounter,&freeNodeCounter,&freeNodesFile);
			nodoActual->partir(nodoAInsertar, SIZE_BLOQUE, clavePromovida, idNodoPromovido);
			setDatoNodo(nodoActual);
			setDatoNodo(nodoAInsertar);

			delete(nodoAInsertar);
			return OVERFLOWDED;
		}
		else if (rdo == 2)//duplicado
			return rdo;
			*/
		return 1;//ok
	}
/*
	else
	{
		// Es un InternalNode
		InternalNode* inner = (InternalNode*) nodoActual;
		int locationId = inner->findLocation(record);

		Node* nextNode = readNode(locationId);
		result = recursiveInsert(record, nextNode, promotedKey, promotedNodeId);

		if (result == OVERFLOWDED)
		{
			inner->insertKeyChild(*promotedKey, *promotedNodeId);
			if (inner->isOverFlowded(BLOCKSIZE))
			{
				// Si luego de insertar el "registrito" quedo en overflow
				newNode = new InternalNode();
				newNode->setLevel(inner->getLevel());
				NodeFactory::assignNodeId(newNode,&nodeCounter,&freeNodeCounter,&freeNodesFile);
				inner->split(newNode, BLOCKSIZE, promotedKey, promotedNodeId);
				writeNode(inner);
				writeNode(newNode);
				delete(newNode);
				delete(nextNode);
				return OVERFLOWDED;
			}
			writeNode(inner);
			delete(nextNode);
			return EXIT_SUCCESS;
		}
		else
		{
			delete(nextNode);
			return result;
		}
	}
	*/
}




void ArbolBMas::setDatoNodo(NodoHojaArbol* nodo)
{
	stringstream* ssAux;

	//TODO definir la metadata
	int sizeMetaData = 20;
	uint32_t offset = sizeMetaData  + (nodo->getId() * SIZE_BLOQUE);


	//TODO
	DatoNodo* datoNodo = new DatoNodo(nodo);
	ssAux->write(datoNodo->getDato().c_str(), datoNodo->getSize());


	//FileManager::writeData(&file, offset, blockSize, &ios);
	Escribir(this->arcIndice,ssAux, offset);

	delete(datoNodo);
}

int ArbolBMas::setMetaDataControl()
{
	/* Meta data de control del arbol:
	 * <SizeBloque><CantidadBloques>¿<CantidadBloquesLibres>? Va o no? Serviria?
	 *
	 */

	cout<<"HOLA MUDNO!"<<sizeof(cantidadBloques);
	stringstream ss;
	ss.write(reinterpret_cast<char *>(&sizeBloque),sizeof(sizeBloque));
	ss.write(reinterpret_cast<char *>(&cantidadBloques),sizeof(cantidadBloques));

	IrAlInicio(arcIndice);
	if (Escribir(arcIndice,&ss))
		return 1;
	else
		return -1;
}


int ArbolBMas::insertar(Dato* dato)
{
	int rdo;
	int idNodoPromovido;
	string clavePromovida;


	if(dato->getSize() > MAX_SIZE_DATO)
		return ERROR;

	rdo = insertarDatoRecursivo(dato, raiz, clavePromovida, idNodoPromovido);
/*
	if(rdo == OVERFLOWDED)
	{
		// Si se desborda la raíz...
		InternalNode* newRoot = new InternalNode();
		newRoot->setLevel(root->getLevel()+1);
		newRoot->setNodeId(0);
		NodeFactory::assignNodeId(root,&nodeCounter,&freeNodeCounter,&freeNodesFile);

		newRoot->getChildIds()->push_back(root->getNodeId()); //por orden se pone una despues de la otra
		newRoot->insertKeyChild(promotedKey, promotedNodeId);

		writeNode(root);
 		writeNode(newRoot);
 		delete this->root;
		this->root=newRoot;
		return EXIT_SUCCESS;
	}
*/
	return rdo;

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
}
