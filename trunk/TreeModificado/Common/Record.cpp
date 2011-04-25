/*
 * Record.cpp
 *
 *  Created on: Apr 7, 2010
 *      Author: igor
 */

#include "Record.h"

using namespace std;

Record::Record(){
	this->data = (char*)malloc(0);
	this->key=-1;
	this->dataSize = 0;
}

Record::Record(int key) {
	this->key = key;
	this->data = (char*)malloc(0);
	this->dataSize=0;
}


Record::Record(int key, char* data) {
	this->key = key;
	this->data = data;
	this->dataSize=strlen(data);
}

Record::~Record() {
	free(this->data);
}

Record* Record::clone(){
	Record* auxRecord = new Record(this->key);
	stringstream ss(ios_base::in | ios_base::out);
	ss.write(this->data,this->dataSize);
	auxRecord->edit(this->key,&ss);
	return auxRecord;
}

void Record::serialize(iostream* ios){
	/* Serialización de Record:
	* <Key><DataSize><Data> */
	(*ios).write(reinterpret_cast<char *>(&key),sizeof(key));
	(*ios).write(reinterpret_cast<char *>(&dataSize),sizeof(dataSize));
	(*ios).write(data, dataSize);
}

void Record::deserialize(iostream* ios){

	(*ios).read( reinterpret_cast<char *>(&key), sizeof(key));
	(*ios).read( reinterpret_cast<char *>(&dataSize), sizeof(dataSize));

	this->data = (char*)realloc(this->data,this->dataSize);
	ios->read(this->data, this->dataSize);
}

int Record::compareTo(void* external) {
	if (this->key < ((Record*)external)->getKey())
		return -1;
	if (this->key == ((Record*)external)->getKey())
		return 0;
	return 1;
}

void Record::toStringXML(iostream* ios, int rootLevel){
	string tabs = setTabsXML(rootLevel +1);
	(*ios) << tabs << "<record" << " KEY=\"" << getKey() << "\" DATA=\"";
	ios->write(this->data, this->dataSize);
	(*ios) << "\" recordSize=\"" 	<<  this->getSize() << "\" recordDataSize=\"" << this->getDataSize() << "\" >" << endl;
	(*ios) << tabs << "</record>" << endl;
}

//void Record::toStringXML(iostream* ios, int rootLevel){
//	string tabs = setTabsXML(rootLevel +1);
//	(*ios) << tabs << "<record" << " key=\"" << getKey() << "\" recordSize=\""
//			<<  this->getSize() << "\" recordDataSize=\"" << this->getDataSize() << "\" >" << endl;
//	(*ios) << tabs << "\t";
//	ios->write(this->data, this->dataSize);
//	(*ios) << endl;
//	(*ios) << tabs << "</record>" << endl;
//}

void Record::toString(iostream* ios, int rootLevel){
	string tabs = setTabs(rootLevel + 1);


	(*ios) << tabs  << "|----- [record" << " KEY= [" << getKey() << "] DATA= [";
	ios->write(this->data, this->dataSize);
	(*ios) << "] recordSize=[" 	<<  this->getSize() << "] recordDataSize=[" << this->getDataSize() << "] ]" << endl;
}

string Record::setTabsXML(int level){
	string tabs = "";
	for(int i =0; i< level; i++){
		tabs += "\t";
	}
	return tabs;
}

string Record::toString(){
	stringstream ios(ios_base::in| ios_base::out| ios_base::binary);
	(ios) <<"(" << getKey() << ";";
	ios.write(this->data, this->dataSize);
	(ios) <<")";
	return ios.str();
}

string Record::setTabs(int level){
	string tabs = "";
	for(int i =0; i< level; i++){
		tabs += "| \t";
	}
	return tabs;
}


int Record::getKey(){
	return this->key;
}

char* Record::getData(){
	return this->data;
}

int Record::getSize() const{
	long recordSize = 0;

	// Sumo el tamaño del atributo key
	recordSize += sizeof(int);
	// Sumo el tamaño del atributo size
	recordSize += sizeof(int);
	// Sumo el tamaño del atributo data
	recordSize += this->dataSize;

	return recordSize;
}

void Record::edit(int key, iostream* ios){
	this->key = key;
	this->data = NULL;
	this->dataSize = 0;
	while(!ios->eof()){
		this->data = (char*)realloc(this->data,this->dataSize + 0x000f);
		ios->read(this->data + this->dataSize, 0x000f);
		this->dataSize += ios->gcount();
	}
}
void Record::setData(char *data) {
	this->data = data;
	this->dataSize=strlen(data);
}

void Record::setKey(int key) {
	this->key = key;
}

void Record::setDataSize(int size) {
	this->dataSize = size;
}

int Record::getDataSize() {
	return dataSize;
}



