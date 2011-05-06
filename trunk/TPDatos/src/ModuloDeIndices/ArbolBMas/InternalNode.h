/*
 * InternalNode.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#ifndef INTERNALNODE_H_
#define INTERNALNODE_H_

#include <sstream>
#include <string.h>
#include <stdint.h>
#include "Node.h"

#include "BPlusTree_CONST.h"

using namespace std;
class InternalNode: public Node {

private:
	list<string> keys;
	list<int> childIds;
	void nodesToString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
	void nodesToStringXML(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
    void synchronizeOnRemove(Node* node, unsigned int* freeNodeCounter, fstream* fs);


public:
	InternalNode();
	virtual ~InternalNode();
    void split(Node* sibling, int blockSize, string* promotedKey, int* promotedNodeID);
	int insert(DatoElementoNodo* elemento);
	int remove(DatoElementoNodo* elemento, int sizeOffset, fstream* fs, unsigned int* nodeCount, fstream* freefs, unsigned int* freeNodeCounter);
	DatoElementoNodo* find(DatoElementoNodo* elemento);
	void insertKeyChild(string key, int childId);
	int findLocation(DatoElementoNodo* elemento);
	int getLeftSiblingId(Node* childNode);
	int getRightSiblingId(Node* childNode);
	list<string>* getKeys();
    list<int>* getChildIds();
	void serialize(iostream* ios);
	void deserialize(iostream* ios);
	long getSize();
	bool isOverFlowded(int blockSize);
	bool isUnderFlowded(int blockSize);
	void toString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
	void toStringXML(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
	string getMaxKey();
	string getMinKey();
	int getCtrlDataSize();
	long getDataSize();
	long getFreeDataSizeOnLeft();
	long getFreeDataSizeOnRight();
    int resolveOverflow(Node* node, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter);
    int resolveUnderflow(Node* node, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter);
    void insertKeyToList(string key);
    void insertKeyInOrderToList(string key);
	void insertChildIDToList(int childID);
	string getKeyMinorEqualTo(string key);
	string getKeyMajorEqualTo(string key);
	string getKeyMinorTo(string clave);
	//redistribute data between the Node and its siblings.
	int tryRotate(Node* leftSibling, Node* node, Node* rightSibling);
	//merge data between the node and its siblings.
	int merge(Node* leftSibling, Node* node, Node* rightSibling);
	void moveDataToLeft(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit);
	void moveDataToRight(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit);
};

#endif /* INTERNALNODE_H_ */
