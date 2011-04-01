/*
 * LeafNode.h
 *
 *  Created on: 27/03/2010
 *      Author: marcelo
 */

#ifndef LEAFNODE_H_
#define LEAFNODE_H_

#include "Node.h"
#include "BPlusTree_CONST.h"
#include "../Common/Record.h"
#include "InternalNode.h"
//#include <sstream>

class LeafNode: public Node {

private:
	list<Record*> records;
	int nextLeafNodeId;
	void recordsToString(iostream* ios, int rootLevel);
	void recordsToStringXML(iostream* ios, int rootLevel);

public:

	LeafNode();
	LeafNode(list<Record*> records, int nextLeafNodeId);
	virtual ~LeafNode();

	void split(Node* sibling, int blockSize, int* promotedKey, int* promotedNodeID);
	int insert(Record* record);
	static bool compareRecords(Record* r1, Record* r2);
	int remove(Record* record, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter);
	int modify(Record* record);
	Record* find(Record* record);
	list<int> getKeys();
	void serialize(iostream* ios);
	void deserialize(iostream* ios);
	list<Record*>* getRecords();
	void readRecords();
	void setNextLeafNodeId(int nextLeaf);
	int getNextLeafNodeId();
	void redistribute(Node* sibling);
	int recordIndex(Record* record);
	long getSize();
	bool isOverFlowded(int blockSize);
	bool isUnderFlowded(int blockSize);
	void toString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
	void toStringXML(iostream* ios, int rootLevel, int sizeOffset, fstream* fs);
	int getMinKey();
	int getMaxKey();
	int getCtrlDataSize();
	long getDataSize();
	long getFreeDataSizeOnLeft();
	long getFreeDataSizeOnRight();
	LeafNode* clone();
	void moveDataToLeft(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit);
	void moveDataToRight(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit);
};

#endif /* LEAFNODE_H_ */
