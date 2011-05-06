/*
 * Tree.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "BPlusTree.h"
#include "BPlusTree_CONST.h"
#include "../../ModuloDeTipos/DatoElementoNodo.h"
#include "tests.cpp"

using namespace std;
/*
DatoElementoNodo* getInputData(istream* is) {
	string key;
	DatoElementoNodo* elemento;
	stringstream ss(ios_base::in| ios_base::out| ios_base::binary);
	string clave;
	string data;

	getline(*is, clave, ';');
	getline(*is, data, ')');

	key = atoi(clave.c_str());
	ss << data;

	elemento = new DatoElementoNodo();
	elemento->edit(key, &ss);
	return elemento;
}

void executeFind(string fileName){
	if(!FileManager::fileExists(fileName)) {
		cout << "No such file  " << fileName << endl;
		return;
	}

	BPlusTree* tree = new BPlusTree(fileName, BLOCKSIZE);
	DatoElementoNodo* elemento = NULL;
	DatoElementoNodo* founded = NULL;
	string line;
	int result;
	while(!getline(cin,line, '(').eof()) {
		elemento = getInputData(&cin);

		founded = tree->find(elemento);
		if(founded!=NULL) {
			result = elemento->compareTo(founded);
			switch(result) {
			case -1:
				cout << "DatoElementoNodo not found " << elemento->getKey() << ". Next elemento: " << founded->toString()<< endl;
				break;
			case 0:
				cout << "Founded " << founded->toString() << endl;
				break;
			case 1:
				cout << "DatoElementoNodo not found " << elemento->getKey() << ". Last elemento in tree: " << founded->toString() << endl;
				break;
			}
		} else {
			cout << "DatoElementoNodo not found " << elemento->getKey() << ". Empty tree. " << endl;
		}
	}
//	delete elemento;
	delete tree;
}

void executeInsert(string fileName){
	BPlusTree* tree = new BPlusTree(fileName, BLOCKSIZE);
	DatoElementoNodo* elemento = NULL;
	string line;
	int result;
	while(!getline(cin,line, '(').eof()) {
		elemento = getInputData(&cin);
		result = tree->insert(elemento);
		if(result == EXIT_SUCCESS) {
			cout << "DatoElementoNodo " << elemento->getKey() << " has been inserted." << endl;
		} else if(result == DUPLICATED){
			cout << "DatoElementoNodo " << elemento->getKey() << " already exists. Operation failed." << endl;
		} else {
			cout << "Oversized elemento " << elemento->getKey() << ". Operation failed." << endl;
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
	DatoElementoNodo* elemento = NULL;
	string line;
	int result;
	while(!getline(cin,line, '(').eof()) {
		elemento = getInputData(&cin);
		result = tree->modify(elemento);
		if(result == EXIT_SUCCESS) {
			cout << "DatoElementoNodo " << elemento->getKey() << " has been modified." << endl;
		} else if(result == NOT_FOUNDED){
			cout << "Not such elemento " << elemento->getKey() << ". Operation failed." << endl;
		} else {
			cout << "Oversized elemento " << elemento->getKey() << ". Operation failed." << endl;
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
	DatoElementoNodo* elemento = NULL;
	string line;
	int result;
	while(!getline(cin,line, '(').eof()) {
		elemento = getInputData(&cin);
		result = tree->remove(elemento);
		if(result== EXIT_FAILURE) {
			cout << "Not such elemento " << elemento->getKey() << ". Operation failed." << endl;
		} else {
			cout << "DatoElementoNodo " << elemento->getKey() << " has been removed." << endl;
		}
	}
	delete elemento;
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
			<< "  -B	Find elemento" << endl
			<< "  -I	Insert elemento" << endl
			<< "  -M	Modify elemento" << endl
			<< "  -Q	Remove elemento" << endl
			<< "  -S	Export to text file" << endl
			<< "  -X	Export to xml file" << endl
			<< "  -h	Show help" << endl;
}


void testSerialize(){
		stringstream ss;
		DatoElementoNodo* elemento = new DatoElementoNodo();
		string key = 22323;
		ss << "this is a test data";
		elemento->edit(key, &ss);

		puts("elemento content");
		cout << elemento->getKey() << endl;
		cout << elemento->getSize() << endl;

		ofstream new_fs("elemento.dat", ios::out | ios::binary);
		new_fs.close();

		fstream fs;
		fs.open("elemento.dat",ios::out| ios::binary);

		elemento->serialize(&fs);
		fs.close();

		delete(elemento);
		fstream fss("elemento.dat",ios::in| ios::binary);

		elemento = new DatoElementoNodo();
		elemento->deserialize(&fss);

		fss.close();

		puts("elemento content");
		cout << elemento->getKey() << endl;
		cout << elemento->getData() << endl;
		cout << elemento->getSize() << endl;
}


void testTreeCreation(){
	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);
	DatoElementoNodo* elemento0 = new DatoElementoNodo(34,"3434343434343434343434343434343434343434");
	DatoElementoNodo* elemento1 = new DatoElementoNodo(23,"2323232323232323232323232323232323232323");
	DatoElementoNodo* elemento2 = new DatoElementoNodo(10,"1010101010101010101010101010101010101010");
	DatoElementoNodo* elemento3 = new DatoElementoNodo(99,"9999999999999999999999999999999999999999");
	DatoElementoNodo* elemento4 = new DatoElementoNodo(78,"7878787878787878787878787878787878787878");
	DatoElementoNodo* elemento5 = new DatoElementoNodo(25,"2525252525252525252525252525252525252525");
	DatoElementoNodo* elemento6 = new DatoElementoNodo(41,"4141414141414141414141414141414141414141");
	DatoElementoNodo* elemento7 = new DatoElementoNodo(42,"4242424242424242424242424242424242424242");
	DatoElementoNodo* elemento8 = new DatoElementoNodo(13,"1313131313131313131313131313131313131313");
	DatoElementoNodo* elemento9 = new DatoElementoNodo(21,"2121212121212121212121212121212121212121");
	DatoElementoNodo* elemento10 = new DatoElementoNodo(18,"1818181818181818181818181818181818181818");
	DatoElementoNodo* elemento11 = new DatoElementoNodo(50,"5050505050505050505050505050505050505050");
	DatoElementoNodo* elemento12 = new DatoElementoNodo(72,"7272727272727272727272727272727272727272");
	DatoElementoNodo* elemento13 = new DatoElementoNodo(60,"6060606060606060606060606060606060606060");
	DatoElementoNodo* elemento14 = new DatoElementoNodo(88,"8888888888888888888888888888888888888888");
	DatoElementoNodo* elemento15 = new DatoElementoNodo(47,"4747474747474747474747474747474747474747");
	DatoElementoNodo* elemento16 = new DatoElementoNodo(19,"1919191919191919191919191919191919191919");
	DatoElementoNodo* elemento17 = new DatoElementoNodo(8,"8888888888888888888888888888888888888888");
	DatoElementoNodo* elemento18 = new DatoElementoNodo(199,"199199199199199199199199199199199199199199199199199199");
	DatoElementoNodo* elemento19 = new DatoElementoNodo(65448,"654486544865448654486544865448654486544865448654486544865448654486544865448654486544865448654486544865448654486544865448654486544865448");
	DatoElementoNodo* elemento20 = new DatoElementoNodo(14,"14141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414");


	tree->insert(elemento0);
	tree->insert(elemento1);
	tree->insert(elemento2);
	tree->insert(elemento3);
	tree->insert(elemento4);
	tree->insert(elemento5);
	tree->insert(elemento6);
	tree->insert(elemento7);
	tree->insert(elemento8);
	tree->insert(elemento9);
	tree->insert(elemento10);
	tree->insert(elemento11);
	tree->insert(elemento12);
	tree->insert(elemento13);
	tree->insert(elemento14);
	tree->insert(elemento15);
	tree->insert(elemento16);
	cout << "Error? " << tree->insert(elemento17) << endl;
	cout << "Error? " << tree->insert(elemento18) << endl;
	cout << "Error? " << tree->insert(elemento19) << endl;
	cout << "Error? " << tree->insert(elemento20) << endl;



	tree->dump("AAA_myFile.xml");
	delete(tree);
}

int testFreeMem(){
	stringstream ss(ios_base::in| ios_base::out);
	ss.write("AAAAAAAAAAAAAAAAAAAAAAAAAAAA" , 10);

	DatoElementoNodo* elemento = new DatoElementoNodo();
	elemento->edit(3, &ss);


	cout << "Mem free..." << endl;
	delete(elemento);
	cout << "Mem free performed!" << endl;

}

void testRemove2(){
	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);
	stringstream ss(ios_base::in| ios_base::out);
	string key;
	srand((unsigned) time(NULL));
	for (int i = 0; i < 500; i++) {
		key = rand()%999;
		string data = "AAAAAAAAAAAAAAAAAAAAAAAAAAAA";
		int size = data.size();
		ss.str("");
		ss.clear();
		ss.seekg(0);
		ss.write("AAAAAAAAAAAAAAAAAAAAAAAAAAAA" , rand()%size);

		DatoElementoNodo* elemento = new DatoElementoNodo();
		elemento->edit(key, &ss);

		tree->insert(elemento);
	}

//	delete(tree);
//
//	tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);

	tree->dumpToXML("AAA_myFile.ins.xml");

	for (int i = 0; i < 2000; i++) {
		DatoElementoNodo* elemento = new DatoElementoNodo(rand()%999, "A");
		tree->remove(elemento);
		cout << "Removing elemento key=" << elemento->getKey()<<endl;

	}
	tree->dumpToXML("AAA_myFile.del.xml");

	delete(tree);

}


void testRemove(){
	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);

	string keys[] = {
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
			DatoElementoNodo* elemento = new DatoElementoNodo(keys[i], "AAAA");
			tree->insert(elemento);
		}



		delete(tree);
		tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);

		string keysToRemove[] = {
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

			DatoElementoNodo* elemento = new DatoElementoNodo(keysToRemove[i], "AAAA");
			tree->remove(elemento);
		}

		string keys2[] = {

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
			DatoElementoNodo* elemento = new DatoElementoNodo(keys2[i], "AAAA");
			tree->insert(elemento);
		}




		tree->dumpToXML("AAA_myFile.xml");


		delete(tree);
}

void testCreationRand(){
	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);
	stringstream ss;
	string key;
	srand((unsigned) time(NULL));
	for (int i = 0; i < 1000; i++) {
		key = rand()%999999999;
		DatoElementoNodo* elemento = new DatoElementoNodo(key,"A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890A.12234567890");
		cout << ":::::::: Insert Nº : " << i << " key: " << key << endl;
		cout << " Insert Error? " << tree->insert(elemento) << endl;
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
	DatoElementoNodo* elemento = new DatoElementoNodo(22,"lalala");
	iostream* ios = NULL;
	elemento->serialize(ios);
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
	DatoElementoNodo* elemento3 = new DatoElementoNodo(99,"marcelomarcelomarcelomarcelomarcelomarce");
	tree->modify(elemento3);
	tree->dump("AAA_myFile.xml");
	delete(tree);
}
*/

void testEscribirElemento(){
	DatoElementoNodo* elemento = new DatoElementoNodo("lalala",22);
	iostream* ios = NULL;
	elemento->serializar(ios);
	fstream* file;
	FileManager::createFile(file,"AAA__testWriteRecord.dat" );
	FileManager::writeData(file,0,12,ios);
}

/*

int main2(int argc, char* argv[]) {

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

	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);

	return EXIT_SUCCESS;
}
*/
