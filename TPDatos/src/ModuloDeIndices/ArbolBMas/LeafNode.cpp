/*
 * LeafNode.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#include "LeafNode.h"

using namespace std;

LeafNode::LeafNode() {
	this->level = 0;
	this->nextLeafNodeId = INVALID_NODE_ID;
}

LeafNode::LeafNode(list<DatoElementoNodo*> elementos, int nextLeafNodeId) {
	this->elementos = elementos;
	this->nextLeafNodeId = nextLeafNodeId;
}

LeafNode::~LeafNode() {
	list<DatoElementoNodo*>::iterator it = elementos.begin();
	while (it != elementos.end()) {
		delete (DatoElementoNodo*) *it;
		it++;
	}
	elementos.clear();
}

LeafNode* LeafNode::clone() {
	return new LeafNode(this->elementos, this->nextLeafNodeId);
}

void LeafNode::split(Node* sibling, int blockSize, string* promotedKey,
		int* promotedNodeID) {
	/*
	 * pasa la segunda mitad de elementos a la hoja hermana
	 */

	LeafNode* siblingLeafNode = (LeafNode*) sibling;
	list<DatoElementoNodo*>::iterator it = elementos.begin();
	DatoElementoNodo* elementoActual = NULL;
	int elementosSizeAccumulator = 0;
	int halfSizeOfCurrentNode = getDataSize() / 2;

	while (it != elementos.end()) {
		elementoActual = (DatoElementoNodo*) *it;
		if (elementosSizeAccumulator > halfSizeOfCurrentNode) {
			siblingLeafNode->insert(elementoActual);
			it = elementos.erase(it);
		} else {
			it++;
		}
		elementosSizeAccumulator += elementoActual->getSize();
		// En este caso, como el DatoElementoNodo esta contenido
		// dentro del LeafNode, debo considerar la data de control tambien,
		// por lo que llamo a getSize()
	}
	*promotedKey = this->getMaxKey();
	*promotedNodeID = siblingLeafNode->getNodeId();

	// Seteo los nextLeafNodeId
	siblingLeafNode->setNextLeafNodeId(this->nextLeafNodeId);
	this->nextLeafNodeId = siblingLeafNode->getNodeId();

}

/* Redistribuye el contenido entre nodos.
 * El nodo que se recibe es el hermano derecho. */
void LeafNode::redistribute(Node* sibling) {
	LeafNode* siblingLeafNode = (LeafNode*) sibling;
	list<DatoElementoNodo*> commonContent;

	list<DatoElementoNodo*>::iterator it = elementos.begin();
	DatoElementoNodo* elementoActual = NULL;
	while (it != elementos.end()) {
		elementoActual = (DatoElementoNodo*) *it;
		commonContent.push_back(elementoActual);
		it = elementos.erase(it);
	}

	it = siblingLeafNode->getElementos()->begin();
	while (it != siblingLeafNode->getElementos()->end()) {
		elementoActual = (DatoElementoNodo*) *it;
		commonContent.push_back(elementoActual);
		it = siblingLeafNode->getElementos()->erase(it);
	}

	long commonContentSize = this->getDataSize()
			+ siblingLeafNode->getDataSize();
	long elementosSize = 0;

	it = commonContent.begin();
	while (it != commonContent.end()) {
		elementoActual = (DatoElementoNodo*) *it;
		elementosSize += elementoActual->getSize();
		if (elementosSize < (commonContentSize) / 2) {
			this->insert(elementoActual);
		} else {
			siblingLeafNode->insert(elementoActual);
		}
		it = commonContent.erase(it);
	}
}

int LeafNode::insert(DatoElementoNodo* elemento) {

	list<DatoElementoNodo*>::iterator it;
	int posicion = elementoIndex(elemento);
	if (posicion == -1) {
		elementos.push_front(elemento);
		elementos.sort(&LeafNode::compareElementos);
	} else {
		it = this->elementos.begin();
		for (int i = 0; i < posicion; i++) {
			++it;
		}
		(*it)->agregarLibro(elemento->getLibros().front());
	}

	if (isOverFlowded(BLOCKSIZE)) {
		return OVERFLOWDED;
	}
	return EXIT_SUCCESS;
}

bool LeafNode::compareElementos(DatoElementoNodo* d1, DatoElementoNodo* d2) {
	if (d1->comparar(d2) == -1)
		return true;
	else
		return false;
}

int LeafNode::remove(DatoElementoNodo* elemento, int sizeOffset, fstream* fs,
		unsigned int* nodeCounter, fstream* freefs,
		unsigned int* freeNodeCounter) {
	list<DatoElementoNodo*>::iterator it = elementos.begin();
	int comparison;
	DatoElementoNodo* currentElemento = NULL;

	while (it != this->elementos.end()) {
		currentElemento = (DatoElementoNodo*) *it;
		comparison = elemento->comparar(currentElemento);
		switch (comparison) {
		case -1:
			return EXIT_FAILURE;
		case 0:
			((DatoElementoNodo*) (*it))->quitarLibro(
					elemento->getLibros().front());
			if (((DatoElementoNodo*) (*it))->getCantidadLibros() == 0) {
				elementos.erase(it);
				delete (DatoElementoNodo*) *it;
			}
			if (isUnderFlowded(BLOCKSIZE)) {
				return UNDERFLOWDED;
			}
			return EXIT_SUCCESS;
		case 1:
			// Sigo avanzando.
			break;
		}
		it++;
	}
	// Si termino de recorrer la lista y no lo encontré
	return EXIT_FAILURE;
}

void LeafNode::moveDataToLeft(InternalNode* parentNode, Node* nodeToMoveData,
		long fromDataLimit, long toDataLimit) {

	if (elementos.size() == 0) {
		/*
		 * si esta hoja no tiene elementos, le quito a padre la clave que apunta a la misma
		 */
		string orphanKey = parentNode->getKeyMajorEqualTo(
				nodeToMoveData->getMaxKey());
		parentNode->getKeys()->remove(orphanKey);
		return;
	}

	LeafNode* leafNodeToMoveData = (LeafNode*) nodeToMoveData;

	DatoElementoNodo* elemento = elementos.front();
	int elementoSize = elemento->getSize();

	while (elementoSize + nodeToMoveData->getDataSize() <= toDataLimit
			&& this->getDataSize() - elementoSize >= fromDataLimit) {

		elementos.remove(elemento);
		//Mueve un elemento
		leafNodeToMoveData->getElementos()->push_back(elemento);

		string previousKey = parentNode->getKeyMinorTo(elemento->getClave());
		parentNode->getKeys()->remove(previousKey);

		if (elementos.size() == 0)
			break;

		//Promueve la clave
		parentNode->insertKeyInOrderToList(elemento->getClave());

		elemento = elementos.front();
		elementoSize = elemento->getSize();

	}
}

void LeafNode::moveDataToRight(InternalNode* parentNode, Node* nodeToMoveData,
		long fromDataLimit, long toDataLimit) {

	if (elementos.size() == 0) {
		string orphanKey = parentNode->getKeyMinorEqualTo(
				nodeToMoveData->getMinKey());
		parentNode->getKeys()->remove(orphanKey);

		return;
	}
	LeafNode* leafNodeToMoveData = (LeafNode*) nodeToMoveData;

	DatoElementoNodo* elemento = elementos.back();
	int elementoSize = elemento->getSize();

	while (elementoSize + nodeToMoveData->getDataSize() <= toDataLimit
			&& this->getDataSize() - elementoSize >= fromDataLimit) {

		elementos.remove(elemento);
		//Mueve un elemento
		leafNodeToMoveData->getElementos()->push_front(elemento);
		string previousKey = parentNode->getKeyMajorEqualTo(
				elemento->getClave());
		parentNode->getKeys()->remove(previousKey);

		if (elementos.size() == 0)
			break;

		elemento = elementos.back();

		//Promueve la clave
		parentNode->insertKeyInOrderToList(elemento->getClave());
		elementoSize = elemento->getSize();
	}
}

int LeafNode::modify(DatoElementoNodo* elemento) {
	list<DatoElementoNodo*>::iterator it = elementos.begin();
	int comparison;
	long newSize;
	bool overflowded;
	DatoElementoNodo* elementoActual = NULL;
	stringstream ss(ios_base::in | ios_base::out | ios_base::binary);
	while (it != this->elementos.end()) {
		/*
		 * busca al DatoElementoNodo que quiere modificar
		 */
		elementoActual = (DatoElementoNodo*) *it;
		comparison = elemento->comparar(elementoActual);
		switch (comparison) {
		case -1:
			return NOT_FOUNDED;
		case 0:
			/*
			 * varifica que no se produzca overflow al realizar la modificaciòn
			 */
			newSize = (this->getDataSize() - elementoActual->getSize()
					+ elemento->getSize());
			overflowded = newSize > (BLOCKSIZE - getCtrlDataSize())
					* MAX_PERCENTAGE;
			if (overflowded) {
				return OVERFLOWDED;
			}
			//ss.write(record->getData(),record->getDataSize());
			//currentRecord->edit(record->getKey(),&ss);
			if (isUnderFlowded(BLOCKSIZE)) {
				return UNDERFLOWDED;
			}
			return EXIT_SUCCESS;
		case 1:
			break;
		}
		it++;
	}
	return NOT_FOUNDED;
}

DatoElementoNodo* LeafNode::find(DatoElementoNodo* elemento) {
	list<DatoElementoNodo*>::iterator it;
	DatoElementoNodo* elementoActual = NULL;

	if (elementos.empty()) {
		return NULL;
	}

	it = elementos.begin();
	while (it != elementos.end()) {
		elementoActual = (DatoElementoNodo*) *it;
		if (elemento->comparar(elementoActual) <= 0) {
			break;
		}
		it++;
	}
	return elementoActual;
}

list<int> LeafNode::getKeys() {
}

void LeafNode::serialize(iostream* stream) {
	/*
	 * Se serializa en el siguiente orden
	 * <TipoNodo><Nivel><IdNodo><CantidadDatoElementoNodo><DatoElementoNodo>...<DatoElementoNodo><SiguienteHoja>
	 * el tipo de nodo se escribe fuera del metodo
	 */
	int cantidadElementos = this->elementos.size();

	stream->write(reinterpret_cast<char *> (&(this->level)),
			sizeof(this->level));
	stream->write(reinterpret_cast<char *> (&(this->nodeId)),
			sizeof(this->nodeId));
	stream->write(reinterpret_cast<char *> (&cantidadElementos),
			sizeof(cantidadElementos));

	//	DatoElementoNodo* elemento;
	//	list<DatoElementoNodo*>::iterator it;
	//	for (it = this->elementos.begin(); it != this->elementos.end(); ++it) {
	//		elemento = *it;
	//		elemento->serializar(stream);
	//	}

	if (cantidadElementos > 0) {

		DatoElementoNodo* aux = NULL;
		list<DatoElementoNodo*>::iterator it;

		list<DatoElementoNodo*>* frontDecodedElements = new list<
				DatoElementoNodo*> ();
		for (it = this->elementos.begin(); it != this->elementos.end(); ++it) {
			aux = new DatoElementoNodo((*it)->getClave(), (*it)->getLibros());
			frontDecodedElements->push_back(aux);

		}

		list<DatoElementoNodo*>* frontCodedElements = frontCode(
				frontDecodedElements);
		for (it = frontCodedElements->begin(); it != frontCodedElements->end(); ++it) {
			aux = (*it);
			aux->serializar(stream);
		}
	}

	stream->write(reinterpret_cast<char *> (&(this->nextLeafNodeId)),
			sizeof(this->nextLeafNodeId));

}

list<DatoElementoNodo*>* LeafNode::frontCode(
		list<DatoElementoNodo*>* frontDecodedElements) {

	list<DatoElementoNodo*>* resultado = new list<DatoElementoNodo*> ();

	if (!frontDecodedElements->empty())
	{
		DatoElementoNodo* aux = frontDecodedElements->front();

		//quito a la palabraInicial de la lista
		//para empezar a encodear a partir de la segunda
		frontDecodedElements->pop_front();

		//la palabraInicial se guarda sin encodear
		resultado->push_back(aux);

		DatoElementoNodo* datoAnterior = aux;
		for (list<DatoElementoNodo*>::iterator it = (frontDecodedElements->begin()); it
				!= frontDecodedElements->end(); ++it) {

			aux = frontCode(datoAnterior, (*it));

			datoAnterior = (*it);
			resultado->push_back(aux);
		}
	}
	return resultado;

}

DatoElementoNodo* LeafNode::frontCode(DatoElementoNodo* anterior,
		DatoElementoNodo* actual) {

	//cout << "Frontcodeando: " << anterior->getClave() << " con: "
		//	<< actual->getClave() << endl;

	DatoElementoNodo* resultado = new DatoElementoNodo(actual->getClave(),
			actual->getLibros());

	//short int sizePalabraActual = actual->getCantidadLetrasClaveActual();
	short int sizePalabraActual = resultado->getCantidadLetrasClaveActual();

	short int i = 0;
	while ((i + 1) <= anterior->getCantidadLetrasClaveActual() && (i + 1)
			<= sizePalabraActual) {
		if (((actual->getClave())[i]) == (anterior->getClave())[i]) {
			i++;
		} else
			break;
	}
	resultado->setCantidadLetrasClaveAnterior(i);
	resultado->setCantidadLetrasClaveActual(sizePalabraActual - i);
	resultado->setClave(
			actual->getClave().substr(
					resultado->getCantidadLetrasClaveAnterior(),
					resultado->getCantidadLetrasClaveActual()));

	//cout << resultado->getClave() << endl;

	return resultado;

}

void LeafNode::deserialize(iostream* stream) {
	/*
	 * Se hidrata en el siguiente orden
	 * <TipoNodo><Nivel><IdNodo><CantidadDatoElementoNodo><DatoElementoNodo>...<DatoElementoNodo><SiguienteHoja>
	 * el tipo de nodo y nivel se recuperan fuera del metodo
	 */
	int cantidadElementos = 0;

	stream->read(reinterpret_cast<char *> (&(this->nodeId)),
			sizeof(this->nodeId));
	stream->read(reinterpret_cast<char *> (&(cantidadElementos)),
			sizeof(cantidadElementos));

	//	DatoElementoNodo* elemento;
	//	for (int i = 0; i < cantidadElementos; i++) {
	//		elemento = new DatoElementoNodo();
	//		elemento->hidratar(stream);
	//		elementos.push_back(elemento);
	//	}

	DatoElementoNodo* frontCodedElement;
	list<DatoElementoNodo*>* frontCodedElements =
			new list<DatoElementoNodo*> ();
	for (int i = 0; i < cantidadElementos; i++) {
		frontCodedElement = new DatoElementoNodo();
		frontCodedElement->hidratar(stream);
		frontCodedElements->push_back(frontCodedElement);

//		cout << "Recuperando DatoElementoNodo FrontCodeado, clave: "
//				<< frontCodedElement->getCantidadLetrasClaveAnterior() << " "
//				<< frontCodedElement->getCantidadLetrasClaveActual() << " "
//				<< frontCodedElement->getClave() << endl;
	}

	list<DatoElementoNodo*>* frontDecodedElements = frontDecode(
			frontCodedElements);
	list<DatoElementoNodo*>::iterator it;
	for (it = frontDecodedElements->begin(); it != frontDecodedElements->end(); ++it) {
		this->elementos.push_back((*it));
	}

	stream->read(reinterpret_cast<char *> (&(this->nextLeafNodeId)),
			sizeof(this->nextLeafNodeId));
}

list<DatoElementoNodo*>* LeafNode::frontDecode(
		list<DatoElementoNodo*>* elementos) {

	list<DatoElementoNodo*>* resultado = new list<DatoElementoNodo*> ();

	//tomo el primer elemento no encodeado
	//para comenzar a realizar las comparaciones
	if(!elementos->empty())
	{
		DatoElementoNodo* aux = elementos->front();

		//quito el primer elemento de la lista para empezar a iterar
		//por el segundo
		elementos->pop_front();

		//guardo la primera palabra que no estaba encodeada.
		resultado->push_back(aux);

		string claveAux = "";
		DatoElementoNodo* datoAnterior = aux;
		list<DatoElementoNodo*>::const_iterator ci;
		for (ci = elementos->begin(); ci != elementos->end(); ++ci) {

			aux = new DatoElementoNodo("", (*ci)->getLibros());

			claveAux.append(
					datoAnterior->getClave().substr(0,
							(*ci)->getCantidadLetrasClaveAnterior()));
			claveAux.append((*ci)->getClave());
			aux->setClave(claveAux);

			//palabraDecodificada->append(palabraDecodificadaAnterior->substr(0,(*ci)->cantidadLetrasPalabraAnterior));
			//palabraDecodificada->append((*ci)->palabraEncodeada);

			claveAux = "";
			datoAnterior = aux;
			resultado->push_back(aux);
			//cout << "Resultado decoding: " << aux->getClave() << endl;

		}
	}

	return resultado;

}

list<DatoElementoNodo*>* LeafNode::getElementos() {
	return &elementos;
}

void LeafNode::setNextLeafNodeId(int nextLeaf) {
	this->nextLeafNodeId = nextLeaf;
}

void LeafNode::readElementos() {
}

int LeafNode::getNextLeafNodeId() {
	return this->nextLeafNodeId;
}

/**
 * If the DatoElementoNodo exists, returns the index position of the elemento inside the Node's list of elementos.
 * If the DatoElementoNodo does not exist, returns -1
 */
int LeafNode::elementoIndex(DatoElementoNodo* elemento) {
	list<DatoElementoNodo*>::iterator it = elementos.begin();
	int comparison, counter = 0;
	DatoElementoNodo* elementoActual = NULL;

	while (it != this->elementos.end()) {
		elementoActual = (DatoElementoNodo*) *it;

		comparison = elemento->comparar(elementoActual);
		switch (comparison) {
		case 1:
			counter++;
			break;
		case 0:
			return counter;
		case -1:
			return -1;
		}

		it++;
	}
	return -1;
}

int LeafNode::getCtrlDataSize() {
	int ctrlDataSize = 0;
	ctrlDataSize += sizeof(level);
	ctrlDataSize += sizeof(nodeId);
	ctrlDataSize += sizeof(int); // Este int representa la cantidad de registros.
	ctrlDataSize += sizeof(int); // Este int representa el Id del siguiente LeafNode.

	return ctrlDataSize;
}

long LeafNode::getDataSize() {
	// Sumo el tamaño de los registros que contiene.
	long dataSize = 0;

	/*
	 * Genero una copia de los elementos para
	 * calcular espacio en el archivo
	 * (front coding)
	 */
	DatoElementoNodo* aux = NULL;
	list<DatoElementoNodo*>::iterator it;
	list<DatoElementoNodo*>* frontDecodedElements =
			new list<DatoElementoNodo*> ();
	for (it = this->elementos.begin(); it != this->elementos.end(); ++it) {
		aux = new DatoElementoNodo((*it)->getClave(), (*it)->getLibros());
		frontDecodedElements->push_back(aux);
	}

	/*
	 * frontcodeo los elementos
	 */
	list<DatoElementoNodo*>* frontCodedElements = frontCode(
			frontDecodedElements);

	/*
	 * realizo el calculo
	 */
	for (it = frontCodedElements->begin(); it != frontCodedElements->end(); it++) {
		aux = (DatoElementoNodo*) *it;
		dataSize += aux->getSize();
	}

	/*
	 * libero la memoria auxiliar
	 */
	for (it = frontCodedElements->begin(); it != frontCodedElements->end(); ++it) {
		aux = *it;
		delete (aux);
	}
	delete (frontCodedElements);

	return dataSize;
}

long LeafNode::getFreeDataSizeOnRight() {
	long minSize = (BLOCKSIZE - getCtrlDataSize()) * MIN_PERCENTAGE;
	long freeDataSize = 0;
	long dataSize = 0;

	/*
	 * Genero una copia de los elementos para
	 * calcular espacio en el archivo
	 * (front coding)
	 */
	DatoElementoNodo* aux = NULL;
	list<DatoElementoNodo*>::iterator it;
	list<DatoElementoNodo*>* frontDecodedElements =
			new list<DatoElementoNodo*> ();
	for (it = this->elementos.begin(); it != this->elementos.end(); ++it) {
		aux = new DatoElementoNodo((*it)->getClave(), (*it)->getLibros());
		frontDecodedElements->push_back(aux);
	}

	/*
	 * frontcodeo los elementos
	 */
	list<DatoElementoNodo*>* frontCodedElements = frontCode(
			frontDecodedElements);

	/*
	 * realizo el calculo
	 */
	for (it = frontCodedElements->begin(); it != frontCodedElements->end(); it++) {
		aux = (DatoElementoNodo*) *it;
		if (dataSize >= minSize)
			freeDataSize += aux->getSize();
		dataSize += aux->getSize();
	}

	/*
	 * libero la memoria auxiliar
	 */
	for (it = frontCodedElements->begin(); it != frontCodedElements->end(); ++it) {
		aux = *it;
		delete (aux);
	}
	delete (frontCodedElements);

	return freeDataSize;
}

long LeafNode::getFreeDataSizeOnLeft() {
	long minSize = (BLOCKSIZE - getCtrlDataSize()) * MIN_PERCENTAGE;
	long freeDataSize = 0;
	long dataSize = 0;

	/*
	 * Genero una copia de los elementos para
	 * calcular espacio en el archivo
	 * (front coding)
	 */
	DatoElementoNodo* aux = NULL;
	list<DatoElementoNodo*>::iterator it;
	list<DatoElementoNodo*>* frontDecodedElements =
			new list<DatoElementoNodo*> ();
	for (it = this->elementos.begin(); it != this->elementos.end(); ++it) {
		aux = new DatoElementoNodo((*it)->getClave(), (*it)->getLibros());
		frontDecodedElements->push_back(aux);
	}

	/*
	 * frontcodeo los elementos
	 */
	list<DatoElementoNodo*>* frontCodedElements = frontCode(
			frontDecodedElements);

	/*
	 * realizo el calculo
	 */
	for (it = frontCodedElements->begin(); it != frontCodedElements->end(); it++) {
		aux = (DatoElementoNodo*) *it;
		if (getDataSize() - dataSize > minSize)
			freeDataSize += aux->getSize();
		dataSize += aux->getSize();
	}

	/*
	 * libero la memoria auxiliar
	 */
	for (it = frontCodedElements->begin(); it != frontCodedElements->end(); ++it) {
		aux = *it;
		delete (aux);
	}
	delete (frontCodedElements);

	return freeDataSize;
}

long LeafNode::getSize() {
	long size = 0;
	size += getCtrlDataSize();
	size += getDataSize();

	return size;
}
/**
 * Retorna:
 * TRUE: Si el maximo porcentaje de la CAPACIDAD (BLOCKSIZE-data de control) del bloque es MENOR que el tamaño de la data
 * FALSE: Si sucede lo contrario
 */
bool LeafNode::isOverFlowded(int blockSize) {
	return (getDataSize() > (BLOCKSIZE - getCtrlDataSize()) * MAX_PERCENTAGE);
}

bool LeafNode::isUnderFlowded(int blockSize) {
	return (getDataSize() < (BLOCKSIZE - getCtrlDataSize()) * MIN_PERCENTAGE);
}

string LeafNode::getMaxKey() {
	return ((DatoElementoNodo *) this->elementos.back())->getClave();
}

string LeafNode::getMinKey() {
	return ((DatoElementoNodo *) this->elementos.front())->getClave();
}

void LeafNode::toStringXML(iostream* ios, int rootLevel, int sizeOffset,
		fstream* fs) {
}

void LeafNode::toString(iostream* ios, int rootLevel, int sizeOffset,
		fstream* fs) {
	string tabs = setTabs(rootLevel - this->level);

	(*ios) << tabs << "|----- [node id=[" << getNodeId() << "] level=["
			<< getLevel() << "] nodeSize=[" << this->getSize()
			<< "] controlDataSize=[" << this->getCtrlDataSize()
			<< "]  nodeDataSize=[" << this->getDataSize() << "] ]" << endl;
	elementosToString(ios, rootLevel);
}

void LeafNode::elementosToString(iostream* ios, int rootLevel) {

	/*
	 * Genero una copia de los elementos para
	 * mostrar como queda persistido en el archivo
	 * (front coding)
	 */
	DatoElementoNodo* aux = NULL;
	list<DatoElementoNodo*>::iterator it;
	list<DatoElementoNodo*>* frontDecodedElements =
			new list<DatoElementoNodo*> ();
	for (it = this->elementos.begin(); it != this->elementos.end(); ++it) {
		aux = new DatoElementoNodo((*it)->getClave(), (*it)->getLibros());
		frontDecodedElements->push_back(aux);
	}

	/*
	 * frontcodeo los elementos
	 */
	list<DatoElementoNodo*>* frontCodedElements = frontCode(
			frontDecodedElements);
	for (it = frontCodedElements->begin(); it != frontCodedElements->end(); ++it) {
		aux = *it;
		aux->toString(ios, rootLevel);
	}

	/*
	 * libero la memoria auxiliar
	 */
	for (it = frontCodedElements->begin(); it != frontCodedElements->end(); ++it) {
		aux = *it;
		delete (aux);
	}
	delete (frontCodedElements);

	//	DatoElementoNodo* elemento;
	//	list<DatoElementoNodo*>::iterator it = this->elementos.begin();
	//	while (it != this->elementos.end()) {
	//		elemento = *it;
	//		elemento->toString(ios, rootLevel);
	//		it++;
	//	}

}

void LeafNode::elementosToStringXML(iostream* ios, int rootLevel) {

}

