//============================================================================
// Name        : Tree.cpp
// Author      : marcelo
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "BPlusTree.h"
#include "BPlusTree_CONST.h"
#include "../Common/Record.h"
#include "tests.cpp"

using namespace std;

Record* getInputData(istream* is) {
	int key;
	Record* record;
	stringstream ss(ios_base::in| ios_base::out| ios_base::binary);
	string clave;
	string data;

	getline(*is, clave, ';');
	getline(*is, data, ')');

	key = atoi(clave.c_str());
	ss << data;

	record = new Record();
	record->edit(key, &ss);
	return record;
}

void executeFind(string fileName){
	if(!FileManager::fileExists(fileName)) {
		cout << "No such file  " << fileName << endl;
		return;
	}

	BPlusTree* tree = new BPlusTree(fileName, BLOCKSIZE);
	Record* record = NULL;
	Record* founded = NULL;
	string line;
	int result;
	while(!getline(cin,line, '(').eof()) {
		record = getInputData(&cin);

		founded = tree->find(record);
		if(founded!=NULL) {
			result = record->compareTo(founded);
			switch(result) {
			case -1:
				cout << "Record not found " << record->getKey() << ". Next record: " << founded->toString()<< endl;
				break;
			case 0:
				cout << "Founded " << founded->toString() << endl;
				break;
			case 1:
				cout << "Record not found " << record->getKey() << ". Last record in tree: " << founded->toString() << endl;
				break;
			}
		} else {
			cout << "Record not found " << record->getKey() << ". Empty tree. " << endl;
		}
	}
//	delete record;
	delete tree;
}

void executeInsert(string fileName){
	BPlusTree* tree = new BPlusTree(fileName, BLOCKSIZE);
	Record* record = NULL;
	string line;
	int result;
	while(!getline(cin,line, '(').eof()) {
		record = getInputData(&cin);
		result = tree->insert(record);
		if(result == EXIT_SUCCESS) {
			cout << "Record " << record->getKey() << " has been inserted." << endl;
		} else if(result == DUPLICATED){
			cout << "Record " << record->getKey() << " already exists. Operation failed." << endl;
		} else {
			cout << "Oversized record " << record->getKey() << ". Operation failed." << endl;
		}
	}

	delete tree;
}

void executeModify(string fileName){
	if(!FileManager::fileExists(fileName)) {
		cout << "No such file  " << fileName << endl;
		return;
	}
	BPlusTree* tree = new BPlusTree(fileName, BLOCKSIZE);
	Record* record = NULL;
	string line;
	int result;
	while(!getline(cin,line, '(').eof()) {
		record = getInputData(&cin);
		result = tree->modify(record);
		if(result == EXIT_SUCCESS) {
			cout << "Record " << record->getKey() << " has been modified." << endl;
		} else if(result == NOT_FOUNDED){
			cout << "Not such record " << record->getKey() << ". Operation failed." << endl;
		} else {
			cout << "Oversized record " << record->getKey() << ". Operation failed." << endl;
		}
	}
	delete tree;
}
void executeRemove(string fileName){
	if(!FileManager::fileExists(fileName)) {
		cout << "No such file  " << fileName << endl;
		return;
	}
	BPlusTree* tree = new BPlusTree(fileName, BLOCKSIZE);
	Record* record = NULL;
	string line;
	int result;
	while(!getline(cin,line, '(').eof()) {
		record = getInputData(&cin);
		result = tree->remove(record);
		if(result== EXIT_FAILURE) {
			cout << "Not such record " << record->getKey() << ". Operation failed." << endl;
		} else {
			cout << "Record " << record->getKey() << " has been removed." << endl;
		}
	}
	delete record;
	delete tree;
}

void executeDump(string fileName){
	if(!FileManager::fileExists(fileName)) {
		cout << "No such file  " << fileName << endl;
		return;
	}
	BPlusTree* tree = new BPlusTree(fileName, BLOCKSIZE);
	string dumpFileName = "text-tree.txt";
	tree->dump(dumpFileName);
	cout << "Generated file: " << dumpFileName << endl;
	delete tree;
}

void executeDumpToXML(string fileName){
	if(!FileManager::fileExists(fileName)) {
		cout << "No such file  " << fileName << endl;
		return;
	}
	BPlusTree* tree = new BPlusTree(fileName, BLOCKSIZE);
	string XMLdumpFileName = "xml-tree.xml";
	tree->dumpToXML(XMLdumpFileName);
	cout << "Generated file: " << XMLdumpFileName << endl;
	delete tree;
}

void printUsage() {
	   cout	<< "Usage: Tree [file] [OPTION]" << endl
			<< "Options:" << endl
			<< "  -B	Find record" << endl
			<< "  -I	Insert record" << endl
			<< "  -M	Modify record" << endl
			<< "  -Q	Remove record" << endl
			<< "  -S	Export to text file" << endl
			<< "  -X	Export to xml file" << endl
			<< "  -h	Show help" << endl;
}


void testSerialize(){
		stringstream ss;
		Record* record = new Record();
		int key = 22323;
		ss << "this is a test data";
		record->edit(key, &ss);

		puts("record content");
		cout << record->getKey() << endl;
		cout << record->getSize() << endl;

		ofstream new_fs("record.dat", ios::out | ios::binary);
		new_fs.close();

		fstream fs;
		fs.open("record.dat",ios::out| ios::binary);

		record->serialize(&fs);
		fs.close();

		delete(record);
		fstream fss("record.dat",ios::in| ios::binary);

		record = new Record();
		record->deserialize(&fss);

		fss.close();

		puts("record content");
		cout << record->getKey() << endl;
		cout << record->getData() << endl;
		cout << record->getSize() << endl;
}


void testTreeCreation(){
	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);
	Record* record0 = new Record(34,"3434343434343434343434343434343434343434");
	Record* record1 = new Record(23,"2323232323232323232323232323232323232323");
	Record* record2 = new Record(10,"1010101010101010101010101010101010101010");
	Record* record3 = new Record(99,"9999999999999999999999999999999999999999");
	Record* record4 = new Record(78,"7878787878787878787878787878787878787878");
	Record* record5 = new Record(25,"2525252525252525252525252525252525252525");
	Record* record6 = new Record(41,"4141414141414141414141414141414141414141");
	Record* record7 = new Record(42,"4242424242424242424242424242424242424242");
	Record* record8 = new Record(13,"1313131313131313131313131313131313131313");
	Record* record9 = new Record(21,"2121212121212121212121212121212121212121");
	Record* record10 = new Record(18,"1818181818181818181818181818181818181818");
	Record* record11 = new Record(50,"5050505050505050505050505050505050505050");
	Record* record12 = new Record(72,"7272727272727272727272727272727272727272");
	Record* record13 = new Record(60,"6060606060606060606060606060606060606060");
	Record* record14 = new Record(88,"8888888888888888888888888888888888888888");
	Record* record15 = new Record(47,"4747474747474747474747474747474747474747");
	Record* record16 = new Record(19,"1919191919191919191919191919191919191919");
	Record* record17 = new Record(8,"8888888888888888888888888888888888888888");
	Record* record18 = new Record(199,"199199199199199199199199199199199199199199199199199199");
	Record* record19 = new Record(65448,"654486544865448654486544865448654486544865448654486544865448654486544865448654486544865448654486544865448654486544865448654486544865448");
	Record* record20 = new Record(14,"14141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414");


	tree->insert(record0);
	tree->insert(record1);
	tree->insert(record2);
	tree->insert(record3);
	tree->insert(record4);
	tree->insert(record5);
	tree->insert(record6);
	tree->insert(record7);
	tree->insert(record8);
	tree->insert(record9);
	tree->insert(record10);
	tree->insert(record11);
	tree->insert(record12);
	tree->insert(record13);
	tree->insert(record14);
	tree->insert(record15);
	tree->insert(record16);
	cout << "Error? " << tree->insert(record17) << endl;
	cout << "Error? " << tree->insert(record18) << endl;
	cout << "Error? " << tree->insert(record19) << endl;
	cout << "Error? " << tree->insert(record20) << endl;



	tree->dump("AAA_myFile.xml");
	delete(tree);
}

int testFreeMem(){
	stringstream ss(ios_base::in| ios_base::out);
	ss.write("AAAAAAAAAAAAAAAAAAAAAAAAAAAA" , 10);

	Record* record = new Record();
	record->edit(3, &ss);


	cout << "Mem free..." << endl;
	delete(record);
	cout << "Mem free performed!" << endl;

}

void testRemove2(){
	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);
	stringstream ss(ios_base::in| ios_base::out);
	int key;
	srand((unsigned) time(NULL));
	for (int i = 0; i < 500; i++) {
		key = rand()%999;
		string data = "AAAAAAAAAAAAAAAAAAAAAAAAAAAA";
		int size = data.size();
		ss.str("");
		ss.clear();
		ss.seekg(0);
		ss.write("AAAAAAAAAAAAAAAAAAAAAAAAAAAA" , rand()%size);

		Record* record = new Record();
		record->edit(key, &ss);

		tree->insert(record);
	}

//	delete(tree);
//
//	tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);

	tree->dumpToXML("AAA_myFile.ins.xml");

	for (int i = 0; i < 2000; i++) {
		Record* record = new Record(rand()%999, "A");
		tree->remove(record);
		cout << "Removing record key=" << record->getKey()<<endl;

	}
	tree->dumpToXML("AAA_myFile.del.xml");

	delete(tree);

}


void testRemove(){
	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);

	int keys[] = {
			34
			,23,10,99,78,25,41
				,42,13,21,18
				,50
				,72
				,60
				,88,47
				,19,51,53,17,9,5,8,46,32,31
				,78,66,33,233,125,74,63,19,4
				,1,345,286,35,91,543,784,13,543
				,656,777,555,232,231,145,133
				,126,789,444,111,222,467,455,90
				,657,876,1776,176,85
	};


		int nodesNumber = sizeof(keys) / sizeof(int);

		cout << nodesNumber << endl;

		cout << "total nodes:" << nodesNumber << endl;
		for (int i=0; i < nodesNumber; i++){


			stringstream ss;
			ss.str("");
			ss << keys[i];
			Record* record = new Record(keys[i], "AAAA");
			tree->insert(record);
		}



		delete(tree);
		tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);

		int keysToRemove[] = {
				34
				,23,10,99,78,25,41
					,42,13,21,18
					,50
					,72
					,60
					,88,47
					,19,51,53,17,9,5,8,46,32,31
					,78,66,33,233,125,74,63,19,4
					,1,345,286,35,91,543,784,13,543
					,656,777,555,232,231,145,133
					,876,1776
//					,126,789,444,111,222,467,455,90
					,657,876,1776,176,85
		};




//		{
//				1
//				,4
//				,5
//				,9
//				,8
//				,10
//				,60
//				,35
//				,41
//				,21
//				42
//				,25
//				,19
//				,50
//				,784
//				,32
//				,33
//				,34
//				,444,543,656,789
//				,345
//		};
		nodesNumber = sizeof(keysToRemove) / sizeof(int);

		for (int i=0; i < nodesNumber; i++){

			Record* record = new Record(keysToRemove[i], "AAAA");
			tree->remove(record);
		}

		int keys2[] = {

//				34
//				,23,10,99,78,25,41
//					,42,13,21,18
//					,50
//					,72
//					,60
//					,88,47
//					,19,51,53,17,9,5,8,46,32,31
//					,78,66,33,233,125,74,63,19,4
//					,1,345,286,35,91,543,784,13,543
//					,656,777,555,232,231,145,133
//					,126,789,444,111,222,467,455,90
//					,657,876,1776,176,85
			};

		nodesNumber = sizeof(keys2) / sizeof(int);

		cout << nodesNumber << endl;

		cout << "total nodes:" << nodesNumber << endl;
		for (int i=0; i < nodesNumber; i++){

			stringstream ss;
			ss.str("");
			ss << keys2[i];
			Record* record = new Record(keys2[i], "AAAA");
			tree->insert(record);
		}




		tree->dumpToXML("AAA_myFile.xml");


		delete(tree);
}

void testCreationRand(){
	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);
	stringstream ss;
	int key;
	srand((unsigned) time(NULL));
	for (int i = 0; i < 1000; i++) {
		key = rand()%999999999;
		Record* record = new Record(key,"A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890");
		cout << ":::::::: Insert Nº : " << i << " key: " << key << endl;
		cout << " Insert Error? " << tree->insert(record) << endl;
	}
	tree->dump("AAA_myFile.xml");
	delete(tree);
}

void testFileManager() {
	if(FileManager::fileExists("lalala.txt")){
		cout << "Existe" << endl;
	} else {
		cout << "No existe" << endl;
	}

	fstream fs;
	FileManager::createFile(&fs,"creado.txt");
	if(fs.is_open()) {
		cout << "Creado y abierto!" << endl;
		FileManager::closeFile(&fs);
	} else {
		cout << "No esta abierto... estará creado?" << endl;
	}

	if(FileManager::openFile(&fs, "creado.txt")) {
		cout << "Abierto" << endl;
		FileManager::closeFile(&fs);
	}
}
void testWriteRecord(){
	Record* record = new Record(22,"lalala");
	iostream* ios = NULL;
	record->serialize(ios);
	fstream* file;
	FileManager::createFile(file,"AAA__testWriteRecord.dat" );
	FileManager::writeData(file,0,12,ios);
}

void testTreeToString(){
//	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);
//	tree->dump();
}

void testModify() {
	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);
	Record* record3 = new Record(99,"marcelomarcelomarcelomarcelomarcelomarce");
	tree->modify(record3);
	tree->dump("AAA_myFile.xml");
	delete(tree);
}

int main(int argc, char* argv[]) {

	if (argc < 3) {
		cout << "Missing arguments. " << endl;
		printUsage();
		return EXIT_SUCCESS;
	}

	char* fileName = argv[1];

	const char* const options = "BIMQSXh"; // Cada una de las opciones posibles
	int selected_option = getopt_long (argc, argv, options, NULL, NULL);

	switch (selected_option) {
		case 'B' :
			executeFind(fileName);
			break;
		case 'I' :
			executeInsert(fileName);
			break;
		case 'M' :
			executeModify(fileName);
			break;
		case 'Q' :
			executeRemove(fileName);
			break;
		case 'S' :
			executeDump(fileName);
			break;
		case 'X' :
			executeDumpToXML(fileName);
			break;
		case 'h' :
			printUsage();
			break;
		case '?' : // Si la opción no es valida
			printUsage();
			break;
		default :
			abort();
	}

	return EXIT_SUCCESS;
}
