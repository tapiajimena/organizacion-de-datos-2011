/*
 * BPlusTree.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
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
#include "../../ModuloDeTipos/DatoElementoNodo.h"
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
		unsigned int elementoCounter; 	//SE GUARDA EN EL HEADER
		unsigned int controlDataSize; 	// cada vez que se agregue un atributo que deba guardarse como dato de control,
										//refactorizar BPlusTree::BPlusTree para que tome el valor correcto.

	public:
		BPlusTree();
		BPlusTree(string fileName, long blockSize);
		virtual ~BPlusTree();
		Node* getRoot();
		int insert(DatoElementoNodo* elemento);
		int recursiveInsert(DatoElementoNodo* elemento, Node* currentNode, string* promotedKey, int* promotedNodeId);
		//int recursiveRemove(DatoElementoNodo* elemento, Node* currentNode, int* promotedKey, int* promotedNodeId);
		int recursiveModify(DatoElementoNodo* elemento, Node* currentNode);
		int remove(DatoElementoNodo* elemento);
		DatoElementoNodo* find(DatoElementoNodo* elemento);
		void iterate();
		int modify(DatoElementoNodo* elemento);
		DatoElementoNodo* recursiveSearch(DatoElementoNodo* elemento, Node* node);
		void dump(string dumpFileName);
		void dumpToXML(string dumpFileName);
		Node* readNode(int nodeId) ;
		string getFreeNodesFileName(string fileName);
		long getMaxRecordSize();

	private:
		Node* getNodeToInsert(string key);

		void writeNode(Node* node);
		int readControlData();
		int writeControlData();
		void balance();


};

#endif /* BPLUSTREE_H_ */
