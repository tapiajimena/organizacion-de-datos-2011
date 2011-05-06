/*
 * main.cpp
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
#include "../ModuloDeTipos/DatoElementoNodo.h"

void testCrearArbol() {
	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);

	DatoElementoNodo* elemento0 = new DatoElementoNodo("a", 1);
	DatoElementoNodo* elemento1 = new DatoElementoNodo("b", 1);
	DatoElementoNodo* elemento2 = new DatoElementoNodo("c", 2);
	DatoElementoNodo* elemento3 = new DatoElementoNodo("d", 2);
	DatoElementoNodo* elemento4 = new DatoElementoNodo("e", 2);
	DatoElementoNodo* elemento5 = new DatoElementoNodo("f", 2);
	DatoElementoNodo* elemento6 = new DatoElementoNodo("g", 2);
	DatoElementoNodo* elemento7 = new DatoElementoNodo("h", 2);
	DatoElementoNodo* elemento8 = new DatoElementoNodo("i", 2);
	DatoElementoNodo* elemento9 = new DatoElementoNodo("j", 2);
	DatoElementoNodo* elemento10 = new DatoElementoNodo("k", 2);
	DatoElementoNodo* elemento11 = new DatoElementoNodo("l", 2);
	DatoElementoNodo* elemento12 = new DatoElementoNodo("m", 2);
	DatoElementoNodo* elemento13 = new DatoElementoNodo("n", 2);
	DatoElementoNodo* elemento14 = new DatoElementoNodo("ñ", 2);
	DatoElementoNodo* elemento15 = new DatoElementoNodo("o", 2);
	DatoElementoNodo* elemento16 = new DatoElementoNodo("p", 2);
	DatoElementoNodo* elemento17 = new DatoElementoNodo("q", 2);
	DatoElementoNodo* elemento18 = new DatoElementoNodo("r", 2);
	DatoElementoNodo* elemento19 = new DatoElementoNodo("s", 2);
	DatoElementoNodo* elemento20 = new DatoElementoNodo("t", 2);
	DatoElementoNodo* elemento21 = new DatoElementoNodo("u", 2);
	DatoElementoNodo* elemento22 = new DatoElementoNodo("v", 2);
	DatoElementoNodo* elemento23 = new DatoElementoNodo("w", 2);
	DatoElementoNodo* elemento24 = new DatoElementoNodo("x", 2);
	DatoElementoNodo* elemento25 = new DatoElementoNodo("y", 2);
	DatoElementoNodo* elemento26 = new DatoElementoNodo("z", 2);
	DatoElementoNodo* elemento27 = new DatoElementoNodo("1", 2);
	DatoElementoNodo* elemento28 = new DatoElementoNodo("2", 2);
	DatoElementoNodo* elemento29 = new DatoElementoNodo("3", 2);
	DatoElementoNodo* elemento30 = new DatoElementoNodo("4", 2);
	DatoElementoNodo* elemento31 = new DatoElementoNodo("5", 2);
	DatoElementoNodo* elemento32 = new DatoElementoNodo("6", 2);
	DatoElementoNodo* elemento33 = new DatoElementoNodo("7", 2);
	DatoElementoNodo* elemento34 = new DatoElementoNodo("8", 2);
	DatoElementoNodo* elemento35 = new DatoElementoNodo("9", 2);
	DatoElementoNodo* elemento36 = new DatoElementoNodo("0", 2);

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
	tree->insert(elemento17);
	tree->insert(elemento18);
	tree->insert(elemento19);
	tree->insert(elemento20);
	tree->insert(elemento21);
	tree->insert(elemento22);
	tree->insert(elemento23);
	tree->insert(elemento24);
	tree->insert(elemento25);
	tree->insert(elemento26);
	tree->insert(elemento27);
	tree->insert(elemento28);
	tree->insert(elemento29);
	tree->insert(elemento30);
	tree->insert(elemento31);
	tree->insert(elemento32);
	tree->insert(elemento33);
	tree->insert(elemento34);
	tree->insert(elemento35);
	tree->insert(elemento36);

	cout << "Error? " << tree->insert(elemento36) << endl;
	cout << "Error? " << tree->insert(elemento1) << endl;
	cout << "Error? " << tree->insert(elemento9) << endl;
	cout << "Error? " << tree->insert(elemento4) << endl;

	tree->dump("rdoArbol.txt");

	delete (tree);
}

void testFind() {
	BPlusTree* tree = new BPlusTree("AAA_myFile.dat", BLOCKSIZE);

	DatoElementoNodo* elemento = new DatoElementoNodo("a", 12);
	DatoElementoNodo* elemento1 = new DatoElementoNodo("b", 13);
	DatoElementoNodo* elemento2 = new DatoElementoNodo("c", 14);
	DatoElementoNodo* elemento3 = new DatoElementoNodo("d", 15);
	DatoElementoNodo* elemento4 = new DatoElementoNodo("e", 16);
	DatoElementoNodo* elemento5 = new DatoElementoNodo("f", 17);
	DatoElementoNodo* elemento6 = new DatoElementoNodo("g", 18);

	DatoElementoNodo* elementoBuscado = new DatoElementoNodo("c", 0);
	DatoElementoNodo* elementoRecuperado = new DatoElementoNodo("", 1);

	tree->insert(elemento);
	tree->insert(elemento1);
	tree->insert(elemento2);
	tree->insert(elemento3);
	tree->insert(elemento4);
	tree->insert(elemento5);
	tree->insert(elemento6);

	elementoRecuperado = tree->find(elementoBuscado);

	const char* aux = elementoRecuperado->getClave().c_str();
	cout << "RESULTADO: " << aux << endl;

	cout << "OFFSET 1er LIBRO: " << elementoRecuperado->getLibros().front()
			<< endl;
	cout << "OFFSET 1er LIBRO: " << elementoRecuperado->getLibros().back()
			<< endl;

	delete (elemento1);
	delete (elemento2);
	delete (elemento3);
	delete (elemento5);
	delete (elemento6);
	delete (elementoBuscado);
	delete (elementoRecuperado);
}
/*
int main() {

	BPlusTree* tree;
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	DatoElementoNodo* elemento = new DatoElementoNodo(
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 50);
	DatoElementoNodo* elemento1 = new DatoElementoNodo("aaaaaa", 18);
	DatoElementoNodo* elemento2 = new DatoElementoNodo("ddddddddd", 31);
	DatoElementoNodo* elemento3 = new DatoElementoNodo("gggggggggg", 61);
	DatoElementoNodo* elemento4 = new DatoElementoNodo("hhhhhhhhhhhhhhh", 71);
	DatoElementoNodo* elemento5 = new DatoElementoNodo(
			"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", 40);
	DatoElementoNodo* elemento6 = new DatoElementoNodo(
			"cccccccccccccccccccccccccccccc", 17);
	DatoElementoNodo* elemento7 = new DatoElementoNodo(
			"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee", 24);
	DatoElementoNodo* elemento8 = new DatoElementoNodo(
			"jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj", 32);
	DatoElementoNodo* elemento9 = new DatoElementoNodo(
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", 91);
	DatoElementoNodo* elemento10 = new DatoElementoNodo(
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", 92);
	DatoElementoNodo* elemento11 = new DatoElementoNodo(
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", 95);
	DatoElementoNodo* elemento12 = new DatoElementoNodo(
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", 97);
	DatoElementoNodo* elemento13 = new DatoElementoNodo(
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", 191);
	DatoElementoNodo* elemento14 = new DatoElementoNodo(
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", 91111);

	tree->insert(elemento);

	delete tree;
	delete (elemento);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento1);

	delete tree;
	delete (elemento1);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento2);

	delete tree;
	delete (elemento2);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento3);

	delete tree;
	delete (elemento3);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento4);

	delete tree;
	delete (elemento4);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento5);

	delete tree;
	delete (elemento5);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento6);

	delete tree;
	delete (elemento6);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento7);

	delete tree;
	delete (elemento7);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento8);

	delete tree;
	delete (elemento8);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento9);

	delete tree;
	delete (elemento9);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento10);

	delete tree;
	delete (elemento10);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento11);

	delete tree;
	delete (elemento11);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento12);

	delete tree;
	delete (elemento12);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento13);

	delete tree;
	delete (elemento13);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	tree->insert(elemento14);

	delete tree;
	delete (elemento14);
	tree = new BPlusTree("arbolito.dat", BLOCKSIZE);

	string dumpFileName = "text-tree.txt";
	tree->dump(dumpFileName);

	delete tree;

	/*
	 elemento->agregarLibro(5);
	 elemento->agregarLibro(10);
	 elemento->agregarLibro(100);
	 elemento->agregarLibro(1000);

	 */

	/*
	 elemento2->agregarLibro(4);
	 elemento2->agregarLibro(3);
	 elemento2->agregarLibro(2);
	 elemento2->agregarLibro(1);
	 */

	//tree->insert(elemento3);
	/*
	 tree->insert(elemento1);
	 tree->insert(elemento2);
	 tree->insert(elemento3);
	 tree->insert(elemento4);
	 */

	//tree->remove(elemento3);
	//elementoRecuperado = tree->find(elemento3);
	//elementoRecuperado2 = tree->find(elemento2);

	//const char* aux = elementoRecuperado->getClave().c_str();
	//cout << "RESULTADO: " << aux << endl;

	//list<uint32_t> libros = elementoRecuperado->getLibros();
	//list<uint32_t>::iterator it = libros.begin();
	//while (it != libros.end()) {
	//cout << "Libro: " << *it << endl;
	//++it;
	//}

	//cout << "OFFSET 1er LIBRO: " << elementoRecuperado->getLibros().front()<< endl;
	//cout << "OFFSET ULTIMO LIBRO: " << elementoRecuperado->getLibros().back()<< endl;
	/*
	 const char* aux2 = elementoRecuperado2->getClave().c_str();
	 cout<<"RESULTADO: "<<aux2<<endl;

	 cout<<"OFFSET 1er LIBRO: "<<elementoRecuperado2->getLibros().front()<<endl;
	 cout<<"OFFSET ULTIMO LIBRO: "<<elementoRecuperado2->getLibros().back()<<endl;


	 //	delete(elemento);
	 //	delete(elemento2);
	 //	delete(elementoRecuperado);
	 *
	 *


}
*/
