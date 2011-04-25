/*
 * NodeFactory.cpp
 *
 *  Created on: Apr 27, 2010
 *      Author: igor
 */

#include "NodeFactory.h"

Node* NodeFactory::readNode(int nodeId, int sizeOffset, fstream* fs){
	int level = 0;
	Node* node = NULL;
	stringstream ios(ios_base::in| ios_base::out| ios_base::binary);
	long offset = sizeOffset + (nodeId * BLOCKSIZE);
	FileManager::readData(fs,offset,BLOCKSIZE,&ios);

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

void NodeFactory::writeNode(Node* node, int sizeOffset, fstream* fs){
	stringstream ios(ios_base::in| ios_base::out| ios_base::binary);
	long offset = sizeOffset + (node->getNodeId() * BLOCKSIZE);
	node->serialize(&ios);
	FileManager::writeData(fs, offset, BLOCKSIZE, &ios);
}

void NodeFactory::addFreeNodeId(int freeNodeId, unsigned int* freeNodeCounter, fstream* fs)
{
	long offset = *freeNodeCounter * sizeof(int);
	stringstream iosFreeNode(ios_base::in| ios_base::out| ios_base::binary);
	iosFreeNode.write(reinterpret_cast<char *>(&freeNodeId),sizeof(freeNodeId));
	FileManager::writeData(fs,offset, sizeof(int), &iosFreeNode);
	(*freeNodeCounter)++;
}

void NodeFactory::assignNodeId(Node* newNode, unsigned int* nodeCounter, unsigned int* freeNodeCounter, fstream* fs) {
	if(*freeNodeCounter > 0) {
		int id;
		long offset = ((*freeNodeCounter)-1) * sizeof(int);
		stringstream iosFreeNode(ios_base::in| ios_base::out| ios_base::binary);
		FileManager::readData(fs,offset,sizeof(int),&iosFreeNode);
		(iosFreeNode).read( reinterpret_cast<char *>(&id), sizeof(id));
		newNode->setNodeId(id);
		(*freeNodeCounter)--;
	} else {
		newNode->setNodeId(*nodeCounter);
		(*nodeCounter)++;
	}
}

