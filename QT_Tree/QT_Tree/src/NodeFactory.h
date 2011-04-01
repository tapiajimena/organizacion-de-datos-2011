/*
 * NodeFactory.h
 *
 *  Created on: Apr 27, 2010
 *      Author: igor
 */

#ifndef NODEFACTORY_H_
#define NODEFACTORY_H_

#include "../Common/FileManager.h"
#include "Node.h"
#include "LeafNode.h"
#include "InternalNode.h"
#include <fstream>

using namespace std;


class NodeFactory {

public:
	static Node* readNode(int nodeId, int sizeOffset, fstream* fs);
	static void writeNode(Node* node, int sizeOffset, fstream* fs);
	static void addFreeNodeId(int freeNodeId, unsigned int* freeNodeCounter, fstream* fs);
	static void assignNodeId(Node* newNode, unsigned int* nodeCounter, unsigned int* freeNodeCounter, fstream* fs);
};

#endif /* NODEFACTORY_H_ */
