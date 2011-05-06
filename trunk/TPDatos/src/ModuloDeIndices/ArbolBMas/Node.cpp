/*
 * Node.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#include "Node.h"

Node::~Node(){}

void Node::balance() {

}

int Node::getNodeId(){
	return nodeId;
}

void Node::setNodeId(int nodeId){
	this->nodeId = nodeId;
}

int Node::getLevel(){
	return level;
}

void Node::setLevel(int level){
	this->level = level;
}

void Node::toString(iostream* ios, int rootLevel, int sizeOffset, fstream* fs){
}


void Node::moveDataToLeft(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit){

}
//move amount of data from current node to its right sibling.
void Node::moveDataToRight(InternalNode* parentNode, Node* nodeToMoveData, long fromDataLimit, long toDataLimit){

}

string Node::setTabsXML(int level){
	string tabs = "";
	for(int i =0; i< level; i++){
		tabs += "\t";
	}
	return tabs;
}

string Node::setTabs(int level){
	string tabs = "";
	for(int i =0; i< level; i++){
		tabs += "| \t";
	}
	return tabs;
}
