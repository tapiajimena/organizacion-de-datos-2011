/*
 * InternalNode.cpp
 *
 *  Created on: Apr 10, 2010
 *      Author: juane
 */

#include "InternalNode.h"
#include "NodeFactory.h"

InternalNode::InternalNode() {

}

InternalNode::~InternalNode() {
	keys.clear();
	childIds.clear();
}

void InternalNode::split(Node* sibling, int blockSize, int* promotedKey, int* promotedNodeID) {
	InternalNode* siblingInternalNode = (InternalNode*)sibling;

	list<int>::iterator itKey = this->keys.begin();
	list<int>::iterator itChildID = this->childIds.begin();

	int currentKey=0, currentChildID=0;
	int nodeSizeAccumulator = 0;
	int halfSizeOfCurrentNode = getDataSize()/2;

	while (itKey != this->keys.end()) {
		currentKey= (int)*itKey;
		currentChildID = (int)*itChildID;

		if (nodeSizeAccumulator > halfSizeOfCurrentNode){
			siblingInternalNode->insertKeyToList((int)*itKey);  // el listado original ya esta ordenado, con mandarlo al final alcanza
			siblingInternalNode->insertChildIDToList((int)*itChildID);  // el listado original ya esta ordenado, con mandarlo al final alcanza
			itKey = keys.erase(itKey);
			itChildID = childIds.erase(itChildID);
		}
		else {
			itKey++;
			itChildID++;
		}

		nodeSizeAccumulator += sizeof(currentKey) + sizeof(currentChildID);
	}
	siblingInternalNode->insertChildIDToList((int)*itChildID);
	childIds.erase(itChildID);

	*promotedKey = this->getMaxKey();
	*promotedNodeID = siblingInternalNode->getNodeId();
	itKey--;
	keys.erase(itKey);
}

void InternalNode::insertKeyToList(int key){
	this->keys.push_back(key);
}

void InternalNode::insertKeyInOrderToList(int key){
	this->keys.push_back(key);
	this->keys.sort();
}

void InternalNode::insertChildIDToList(int childID){
	this->childIds.push_back(childID);
}

int InternalNode::insert(Record* record) {
}

int InternalNode::remove(Record* record, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter) {
	int childNodeId = findLocation(record);
	Node* node = NodeFactory::readNode(childNodeId, sizeOffset, fs);

	int result = node->remove(record, sizeOffset, fs, nodeCounter, freefs, freeNodeCounter);

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

	int keyToPromote = keys.front();

	while (2*sizeof(int) + internalNodeToMoveData->getDataSize() <= toDataLimit
			&& this->getDataSize() - 2*sizeof(int)   >= fromDataLimit) {

		//Promote the key
		if(keys.size()>0){
			keyToPromote = keys.front();

			int previousKey = parentNode->getKeyMinorEqualTo(keyToPromote);
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

	int keyToPromote = keys.back();

	while (2*sizeof(int) + internalNodeToMoveData->getDataSize() <= toDataLimit
			&& this->getDataSize() - 2*sizeof(int)   >= fromDataLimit) {

		if(keys.size() >0){
			keyToPromote = keys.back();

			//Promote the key
			int previousKey = parentNode->getKeyMajorEqualTo(keyToPromote);
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
			int keyToPromote = parentNode->getKeyMinorTo(nodeToMoveData->getMinKey());

			parentNode->getKeys()->remove(keyToPromote);

			//Move childId and key
			internalNodeToMoveData->getChildIds()->push_front(childId);
			internalNodeToMoveData->getKeys()->push_front(keyToPromote);

			childIds.remove(childId);
		}
	}
}

int InternalNode::getKeyMinorEqualTo(int key){

	list<int>::iterator itKeys=keys.end();

	do{
		itKeys--;
		if(*itKeys <= key){
			return *itKeys;
		}
	}
	while(itKeys != keys.begin());
	return key;
}

int InternalNode::getKeyMinorTo(int key){

	list<int>::iterator itKeys=keys.end();

	do{
		itKeys--;
		if(*itKeys < key){
			return *itKeys;
		}
	}
	while(itKeys != keys.begin());
	return key;
}

int InternalNode::getKeyMajorEqualTo(int key){

	for (list<int>::iterator itKeys=keys.begin(); itKeys!=keys.end(); ++itKeys){
		if(*itKeys >= key){
			return *itKeys;
		}
	}
	return key;
}


Record* InternalNode::find(Record* record) {
}

int InternalNode::resolveOverflow(Node* node, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter){

	Node* newNode;
	if(node->getLevel() > 0)
		newNode = new InternalNode();
	else
		newNode = new LeafNode();

	NodeFactory::assignNodeId(newNode, nodeCounter, freeNodeCounter, freefs);
	newNode->setLevel(node->getLevel());


	list<int>::iterator keyIterator = keys.begin();
	list<int>::iterator childIterator = childIds.begin();

	int a;
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

/* Devuelve el id del hijo en el cual hay que buscar el registro recibido. */

list<int>* InternalNode::getKeys() {
	return &keys;
}

list<int>* InternalNode::getChildIds() {
	return &childIds;
}

void InternalNode::insertKeyChild(int key, int childId) {
	int currentKey;

	list<int>::iterator keyIterator = keys.begin();
	list<int>::iterator childIterator = childIds.begin();

	while (keyIterator != keys.end()) {

		currentKey = (int) *keyIterator;
		if (key < currentKey) {
			break;
		}
		keyIterator++;
		childIterator++;
	}

	keys.insert(keyIterator, key);

	childIterator++;
	childIds.insert(childIterator, childId);
}

int InternalNode::findLocation(Record* record) {
	int currentKey;
	int locationId = 0;
	list<int>::iterator keyIterator = keys.begin();
	list<int>::iterator childIterator = childIds.begin();

	while (keyIterator != keys.end()) {
		currentKey = (int) *keyIterator;
		Record* auxRecord = new Record(currentKey);
		if (record->compareTo(auxRecord) != 1) {
			locationId = *childIterator;
			delete auxRecord;
			return locationId;
		}
		delete auxRecord;
		keyIterator++;
		childIterator++;
	}

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

void InternalNode::serialize(iostream* ios) {
	/* Serialización de InternalNode:
	 * <Nivel><Id><CantKeys><Key>...<Key><ChildId>...<ChildId>*/

	int keyCount = keys.size();
	stringstream ss;
	ss << keyCount;
	int key, childId;

	list<int>::iterator keyIterator;
	list<int>::iterator childIdIterator;

	(*ios).write(reinterpret_cast<char *> (&level), sizeof(int));
	(*ios).write(reinterpret_cast<char *> (&nodeId), sizeof(int));
	(*ios).write(reinterpret_cast<char *> (&keyCount), sizeof(int));

	for (keyIterator = keys.begin(); keyIterator != keys.end(); keyIterator++) {
		key = (int) *keyIterator;
		(*ios).write(reinterpret_cast<char *> (&key), sizeof(int));
	}

	for (childIdIterator = childIds.begin(); childIdIterator != childIds.end(); childIdIterator++) {
		childId = (int) *childIdIterator;
		(*ios).write(reinterpret_cast<char *> (&childId), sizeof(int));
	}
}

void InternalNode::deserialize(iostream* ios) {
	/* Deserialización de InternalNode:
	 * Se carga de acuerdo a cómo está serializado, excepto por el nivel, que se lee desde afuera*/
	int keyCount;
	int currentKey;
	int currentChildId;

	(*ios).read(reinterpret_cast<char *> (&nodeId), sizeof(int));
	(*ios).read(reinterpret_cast<char *> (&keyCount), sizeof(int));
	stringstream ss;
	ss << keyCount;

	for (int i = 0; i < keyCount; i++) {
		(*ios).read(reinterpret_cast<char *> (&currentKey), sizeof(currentKey));
		keys.push_back(currentKey);
	}

	for (int i = 0; i < (keyCount + 1); i++) {
		(*ios).read(reinterpret_cast<char *> (&currentChildId),	sizeof(currentChildId));
		childIds.push_back(currentChildId);
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
	dataSize += sizeof(int) * keys.size(); // Sumo el tamaño de las claves que guarda.
	dataSize += sizeof(int) * childIds.size(); // Sumo el tamaño de las referencias que guarda.

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
	list<int>::iterator it = this->keys.begin();
	stringstream ss;
	ss.str("");
	while (it != this->keys.end())
	{
		ss << (*it) << ",";
		it++;
	}
	keys = ss.str();

	it = this->childIds.begin();
	ss.str("");
	while (it != this->childIds.end()){
		ss << (*it) << ",";
		it++;
	}

	string ids = ss.str();

	(*ios) << tabs << "|----- [node id= [" << getNodeId() << "] level=[" << getLevel()
				 << "] keys=[" << keys << "] ids=[" << ids  <<  "]  nodeSize=["
				 			<< this->getSize() << "] controlDataSize=[" << this->getCtrlDataSize()
				 			<< "]  nodeDataSize=[" << this->getDataSize() << "] ]" << endl;
	nodesToString(ios, rootLevel, sizeOffset, fs);
}

void InternalNode::toStringXML(iostream* ios, int rootLevel, int sizeOffset, fstream* fs){
	string tabs = setTabsXML(rootLevel - this->level);

	string keys = "";
	list<int>::iterator it = this->keys.begin();
	stringstream ss;
	ss.str("");
	while (it != this->keys.end())
	{
		ss << (*it) << ",";
		it++;
	}
	keys = ss.str();
	it = this->childIds.begin();
	ss.str("");
	while (it != this->childIds.end())
	{
		ss << (*it) << ",";
		it++;
	}

	string ids = ss.str();

	(*ios) << tabs << "<node id=\"" << getNodeId() << "\" level=\"" << getLevel()
			<< "\" keys=\"" << keys << "\" ids=\"" << ids  <<  "\" nodeSize=\""
			<< this->getSize() << "\" controlDataSize=\"" << this->getCtrlDataSize()
			<< "\"  nodeDataSize=\"" << this->getDataSize() << "\" >" << endl;
	nodesToStringXML(ios, rootLevel, sizeOffset, fs);
	(*ios) << tabs << "</node>" << endl;
}


void InternalNode::nodesToString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs){
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
	list<int>::iterator it = this->childIds.begin();
	while (it != this->childIds.end())
	{
		Node* pNode = NodeFactory::readNode(*it, sizeOffset, fs);
		pNode->toStringXML(ios, rootLevel, sizeOffset, fs);
		it++;
		delete pNode;
	}
}


int InternalNode::getMaxKey(){
	return (int)keys.back();
}

int InternalNode::getMinKey(){
	return (int)keys.front();
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

