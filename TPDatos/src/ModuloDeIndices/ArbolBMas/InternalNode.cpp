/*
 * InternalNode.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */
#include "InternalNode.h"
#include "NodeFactory.h"

InternalNode::InternalNode() {

}

InternalNode::~InternalNode() {
	keys.clear();
	childIds.clear();
}

void InternalNode::split(Node* sibling, int blockSize, string* promotedKey, int* promotedNodeID) {
	InternalNode* siblingInternalNode = (InternalNode*)sibling;

	list<string>::iterator itKey = this->keys.begin();
	list<int>::iterator itChildID = this->childIds.begin();

	string currentKey;
	int currentChildID=0;
	int nodeSizeAccumulator = 0;
	int halfSizeOfCurrentNode = getDataSize()/2;

	while (itKey != this->keys.end()) {
		currentKey= (string)*itKey;
		currentChildID = (int)*itChildID;

		if (nodeSizeAccumulator > halfSizeOfCurrentNode){
			siblingInternalNode->insertKeyToList((string)*itKey);  // el listado original ya esta ordenado, con mandarlo al final alcanza
			siblingInternalNode->insertChildIDToList((int)*itChildID);  // el listado original ya esta ordenado, con mandarlo al final alcanza
			itKey = keys.erase(itKey);
			itChildID = childIds.erase(itChildID);
		}
		else {
			itKey++;
			itChildID++;
		}

		//suma el espacio de disco que le quedarìa libre al nodo al partirse
		nodeSizeAccumulator += sizeof(int) + currentKey.length() + sizeof(currentChildID);
	}
	siblingInternalNode->insertChildIDToList((int)*itChildID);
	childIds.erase(itChildID);

	*promotedKey = this->getMaxKey();
	*promotedNodeID = siblingInternalNode->getNodeId();
	itKey--;
	keys.erase(itKey);
}

void InternalNode::insertKeyToList(string key){
	this->keys.push_back(key);
}

void InternalNode::insertKeyInOrderToList(string key){
	this->keys.push_back(key);
	this->keys.sort();
}

void InternalNode::insertChildIDToList(int childID){
	this->childIds.push_back(childID);
}

int InternalNode::insert(DatoElementoNodo* elemento) {
}

int InternalNode::remove(DatoElementoNodo* elemento, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter) {
	int childNodeId = findLocation(elemento);
	Node* node = NodeFactory::readNode(childNodeId, sizeOffset, fs);

	int result = node->remove(elemento, sizeOffset, fs, nodeCounter, freefs, freeNodeCounter);

	if(result == EXIT_FAILURE){
		delete node;
		return result;
	}

	if(result == UNDERFLOWDED){
		resolveUnderflow(node, sizeOffset, fs, nodeCounter, freefs, freeNodeCounter);
	}
	else if(result == OVERFLOWDED){
		resolveOverflow(node, sizeOffset, fs, nodeCounter, freefs, freeNodeCounter);
	}
	if (node->getDataSize()!=0)
		NodeFactory::writeNode(node, sizeOffset, fs);

	delete node;
	if(isUnderFlowded(BLOCKSIZE)) {
		return UNDERFLOWDED;
	}

	if (isOverFlowded(BLOCKSIZE))
		return OVERFLOWDED;

	return EXIT_SUCCESS;
}

void InternalNode::moveDataToLeft(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit){

	InternalNode* internalNodeToMoveData = (InternalNode*) nodeToMoveData;

	string keyToPromote = keys.front();

	while (2*sizeof(int) + keyToPromote.length() + internalNodeToMoveData->getDataSize() <= toDataLimit
			&& this->getDataSize() - 2*sizeof(int) - keyToPromote.length() >= fromDataLimit) {

		//Promote the key
		if(keys.size()>0){
			keyToPromote = keys.front();

			string previousKey = parentNode->getKeyMinorEqualTo(keyToPromote);
			int childId = childIds.front();

			parentNode->getKeys()->remove(previousKey);
			parentNode->insertKeyInOrderToList(keyToPromote);

			//Move childId and key
			internalNodeToMoveData->getChildIds()->push_back(childId);
			internalNodeToMoveData->getKeys()->push_back(previousKey);

			//Remove moved childId and key
			keys.remove(keyToPromote);

			childIds.remove(childId);
		}
		else{

			if(childIds.size() == 0)
				break;

			int childId = childIds.front();

			parentNode->getKeys()->remove(keyToPromote);

			//Move childId and key
			internalNodeToMoveData->getChildIds()->push_back(childId);
			internalNodeToMoveData->getKeys()->push_back(keyToPromote);

			childIds.remove(childId);
		}
	}
}

void InternalNode::moveDataToRight(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit){

	InternalNode* internalNodeToMoveData = (InternalNode*) nodeToMoveData;

	string keyToPromote = keys.back();

	while (2*sizeof(int) + keyToPromote.length() + internalNodeToMoveData->getDataSize() <= toDataLimit
			&& this->getDataSize() - 2*sizeof(int) - keyToPromote.length()   >= fromDataLimit) {

		if(keys.size() >0){
			keyToPromote = keys.back();

			//Promote the key
			string previousKey = parentNode->getKeyMajorEqualTo(keyToPromote);
			int childId = childIds.back();
			parentNode->getKeys()->remove(previousKey);
			parentNode->insertKeyInOrderToList(keyToPromote);

			//Move childId and key
			internalNodeToMoveData->getChildIds()->push_front(childId);
			internalNodeToMoveData->getKeys()->push_front(previousKey);

			keys.remove(keyToPromote);
			childIds.remove(childId);
		}
		else{

			if(childIds.size() == 0)
				break;
			int childId = childIds.back();
			string keyToPromote = parentNode->getKeyMinorTo(nodeToMoveData->getMinKey());

			parentNode->getKeys()->remove(keyToPromote);

			//Move childId and key
			internalNodeToMoveData->getChildIds()->push_front(childId);
			internalNodeToMoveData->getKeys()->push_front(keyToPromote);

			childIds.remove(childId);
		}
	}
}

string InternalNode::getKeyMinorEqualTo(string key){

	list<string>::iterator itKeys=keys.end();

	do{
		itKeys--;
		if(strcmp((*itKeys).c_str(), key.c_str())<=0){
			return *itKeys;
		}
	}
	while(itKeys != keys.begin());
	return key;
}

string InternalNode::getKeyMinorTo(string clave)
{

	list<string>::iterator itClaves=keys.end();

	do{
		itClaves--;
		if(strcmp((*itClaves).c_str(), clave.c_str())<0){
			return *itClaves;
		}
	}
	while(itClaves != keys.begin());
	return clave;
}

string InternalNode::getKeyMajorEqualTo(string key){

	for (list<string>::iterator itKeys=keys.begin(); itKeys!=keys.end(); ++itKeys){
		if(strcmp((*itKeys).c_str(), key.c_str())>=0){
			return *itKeys;
		}
	}
	return key;
}


DatoElementoNodo* InternalNode::find(DatoElementoNodo* elemento) {
}

int InternalNode::resolveOverflow(Node* node, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter){

	Node* newNode;
	if(node->getLevel() > 0)
		newNode = new InternalNode();
	else
		newNode = new LeafNode();

	NodeFactory::assignNodeId(newNode, nodeCounter, freeNodeCounter, freefs);
	newNode->setLevel(node->getLevel());


	list<string>::iterator keyIterator = keys.begin();
	list<int>::iterator childIterator = childIds.begin();

	string a;
	int b;

	node->split(newNode, BLOCKSIZE, &a, &b );

	insertKeyChild(a,b);

	NodeFactory::writeNode(newNode, sizeOffset, fs);
	delete newNode;
	return EXIT_SUCCESS;

}

void InternalNode::synchronizeOnRemove(Node* node, unsigned int* freeNodeCounter, fstream* fs){
	if(node->getDataSize() == 0){
		this->childIds.remove(node->getNodeId());
		NodeFactory::addFreeNodeId(node->getNodeId(), freeNodeCounter, fs);
	}
}

int InternalNode::resolveUnderflow(Node* node, int sizeOffset, fstream* fs,
		unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter){

	int leftSiblingId = getLeftSiblingId(node);
	int rightSiblingId = getRightSiblingId(node);

	Node* leftSibling = NULL;
	if(leftSiblingId != INVALID_NODE_ID)
		leftSibling = NodeFactory::readNode(leftSiblingId, sizeOffset, fs);

	Node* rightSibling = NULL;
	if(rightSiblingId != INVALID_NODE_ID)
		rightSibling = NodeFactory::readNode(rightSiblingId, sizeOffset, fs);

	if(tryRotate(leftSibling, node, rightSibling) == EXIT_FAILURE){
		merge(leftSibling, node, rightSibling);
		synchronizeOnRemove(node,freeNodeCounter, freefs);
	}

	if(leftSibling != NULL && leftSibling->isOverFlowded(BLOCKSIZE)){
		resolveOverflow(leftSibling, sizeOffset, fs, nodeCounter, freefs, freeNodeCounter);}
	if(rightSibling != NULL && rightSibling->isOverFlowded(BLOCKSIZE)){
		resolveOverflow(rightSibling, sizeOffset, fs, nodeCounter, freefs, freeNodeCounter);
	}
	if(leftSibling != NULL){
		NodeFactory::writeNode(leftSibling, sizeOffset, fs);
		delete leftSibling;
	}
	if(rightSibling != NULL){
		NodeFactory::writeNode(rightSibling, sizeOffset, fs);
		delete rightSibling;
	}

	return EXIT_SUCCESS;
}

list<string>* InternalNode::getKeys() {
	return &keys;
}

list<int>* InternalNode::getChildIds() {
	return &childIds;
}

void InternalNode::insertKeyChild(string key, int childId) {
	string currentKey;

	list<string>::iterator keyIterator = keys.begin();
	list<int>::iterator childIterator = childIds.begin();

	while (keyIterator != keys.end()) {

		currentKey = *keyIterator;
		if (strcmp(key.c_str(), currentKey.c_str())<0) {
			break;
		}
		keyIterator++;
		childIterator++;
	}

	keys.insert(keyIterator, key);

	childIterator++;
	childIds.insert(childIterator, childId);
}

int InternalNode::findLocation(DatoElementoNodo* elemento) {
	string currentKey;
	int locationId = 0;
	list<string>::iterator keyIterator = keys.begin();
	list<int>::iterator childIterator = childIds.begin();

	DatoElementoNodo* elementoActual;
	while (keyIterator != keys.end()) {
		currentKey = (string) *keyIterator;
		elementoActual = new DatoElementoNodo(currentKey);
		if (elemento->comparar(elementoActual) != 1) {
			locationId = *childIterator;
			delete elementoActual;
			return locationId;
		}
		delete elementoActual;
		keyIterator++;
		childIterator++;
	}

	/*
	 * en caso de no poder encontrarlo
	 * devuelve el hijo de màs a la derecha.
	 */
	locationId =  *childIterator;
	return locationId;
}

/* Devuelve el id del hermano izquierdo del nodo recibido.
 * Si no tiene, devuelve INVALID_NODE_ID*/
int InternalNode::getLeftSiblingId(Node* childNode) {
	int id = childNode->getNodeId();
	int currentId;
	int leftSiblingId = INVALID_NODE_ID;
	list<int>::iterator childIdIterator = childIds.begin();
	while(childIdIterator != childIds.end()) {
		currentId = (int) *childIdIterator;
		if(currentId == id) {
			if(childIdIterator != childIds.begin()) {
				childIdIterator--;
				leftSiblingId = *childIdIterator;
			}
			return leftSiblingId;
		}
		childIdIterator++;
	}
	return leftSiblingId;
}

/* Devuelve el id del hermano izquierdo del nodo recibido.
 * Si no tiene, devuelve INVALID_NODE_ID*/
int InternalNode::getRightSiblingId(Node* childNode) {
	int id = childNode->getNodeId();
	int currentId;
	int leftSiblingId = INVALID_NODE_ID;
	list<int>::iterator childIdIterator = childIds.begin();
	while(childIdIterator != childIds.end()) {
		currentId = (int) *childIdIterator;
		if(currentId == id) {
			childIdIterator++;
			if(childIdIterator != childIds.end()) {
				leftSiblingId = *childIdIterator;
			}
			return leftSiblingId;
		}
		childIdIterator++;
	}
	return leftSiblingId;
}

void InternalNode::serialize(iostream* ios)
{

	/* Se serializara:
	 * <Nivel><IdNodo><CantidadClaves>[<SizeClave><Clave>]...[<SizeClave><Clave>]<idHijo>...<idHijo>
	 * */
	int hijoAux = 0;
	int sizeClave = 0;
	int cantidadClaves = this->keys.size();
	string claveAux;

	ios->write(reinterpret_cast<char *>(&(level)), sizeof(level));//nivel
	ios->write(reinterpret_cast<char *>(&(nodeId)), sizeof(nodeId));//idNodo
	ios->write(reinterpret_cast<char *>(&cantidadClaves), sizeof(cantidadClaves));//cantidadClaves

	//se serializan las claves
	list<string> claves = this->keys;
	for (list<string>::const_iterator ci = claves.begin(); ci != claves.end(); ++ci)
	{
		claveAux = *ci;
		sizeClave = claveAux.size();
		ios->write(reinterpret_cast<char *>(&sizeClave), sizeof(sizeClave));//sizeClave
		ios->write(claveAux.c_str(), sizeClave);//clave
	}


	list<int> hijos = this->childIds;
	for (list<int>::const_iterator ci = hijos.begin(); ci != hijos.end(); ++ci)
	{
		hijoAux = *ci;
		ios->write(reinterpret_cast<char *>(&hijoAux), sizeof(hijoAux));//hijo
	}
}

void InternalNode::deserialize(iostream* ios)
{
	/* Se serializara:
	 * <Nivel><IdNodo><CantidadClaves>[<SizeClave><Clave>]...[<SizeClave><Clave>]<idHijo>...<idHijo>
	 * */
	int sizeClave =0, cantidadClaves = 0, hijo= 0;
	char* claveAux;
	string clave="";


	//el nivel se carga desde afuera
	//ios->read(reinterpret_cast<char *>(&(level)), sizeof(level));//nivel
	ios->read(reinterpret_cast<char *>(&(nodeId)), sizeof(nodeId));//idNodo
	ios->read(reinterpret_cast<char *>(&cantidadClaves), sizeof(cantidadClaves));//cantidadClaves

	for(int i =0; i < cantidadClaves; i++)
	{
		ios->read(reinterpret_cast<char *>(&sizeClave), sizeof(sizeClave));//sizeClave
		claveAux = new char[sizeClave];
		ios->read(claveAux, sizeClave);//clave

		clave.assign(claveAux,sizeClave);


		this->keys.push_back(clave);

		delete[] claveAux;

	}

	if (cantidadClaves != 0)
	{
		for(int i =0; i <= cantidadClaves; i++)
		{
			ios->read(reinterpret_cast<char *>(&hijo), sizeof(hijo));//sizeClave
			this->childIds.push_back(hijo);
		}
	}
}

int InternalNode::getCtrlDataSize(){
	int ctrlDataSize = 0;
	ctrlDataSize += sizeof(level);
	ctrlDataSize += sizeof(nodeId);
	ctrlDataSize += sizeof(int); // Este último int representa la cantidad de claves.

	return  ctrlDataSize;
}

long InternalNode::getDataSize() {
	long dataSize = 0;
	dataSize += sizeof(int) * keys.size(); // Sumo el tamaño de la metadata para cada clave que guarda.
	dataSize += sizeof(int) * childIds.size(); // Sumo el tamaño de las referencias que guarda.

	list<string>::const_iterator ci = this->keys.begin();
	while(ci != this->keys.end())
	{
		dataSize += (*ci).length();//sumo el tamanio de las claves que guarda
		++ci;
	}


	return dataSize;
}

long InternalNode::getFreeDataSizeOnLeft(){
	//TODO check minSize calculation.

	long minSize = (BLOCKSIZE - getCtrlDataSize()) * MIN_PERCENTAGE;
	long freeDataSize = 0;

	int pareSize = 2*sizeof(int);

	while(getDataSize()-freeDataSize > minSize ){
		freeDataSize += pareSize;
	}

	if(freeDataSize ==0 )
		return freeDataSize;

	return freeDataSize - pareSize;
}

long InternalNode::getFreeDataSizeOnRight(){
	//TODO check minSize calculation.
	long minSize = (BLOCKSIZE - getCtrlDataSize()) * MIN_PERCENTAGE;
	long freeDataSize = 0;
	int pareSize = 2*sizeof(int);

	while(getDataSize()-freeDataSize > minSize ){
		freeDataSize += pareSize;
	}

	if(freeDataSize ==0 )
		return freeDataSize;

	return freeDataSize - pareSize;
}

long InternalNode::getSize() {
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
bool InternalNode::isOverFlowded(int blockSize) {
	return (getDataSize() > (BLOCKSIZE-getCtrlDataSize())*MAX_PERCENTAGE  );
}

bool InternalNode::isUnderFlowded(int blockSize) {
	return (getDataSize()< (BLOCKSIZE-getCtrlDataSize())*MIN_PERCENTAGE);
}

void InternalNode::toString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs){
	string tabs = setTabs(rootLevel - this->level);

	string keys = "";
	string ids = "";
	stringstream ss;
	ss.str("");

	list<string>::const_iterator it_keys = this->keys.begin();
	//begin front coding
	list<string*>* frontDecodedStrings = new list<string*>();
	FrontCodedString* fcs = new FrontCodedString();
	while (it_keys != this->keys.end())
	{
		frontDecodedStrings->push_back(new string(*it_keys));
		it_keys++;
	}
	list<FrontCodedString*>* frontCodedStrings = fcs->frontCode(frontDecodedStrings);
	list<FrontCodedString*>::const_iterator ci;
	for(ci = frontCodedStrings->begin();ci != frontCodedStrings->end();++ci){
		ss << "(" << ((*ci)->getCantidadLetrasPalabraAnterior()) << ")";
		ss << "(" << ((*ci)->getCantidadLetrasPalabraActual()) << ")";
		ss << ((*ci)->getPalabraEncodeada());
		delete (*ci);
	}
	delete (fcs);
	delete (frontDecodedStrings);
	delete (frontCodedStrings);
	
	//end front coding

	/*
	while (it_keys != this->keys.end())
	{
		ss << "(" << (*it_keys) << ")";
		it_keys++;
	}
	*/
	keys = ss.str();

	ss.str("");

	list<int>::const_iterator it_ids = this->childIds.begin();
	while (it_ids != this->childIds.end()){
		ss << "(" << (*it_ids) << ")";
		it_ids++;
	}

	ids = ss.str();

	(*ios) << tabs << "|----- [node id= [" << getNodeId() << "] level=[" << getLevel()
				 << "] keys=[" << keys << "] ids=[" << ids <<  "]  nodeSize=["
				 			<< this->getSize() << "] controlDataSize=[" << this->getCtrlDataSize()
				 			<< "]  nodeDataSize=[" << this->getDataSize() << "] ]" << endl;
	nodesToString(ios, rootLevel, sizeOffset, fs);

}

void InternalNode::toStringXML(iostream* ios, int rootLevel, int sizeOffset, fstream* fs){

}


void InternalNode::nodesToString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs)
{
	list<int>::iterator it = this->childIds.begin();
	while (it != this->childIds.end())
	{
		Node* pNode = NodeFactory::readNode(*it, sizeOffset, fs);
		pNode->toString(ios, rootLevel, sizeOffset, fs);
		it++;
		delete pNode;
	}
}

void InternalNode::nodesToStringXML(iostream* ios, int rootLevel, int sizeOffset, fstream* fs){

}


string InternalNode::getMaxKey(){
	return (string)keys.back();
}

string InternalNode::getMinKey(){
	return (string)keys.front();
}

// This method try to redistribute data between the node and its siblings
int InternalNode::tryRotate(Node* leftSibling, Node* node, Node* rightSibling){

	long minSize = (BLOCKSIZE - node->getCtrlDataSize()) * MIN_PERCENTAGE;
	long maxSize = (BLOCKSIZE - node->getCtrlDataSize()) * MAX_PERCENTAGE;


	//Check if it is ever possible to rotate
	long freeSize = 0;
	freeSize += node->getDataSize();

	if(leftSibling != NULL)
	{
		freeSize += leftSibling->getFreeDataSizeOnRight();
	}
	if(rightSibling != NULL)
	{
		freeSize += rightSibling->getFreeDataSizeOnLeft();
	}

	// If free data is insufficient, rotate fails!
	if(freeSize < minSize){
		return EXIT_FAILURE;
	}
	// It's possible to rotate
	if(leftSibling != NULL)
		leftSibling->moveDataToRight(this, node, minSize, maxSize);

	if(!node->isUnderFlowded(BLOCKSIZE)){
		return EXIT_SUCCESS;
	}
	// Node is still underflowed, rotate again!
	if(rightSibling != NULL)
		rightSibling->moveDataToLeft(this, node, minSize, maxSize);

	// Next to the last rotation node should be left balanced.
	return EXIT_SUCCESS;
}

int InternalNode::merge(Node* leftSibling, Node* node, Node* rightSibling){

	long maxSize = (BLOCKSIZE - getCtrlDataSize()) * MAX_PERCENTAGE;

	if(leftSibling == NULL || rightSibling == NULL)
		maxSize = BLOCKSIZE*2;

	// Trying to merge with left sibling if there is one.
	if(leftSibling != NULL){
		node->moveDataToLeft(this, leftSibling, 0, maxSize);
	}
	//If there is right sibling and still some data left, trying to merge with right sibling.
	if(rightSibling != NULL && node->getDataSize()>0)
		node->moveDataToRight(this, rightSibling, 0, maxSize);

	//Next to the last merge node should be left empty.
	return EXIT_SUCCESS;
}



