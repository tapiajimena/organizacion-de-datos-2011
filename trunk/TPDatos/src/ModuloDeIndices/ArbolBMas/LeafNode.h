/*
 * LeafNode.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#ifndef LEAFNODE_H_
#define LEAFNODE_H_

#include <stdio.h>
#include <string.h>
#include "Node.h"
#include "BPlusTree_CONST.h"
#include "../../../Common/Utilitarios/Logger.h"
#include "../../ModuloDeTipos/DatoElementoNodo.h"
#include "InternalNode.h"


class LeafNode: public Node {

private:
	list<DatoElementoNodo*> elementos;
	int nextLeafNodeId;
	void elementosToString(iostream* ios, int rootLevel);
	void elementosToStringXML(iostream* ios, int rootLevel);

	/*
	 * front coding
	 */
	list<DatoElementoNodo*>* frontCode(list<DatoElementoNodo*>* elementos);
	list<DatoElementoNodo*>* frontDecode(list<DatoElementoNodo*>* elementos);
	DatoElementoNodo* frontCode(DatoElementoNodo* anterior, DatoElementoNodo* actual);

public:

	LeafNode();
	LeafNode(list<DatoElementoNodo*> elementos, int nextLeafNodeId);
	virtual ~LeafNode();

	void split(Node* sibling, int blockSize, string* promotedKey, int* promotedNodeID);
	int insert(DatoElementoNodo* elemento);
	static bool compareElementos(DatoElementoNodo* r1, DatoElementoNodo* r2);
	int remove(DatoElementoNodo* elemento, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter);
	int modify(DatoElementoNodo* elemento);
	DatoElementoNodo* find(DatoElementoNodo* elemento);
	list<int> getKeys();
	void serialize(iostream* ios);
	void deserialize(iostream* ios);
	list<DatoElementoNodo*>* getElementos();
	void readElementos();
	void setNextLeafNodeId(int nextLeaf);
	int getNextLeafNodeId();
	void redistribute(Node* sibling);
	int elementoIndex(DatoElementoNodo* elemento);
	long getSize();
	bool isOverFlowded(int blockSize);
	bool isUnderFlowded(int blockSize);
	void toString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
	void toStringXML(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
	string getMinKey();
	string getMaxKey();
	int getCtrlDataSize();
	long getDataSize();
	long getFreeDataSizeOnLeft();
	long getFreeDataSizeOnRight();
	LeafNode* clone();
	void moveDataToLeft(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit);
	void moveDataToRight(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit);
};

#endif /* LEAFNODE_H_ */
