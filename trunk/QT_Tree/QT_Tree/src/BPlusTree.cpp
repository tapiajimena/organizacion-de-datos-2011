/*
 * BPlusTree.cpp
 *
 *  Created on: 27/03/2010
 *      Author: marcelo
 */

#include "BPlusTree.h"
#include "BPlusTree_CONST.h"

BPlusTree::BPlusTree(){
}

BPlusTree::BPlusTree(string fileName, long blockSize){
	this->fileName=fileName;
	this->blockSize=blockSize;
	this->controlDataSize= sizeof(long) + 3* sizeof(unsigned int); //long: blockSize unsigned int: recordCounter, nodeCounter, freeNodeCounter
	if (FileManager::fileExists(fileName)){ // si el archivo existe
		FileManager::openFile(&file, fileName);  // abre el archivo
		FileManager::openFile(&freeNodesFile, getFreeNodesFileName(fileName));
		if (this->readControlData() == EXIT_SUCCESS) {// si pudo leer el header
			root = readNode(0);	//lee y carga la raiz, del primer bloque del archivo
		} else {
			exit (EXIT_FAILURE);
		}
	} else {
		if (FileManager::createFile(&file, fileName)){
			FileManager::createFile(&freeNodesFile, getFreeNodesFileName(fileName));
			root = new LeafNode();
			root->setNodeId(0);
			nodeCounter = 1;
			freeNodeCounter = 0;
			writeControlData();
			writeNode(root);
		}
	}
}


BPlusTree::~BPlusTree(){
	writeControlData();
	FileManager::closeFile(&file);
	FileManager::closeFile(&freeNodesFile);
	delete this->root;
}

int BPlusTree::readControlData(){
	stringstream iosCtrlData(ios_base::in| ios_base::out| ios_base::binary);
	bool readData = false;
	readData = FileManager::readData(&file,0,controlDataSize,&iosCtrlData);
	if (readData){
		(iosCtrlData).read( reinterpret_cast<char *>(&blockSize), sizeof(blockSize));
		(iosCtrlData).read( reinterpret_cast<char *>(&nodeCounter), sizeof(nodeCounter));
		(iosCtrlData).read( reinterpret_cast<char *>(&freeNodeCounter), sizeof(freeNodeCounter));
		(iosCtrlData).read( reinterpret_cast<char *>(&recordCounter), sizeof(recordCounter));
		return EXIT_SUCCESS;
	}else {
		return EXIT_FAILURE;
	}
}

int BPlusTree::writeControlData(){
	/* Datos de control del árbol:
	 * <TamBloque><CantNodos><CantNodosLibres><CantRegistros> */
	stringstream iosCtrlData(ios_base::in| ios_base::out| ios_base::binary);
	(iosCtrlData).write(reinterpret_cast<char *>(&blockSize),sizeof(blockSize));
	(iosCtrlData).write(reinterpret_cast<char *>(&nodeCounter),sizeof(nodeCounter));
	(iosCtrlData).write(reinterpret_cast<char *>(&freeNodeCounter),sizeof(freeNodeCounter));
	(iosCtrlData).write(reinterpret_cast<char *>(&recordCounter),sizeof(recordCounter));
	if (FileManager::writeData(&file,0,controlDataSize,&iosCtrlData)){
			return EXIT_SUCCESS;
	} else {
			return EXIT_FAILURE;
	}
}

Node* BPlusTree::getRoot(){
	if (root==NULL)
		root = new LeafNode();
	return root;
}

int BPlusTree::insert(Record* record) {
	int result, promotedKey, promotedNodeId;

	if(record->getSize() > getMaxRecordSize()) {
		return EXIT_FAILURE;
	}

	result = recursiveInsert(record, root, &promotedKey, &promotedNodeId);
	if(result == OVERFLOWDED) { // Si se desborda la raíz...
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
	return result;
}

int BPlusTree::recursiveInsert(Record* record, Node* currentNode, int* promotedKey, int* promotedNodeId) {
	int result;
	Node* newNode = NULL;
	if (currentNode->getLevel() == 0) { // Es un LeafNode
		result = currentNode->insert(record);

		if (result == EXIT_SUCCESS) {
			writeNode(currentNode);
		} else if (result == OVERFLOWDED) {
			newNode = new LeafNode();
			NodeFactory::assignNodeId(newNode,&nodeCounter,&freeNodeCounter,&freeNodesFile);
			currentNode->split(newNode, BLOCKSIZE, promotedKey, promotedNodeId);
			writeNode(currentNode);
			writeNode(newNode);

			delete(newNode);
			return OVERFLOWDED;
		} else if (result == DUPLICATED) {
			return result;
		}
		return EXIT_SUCCESS;
	} else { // Es un InternalNode
		InternalNode* inner = (InternalNode*) currentNode;
		int locationId = inner->findLocation(record);

		Node* nextNode = readNode(locationId);
		result = recursiveInsert(record, nextNode, promotedKey, promotedNodeId);

		if (result == OVERFLOWDED) {
			inner->insertKeyChild(*promotedKey, *promotedNodeId);
			if (inner->isOverFlowded(BLOCKSIZE)) { // Si luego de insertar el "registrito" quedo en overflow
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
		} else {
			delete(nextNode);
			return result;
		}
	}
}

int BPlusTree::remove(Record* record){
	int result = this->root->remove(record, this->controlDataSize, &this->file, &nodeCounter, &freeNodesFile, &freeNodeCounter );

	if(this->root->getLevel() > 0){
		InternalNode* root = (InternalNode*)this->root;
		if(root->getChildIds()->size()==1)
		{
			int newRootId = root->getChildIds()->front();
			NodeFactory::addFreeNodeId(newRootId,&freeNodeCounter,&freeNodesFile);

			Node* newRoot = readNode(newRootId);
			newRoot->setNodeId(0);
			delete(this->root);
			this->root = newRoot;
			writeNode(this->root);
		}
	}

	this->writeNode(this->root);
	return result;
}

Record* BPlusTree::find(Record* record){
	return recursiveSearch(record, root);
}

Record* BPlusTree::recursiveSearch(Record* record, Node* node){
	InternalNode* inner;
	Record* auxRecord;
	if(node->getLevel()==0){
		auxRecord = node->find(record);
		return auxRecord->clone();
	} else {
		inner = (InternalNode*) node;
		int locationId = inner->findLocation(record);
		Node* nextNode = readNode(locationId);
		auxRecord = recursiveSearch(record, nextNode);
		delete(nextNode);
		return auxRecord;
	}
}

void BPlusTree::dump(string dumpFileName){
	fstream dumpFile;

	FileManager::createFile(&dumpFile, dumpFileName);

	(dumpFile) << "[B+Tree controlDataSize=[" << this->controlDataSize << "] blockSize=[" << BLOCKSIZE
			<< "] nodeCounter=[" << this->nodeCounter << "] freeNodeCounter=[" << this->freeNodeCounter << "] ]"
			<< endl;

	this->root->toString(&dumpFile, this->root->getLevel(), this->controlDataSize, &this->file);
	FileManager::closeFile(&dumpFile);
}

void BPlusTree::dumpToXML(string dumpFileName){
	fstream dumpFile;

	FileManager::createFile(&dumpFile, dumpFileName);

	(dumpFile) << "<BPlusTree controlDataSize=\"" << this->controlDataSize << "\" blockSize=\"" << BLOCKSIZE
				<< "\" nodeCounter=\"" << this->nodeCounter << "\" freeNodeCounter=\"" << this->freeNodeCounter << "\" >"
				<< endl;

	this->root->toStringXML(&dumpFile, this->root->getLevel(), this->controlDataSize, &this->file);

	(dumpFile) << "</BPlusTree>";
	FileManager::closeFile(&dumpFile);
}


Node* BPlusTree::readNode(int nodeId){
	int level = 0;
	Node* node = NULL;
	stringstream ios(ios_base::in| ios_base::out| ios_base::binary);
	long offset = this->controlDataSize + (nodeId * this->blockSize);
	stringstream ss;
	FileManager::readData(&file,offset,blockSize,&ios);

	ios.read(reinterpret_cast<char *> (&level), sizeof(int));
	if (level == 0) {
		node = new LeafNode();
	} else {
		node = new InternalNode();
		node->setLevel(level);
	}

	node->deserialize(&ios);
	return node;
}

void BPlusTree::writeNode(Node* node){
	stringstream ios(ios_base::in| ios_base::out| ios_base::binary);
	long offset = controlDataSize + (node->getNodeId() * blockSize);
	node->serialize(&ios);
	FileManager::writeData(&file, offset, blockSize, &ios);
}

void BPlusTree::iterate(){

}

int BPlusTree::modify(Record* record){
	if(record->getSize() > getMaxRecordSize()) {
		return EXIT_FAILURE;
	}
	
	int result = recursiveModify(record, root);
	if(result==OVERFLOWDED) {
		remove(record); // Como se que existe, lo puedo borrar
		insert(record); // Como ya lo borré, lo puedo insertar
		return EXIT_SUCCESS;
	} else if(this->root->getLevel() > 0){
		InternalNode* root = (InternalNode*)this->root;
		if(root->getChildIds()->size()==1)
		{
			int newRootId = root->getChildIds()->front();
			NodeFactory::addFreeNodeId(newRootId,&freeNodeCounter,&freeNodesFile);

			Node* newRoot = readNode(newRootId);
			newRoot->setNodeId(0);
			delete(this->root);
			this->root = newRoot;
			writeNode(this->root);
			return EXIT_SUCCESS;
		}
	}
	return result;
}

int BPlusTree::recursiveModify(Record* record, Node* currentNode){
	int result;


	if(currentNode->getLevel()==0){
		LeafNode* leafNode = (LeafNode*) currentNode;
		result = leafNode->modify(record);

		if(result==EXIT_SUCCESS) {
			writeNode(leafNode);
		}

		if (result == UNDERFLOWDED && leafNode->getNodeId()==0)
			return EXIT_SUCCESS;
		return result;
	} else {
		InternalNode* inner = (InternalNode*) currentNode;
		int locationId = inner->findLocation(record);

		Node* nextNode = readNode(locationId);
		result = recursiveModify(record, nextNode);
		if(result == OVERFLOWDED)
			return OVERFLOWDED;

		if (result == UNDERFLOWDED) {
			result = inner->resolveUnderflow(nextNode, controlDataSize, &file, &nodeCounter, &freeNodesFile,&freeNodeCounter);

			if (nextNode->getDataSize() != 0)
				NodeFactory::writeNode(nextNode, controlDataSize, &file);
		}

		NodeFactory::writeNode(inner, controlDataSize, &file);

		delete nextNode;
		if (inner->isUnderFlowded(BLOCKSIZE)){
			if (currentNode->getNodeId()==0)
				return EXIT_SUCCESS;
			else
				return UNDERFLOWDED;
		}
		return result;
	}
}

Node* BPlusTree::getNodeToInsert(int key){
	if(root == NULL)
		root = new LeafNode();
	return root;
}

void BPlusTree::balance(){
}

string BPlusTree::getFreeNodesFileName(string fileName){
	string name, ext;
	size_t found;
	found = fileName.find_last_of(".");
	name=fileName.substr(0,found);
	if(found == fileName.npos) {
		return (name+".free");
	}
	ext=fileName.substr(found);
	return (name+".free"+ext);
}

long BPlusTree::getMaxRecordSize() {
	return MAX_RECORD_PERCENTAGE * (BLOCKSIZE - 16);
}
