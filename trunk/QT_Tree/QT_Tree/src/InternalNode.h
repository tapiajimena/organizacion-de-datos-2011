/*
 * InternalNode.h
 *
 *  Created on: Apr 10, 2010
 *      Author: juane
 */

#ifndef INTERNALNODE_H_
#define INTERNALNODE_H_

#include <sstream>
#include "Node.h"
#include "BPlusTree_CONST.h"

class InternalNode: public Node {

private:
	list<int> keys;
	list<int> childIds;
	void nodesToString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
	void nodesToStringXML(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
    void synchronizeOnRemove(Node* node, unsigned int* freeNodeCounter, fstream* fs);


public:
	InternalNode();
	virtual ~InternalNode();
    void split(Node* sibling, int blockSize, int* promotedKey, int* promotedNodeID);
	int insert(Record* record);
	int remove(Record* record, int sizeOffset, fstream* fs, unsigned int* nodeCount, fstream* freefs, unsigned int* freeNodeCounter);
	Record* find(Record* record);
	void insertKeyChild(int key, int childId);
	int findLocation(Record* record);
	int getLeftSiblingId(Node* childNode);
	int getRightSiblingId(Node* childNode);
	list<int>* getKeys();
    list<int>* getChildIds();
	void serialize(iostream* ios);
	void deserialize(iostream* ios);
	long getSize();
	bool isOverFlowded(int blockSize);
	bool isUnderFlowded(int blockSize);
	void toString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
	void toStringXML(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
	int getMaxKey();
	int getMinKey();
	int getCtrlDataSize();
	long getDataSize();
	long getFreeDataSizeOnLeft();
	long getFreeDataSizeOnRight();
    int resolveOverflow(Node* node, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter);
    int resolveUnderflow(Node* node, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter);
    void insertKeyToList(int key);
    void insertKeyInOrderToList(int key);
	void insertChildIDToList(int childID);
	int getKeyMinorEqualTo(int key);
	int getKeyMajorEqualTo(int key);
	int getKeyMinorTo(int key);
	//redistribute data between the Node and its siblings.
	int tryRotate(Node* leftSibling, Node* node, Node* rightSibling);
	//merge data between the node and its siblings.
	int merge(Node* leftSibling, Node* node, Node* rightSibling);
	void moveDataToLeft(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit);
	void moveDataToRight(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit);
};

#endif /* INTERNALNODE_H_ */
