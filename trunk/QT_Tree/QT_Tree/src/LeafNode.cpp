/*
 * LeafNode.cpp
 *
 *  Created on: 27/03/2010
 *      Author: marcelo
 */

#include "LeafNode.h"

using namespace std;

LeafNode::LeafNode() {
	level = 0;
	nextLeafNodeId = INVALID_NODE_ID;
}



LeafNode::LeafNode(list<Record*> records, int nextLeafNodeId) {
	this->records = records;
	this->nextLeafNodeId = nextLeafNodeId;
}

LeafNode::~LeafNode() {
	list<Record*>::iterator it = records.begin();
	while (it != records.end()) {
		delete (Record*)*it;
		it++;
	}
	records.clear();
}

LeafNode* LeafNode::clone(){
	return new LeafNode(this->records,this->nextLeafNodeId);
}

void LeafNode::split(Node* sibling, int blockSize, int* promotedKey, int* promotedNodeID) {
	LeafNode* siblingLeafNode = (LeafNode*)sibling;
	list<Record*>::iterator it = records.begin();
	Record* currentRecord = NULL;
	int recordsSizeAccumulator = 0;
	int halfSizeOfCurrentNode = getDataSize()/2;

	while (it != records.end()) {
		currentRecord = (Record*) *it;
		if (recordsSizeAccumulator > halfSizeOfCurrentNode){
			siblingLeafNode->insert(currentRecord);
			it = records.erase(it);
		} else {
			it++;
		}
		recordsSizeAccumulator += currentRecord->getSize(); // En este caso, como el Registro esta contenido
															// dentro del LeafNode, debo considerar la data de control tambien, por lo que llamo a getSize()
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
	LeafNode* siblingLeafNode = (LeafNode*)sibling;
	list<Record*> commonContent;

	list<Record*>::iterator it = records.begin();
	Record* currentRecord = NULL;
	while (it != records.end()) {
		currentRecord = (Record*) *it;
		commonContent.push_back(currentRecord);
		it = records.erase(it);
	}

	it = siblingLeafNode->getRecords()->begin();
	while (it != siblingLeafNode->getRecords()->end()) {
		currentRecord = (Record*) *it;
		commonContent.push_back(currentRecord);
		it = siblingLeafNode->getRecords()->erase(it);
	}

	long commonContentSize = this->getDataSize() + siblingLeafNode->getDataSize();
	long recordsSize = 0;

	it = commonContent.begin();
	while (it != commonContent.end()) {
		currentRecord = (Record*) *it;
		recordsSize += currentRecord->getSize();
		if (recordsSize < (commonContentSize)/2){
			this->insert(currentRecord);
		} else {
			siblingLeafNode->insert(currentRecord);
		}
		it = commonContent.erase(it);
	}
}

int LeafNode::insert(Record* record) {
	if (recordIndex(record)==-1){
		records.push_front(record);
		records.sort(&LeafNode::compareRecords);
		if (isOverFlowded(BLOCKSIZE)) {
			return OVERFLOWDED;
		}
		return EXIT_SUCCESS;
	} else return DUPLICATED;
}

bool LeafNode::compareRecords(Record* r1, Record* r2) {
	if (r1->compareTo((void*) r2) == -1)
		return true;
	else
		return false;
}

int LeafNode::remove(Record* record, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter) {
	list<Record*>::iterator it = records.begin();
	int comparison;
	Record* currentRecord = NULL;

	while (it != this->records.end()) {
		currentRecord = (Record*) *it;
		comparison = record->compareTo((void*) currentRecord);
		switch (comparison) {
		case -1:
			return EXIT_FAILURE;
		case 0:
			records.erase(it);
			delete (Record*)*it;

			if(isUnderFlowded(BLOCKSIZE)) {
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

void LeafNode::moveDataToLeft(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit){

	if(records.size() == 0){
		int orphanKey = parentNode->getKeyMajorEqualTo(nodeToMoveData->getMaxKey());
		parentNode->getKeys()->remove(orphanKey);
		return;
	}

	LeafNode* leafNodeToMoveData = (LeafNode*) nodeToMoveData;

	Record* record = records.front();
	int recordSize = record->getSize();

	while (recordSize + nodeToMoveData->getDataSize() <= toDataLimit
			&& this->getDataSize() - recordSize >= fromDataLimit) {

		records.remove(record);
		//Move one record
		leafNodeToMoveData->getRecords()->push_back(record);

		int previousKey = parentNode->getKeyMinorTo(record->getKey());
		parentNode->getKeys()->remove(previousKey);

		if(records.size() == 0)
			break;

		//Promote the key
		parentNode->insertKeyInOrderToList(record->getKey());

		record = records.front();
		recordSize = record->getSize();

	}
}

void LeafNode::moveDataToRight(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit){

	if(records.size() == 0){
		int orphanKey = parentNode->getKeyMinorEqualTo(nodeToMoveData->getMinKey());
		parentNode->getKeys()->remove(orphanKey);

		return;
	}
	LeafNode* leafNodeToMoveData = (LeafNode*) nodeToMoveData;



	Record* record = records.back();
	int recordSize = record->getSize();

	while (recordSize + nodeToMoveData->getDataSize() <= toDataLimit
			&& this->getDataSize() - recordSize >= fromDataLimit) {

		records.remove(record);
		//Move one record
		leafNodeToMoveData->getRecords()->push_front(record);
		int previousKey = parentNode->getKeyMajorEqualTo(record->getKey());
		parentNode->getKeys()->remove(previousKey);

		if(records.size() == 0)
			break;

		record = records.back();

		//Promote the key
		parentNode->insertKeyInOrderToList(record->getKey());
		recordSize = record->getSize();
	}
}


int LeafNode::modify(Record* record) {
	list<Record*>::iterator it = records.begin();
	int comparison;
	long newSize;
	bool overflowded;
	Record* currentRecord = NULL;
	stringstream ss(ios_base::in| ios_base::out| ios_base::binary);
	while (it != this->records.end()) {
		currentRecord = (Record*) *it;
		comparison = record->compareTo((void*) currentRecord);
		switch (comparison) {
		case -1:
			return NOT_FOUNDED;
		case 0:
			newSize = (getDataSize() - currentRecord->getSize() + record->getSize());
			overflowded = newSize > (BLOCKSIZE - getCtrlDataSize())*MAX_PERCENTAGE;
			if(overflowded) {
				return OVERFLOWDED;
			}
			ss.write(record->getData(),record->getDataSize());
			currentRecord->edit(record->getKey(),&ss);
			if (isUnderFlowded(BLOCKSIZE)){
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

Record* LeafNode::find(Record* record) {
	list<Record*>::iterator it;
	Record* currentRecord = NULL;

	if(records.empty()) {
		return NULL;
	}

	it = records.begin();
	while (it != records.end()) {
		currentRecord = (Record*) *it;
		if (record->compareTo((void*) currentRecord) <= 0) {
			break;
		}
		it++;
	}
	return currentRecord;
}

list<int> LeafNode::getKeys(){
}

void LeafNode::serialize(iostream* ios) {
	/* Serialización de LeafNode:
	 * <Tipo><Id><Nivel><CantRegistros><Registro>...<Registro><SiguienteHoja>*/
	int recordCount = records.size();
	Record* rec = NULL;
	(*ios).write(reinterpret_cast<char *> (&level), sizeof(int));
	(*ios).write(reinterpret_cast<char *> (&nodeId), sizeof(int));

	(*ios).write(reinterpret_cast<char *> (&recordCount), sizeof(int));
	list<Record*>::iterator it;
	for (it = records.begin(); it != records.end(); it++) {
		rec = (Record*) *it;
		rec->serialize(ios);
	}
	(*ios).write(reinterpret_cast<char *> (&nextLeafNodeId), sizeof(int));
}

void LeafNode::deserialize(iostream* ios) {
	/* Deserialización de LeafNode:
	 * Se carga de acuerdo a cómo está serializado, excepto por el tipo, que se lee desde afuera*/
	int recordCount;
	(*ios).read(reinterpret_cast<char *> (&nodeId), sizeof(int));
	(*ios).read(reinterpret_cast<char *> (&recordCount), sizeof(int));
	for (int i = 0; i < recordCount; i++){
		Record* auxRecord = new Record();
		auxRecord->deserialize(ios);
		records.push_back(auxRecord);
 	}
	(*ios).read(reinterpret_cast<char *> (&(this->nextLeafNodeId)), sizeof(int));
}

list<Record*>* LeafNode::getRecords() {
	return &records;
}

void LeafNode::setNextLeafNodeId(int nextLeaf) {
	this->nextLeafNodeId=nextLeaf;
}


void LeafNode::readRecords() {
}

int LeafNode::getNextLeafNodeId() {
	return this->nextLeafNodeId;
}

/**
 * If the Record exists, returns the index position of the record inside the Node's list of records.
 * If the Record does not exist, returns -1
 */
int LeafNode::recordIndex(Record* record) {
	list<Record*>::iterator it = records.begin();
	int comparison, counter = 0;
	Record* currentRecord = NULL;
	while (it != this->records.end()) {
		currentRecord = (Record*) *it;
		comparison = record->compareTo((void*) currentRecord);
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

	return  ctrlDataSize;
}

long LeafNode::getDataSize() {
	// Sumo el tamaño de los registros que contiene.
	long dataSize = 0;
	Record* rec;
	for (list<Record*>::iterator it = records.begin(); it != records.end(); it++) {
		rec = (Record*) *it;
		dataSize += rec->getSize();
	}
	return dataSize;
}

long LeafNode::getFreeDataSizeOnRight(){
	long minSize = (BLOCKSIZE - getCtrlDataSize()) * MIN_PERCENTAGE;
	long freeDataSize = 0;
	long dataSize = 0;


	for (list<Record*>::iterator it = records.begin(); it != records.end(); it++) {
		Record* rec = (Record*) *it;
		if(dataSize >= minSize)
			freeDataSize += rec->getSize();
		dataSize += rec->getSize();
	}
	return freeDataSize;
}

long LeafNode::getFreeDataSizeOnLeft(){
	long minSize = (BLOCKSIZE - getCtrlDataSize()) * MIN_PERCENTAGE;
	long freeDataSize = 0;
	long dataSize = 0;

	list<Record*>::iterator it = records.begin();

	for (list<Record*>::iterator it = records.begin(); it != records.end(); it++) {
		Record* rec = (Record*) *it;
		if(getDataSize() - dataSize > minSize)
			freeDataSize += rec->getSize();
		dataSize += rec->getSize();
	}

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
bool LeafNode::isOverFlowded(int blockSize){
	return (getDataSize()>(BLOCKSIZE-getCtrlDataSize())*MAX_PERCENTAGE);
}

bool LeafNode::isUnderFlowded(int blockSize){
	return (getDataSize()<(BLOCKSIZE-getCtrlDataSize())*MIN_PERCENTAGE);
}

int LeafNode::getMaxKey(){
	return ((Record *)this->records.back())->getKey();
}

int LeafNode::getMinKey(){
	return ((Record *)this->records.front())->getKey();
}

void LeafNode::toStringXML(iostream* ios, int rootLevel, int sizeOffset, fstream* fs){
	string tabs = setTabsXML(rootLevel - this->level);

	(*ios) << tabs << "<node id=\"" << getNodeId() << "\" level=\"" << getLevel()
				<<  "\" nodeSize=\"" << this->getSize() << "\" controlDataSize=\"" << this->getCtrlDataSize()
				<< "\"  nodeDataSize=\"" << this->getDataSize() << "\" >" << endl;

	recordsToStringXML(ios, rootLevel);
	(*ios) << tabs << "</node>" << endl;
}

void LeafNode::toString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs){
	string tabs = setTabs(rootLevel - this->level);

	(*ios) << tabs << "|----- [node id=[" << getNodeId() << "] level=[" << getLevel() << "] nodeSize=["
					 			<< this->getSize() << "] controlDataSize=[" << this->getCtrlDataSize()
					 			<< "]  nodeDataSize=[" << this->getDataSize() << "] ]" << endl;
 	recordsToString(ios, rootLevel);
}

void LeafNode::recordsToString(iostream* ios, int rootLevel){
	list<Record*>::iterator it = this->records.begin();
	while (it != this->records.end())
	{
		Record* pRecord = *it;
		pRecord->toString(ios, rootLevel);
		it++;
	}
}

void LeafNode::recordsToStringXML(iostream* ios, int rootLevel){
	list<Record*>::iterator it = this->records.begin();
	while (it != this->records.end())
	{
		Record* pRecord = *it;
		pRecord->toStringXML(ios, rootLevel);
		it++;
	}
}

