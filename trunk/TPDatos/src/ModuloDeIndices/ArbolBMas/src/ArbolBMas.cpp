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

ArbolBMas::ArbolBMas() {
	// TODO Auto-generated constructor stub
	setMinCantidadClaves();
	setMaxCantidadHijos();
	//setOrden();
}

int ArbolBMas::insertar(Dato* dato)
{
	int rdo;
	int clavePromovida, idNodoPromovido;

	//if(dato->getSize() > getMaxRecordSize())
		//return EXIT_FAILURE;

	//rdo = insertarDatoRecursivo(dato, , &promotedKey, &promotedNodeId);
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

int ArbolBMas::recursiveInsert(Dato* dato, NodoArbol* nodoActual, int* clavePromovida, int* idNodoPromovido)
{
	int result;
	Node* newNode = NULL;
	if (currentNode->getLevel() == 0)
	{
		// Es un LeafNode
		result = currentNode->insert(record);

		if (result == EXIT_SUCCESS)
			writeNode(currentNode);
		else if (result == OVERFLOWDED)
		{
			newNode = new LeafNode();
			NodeFactory::assignNodeId(newNode,&nodeCounter,&freeNodeCounter,&freeNodesFile);
			currentNode->split(newNode, BLOCKSIZE, promotedKey, promotedNodeId);
			writeNode(currentNode);
			writeNode(newNode);

			delete(newNode);
			return OVERFLOWDED;
		}
		else if (result == DUPLICATED)
			return result;
		return EXIT_SUCCESS;
	}
	else
	{
		// Es un InternalNode
		InternalNode* inner = (InternalNode*) currentNode;
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
}


int ArbolBMas::getMaxCantidadHijos() const {
	return maxCantidadHijos;
}

int ArbolBMas::getMinCantidadClaves() const {
	NodoInternoArbol nI;
	int a =nI.getId();
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

fstream ArbolBMas::getArcIndice() const
{
    return arcIndice;
}

uint32_t ArbolBMas::getOffsetRaiz() const
{
    return offsetRaiz;
}

string ArbolBMas::getPathArcIndice() const
{
    return pathArcIndice;
}

NodoArbol *ArbolBMas::getRaiz() const
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

ArbolBMas::~ArbolBMas() {
	// TODO Auto-generated destructor stub
}
