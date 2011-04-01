/*
 * Node.h
 *
 *  Created on: 27/03/2010
 *      Author: marcelo
 */

#ifndef NODE_H_
#define NODE_H_

#include <list>
#include <algorithm>
#include "../Common/Serializable.h"
#include "../Common/Record.h"

using namespace std;

class InternalNode;

class Node : public Serializable {

protected:
	int nodeId; //DATA DE CONTROL
	int level; 	//DATA DE CONTROL
	void balance();
	string setTabs(int level);
	string setTabsXML(int level);
public:

	virtual ~Node()=0;
	virtual void split(Node* sibling, int blockSize, int* promotedKey, int* promotedNodeID)=0;
	virtual int insert(Record* record)=0;
	virtual int remove(Record* record, int sizeOffset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter)=0;
	virtual Record* find(Record* record)=0;
	virtual bool isOverFlowded(int blockSize)=0;
	virtual bool isUnderFlowded(int blockSize)=0;
	virtual int getMaxKey()=0;
	virtual int getMinKey()=0;
	virtual long getSize()=0;
	virtual int getCtrlDataSize()=0;
	virtual long getDataSize()=0;
	//return the size of data that can be moved without cause underflow.
	virtual long getFreeDataSizeOnLeft()=0;
	virtual long getFreeDataSizeOnRight()=0;
    int getNodeId();
    void setNodeId(int nodeId);
    int getLevel();
    void setLevel(int level);
    virtual void toString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs) = 0;
    virtual void toStringXML(iostream* ios, int rootLevel, int sizeOffset, fstream* fs) = 0;
    //move amount of data from current node to its left sibling.
    virtual void moveDataToLeft(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit) = 0;
    //move amount of data from current node to its right sibling.
    virtual void moveDataToRight(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit) = 0;

};

#endif /* NODE_H_ */
