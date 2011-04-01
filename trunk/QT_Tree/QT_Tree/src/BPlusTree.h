	/*
 * BPlusTree.h
 *
 *  Created on: 27/03/2010
 *      Author: marcelo
 */

//#ifndef NULL
//#define NULL 0

#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include "Node.h"
#include "LeafNode.h"
#include "InternalNode.h"
#include "NodeFactory.h"
#include "../Common/FileManager.h"
#include "../Common/Record.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

class BPlusTree {

	private:
		fstream file;
		fstream freeNodesFile;
		Node* root;
		long rootOffset;
		string fileName;
		long blockSize;					//SE GUARDA EN EL HEADER
		unsigned int nodeCounter;		//SE GUARDA EN EL HEADER
		unsigned int freeNodeCounter; 	//SE GUARDA EN EL HEADER
		unsigned int recordCounter; 	//SE GUARDA EN EL HEADER
		unsigned int controlDataSize; 	// cada vez que se agregue un atributo que deba guardarse como dato de control,
										//refactorizar BPlusTree::BPlusTree para que tome el valor correcto.

	public:
		BPlusTree();
		BPlusTree(string fileName, long blockSize);
		virtual ~BPlusTree();
		Node* getRoot();
		int insert(Record* record);
		int recursiveInsert(Record* record, Node* currentNode, int* promotedKey, int* promotedNodeId);
		//int recursiveRemove(Record* record, Node* currentNode, int* promotedKey, int* promotedNodeId);
		int recursiveModify(Record* record, Node* currentNode);
		int remove(Record* record);
		Record* find(Record* record);
		void iterate();
		int modify(Record* record);
		Record* recursiveSearch(Record* record, Node* node);
		void dump(string dumpFileName);
		void dumpToXML(string dumpFileName);
		Node* readNode(int nodeId) ;
		string getFreeNodesFileName(string fileName);
		long getMaxRecordSize();

	private:
		Node* getNodeToInsert(int key);

		void writeNode(Node* node);
		int readControlData();
		int writeControlData();
		void balance();


};

#endif /* BPLUSTREE_H_ */
