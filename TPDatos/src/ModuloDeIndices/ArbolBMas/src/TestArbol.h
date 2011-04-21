/*
 * testArbol.cpp
 *
 *    Autor   	 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 *	Test del arbol para llamar desde el main
 *
 */

#ifndef TESTARBOL_CPP_
#define TESTARBOL_CPP_

#include <iostream>
#include "ArbolBMas.h"
#include "./Common/Constantes.h"

using namespace std;


/*
 * se crea un arbol con su data de control y se muestra la data de control
 */
void testCrearArbol()
{
	stringstream 	ss;
	uint32_t 		sizeBloque;
	int 			cantidadBloques;
	ArbolBMas* 		arb = new ArbolBMas("IndiceArbol", SIZE_BLOQUE);

	arb->setMetaDataControl();
	ss.write(arb->getMetaDataControl().c_str(), arb->getMetaDataControl().length());//se lee la metadata en ss

	ss.seekp(0, ios_base::beg);
	ss.read(reinterpret_cast<char *>(&sizeBloque), sizeof(sizeBloque));
	ss.read(reinterpret_cast<char *>(&cantidadBloques), sizeof(cantidadBloques));

	cout<<"Tamano bloque: "<<sizeBloque<<endl;
	cout<<"Cantidad de bloques: "<<cantidadBloques<<endl;

	delete(arb);
}

void testSetHidratacionHoja()
{
	//se crea un nodoHoja y se le setea data (libros, id, tipo)
	NodoHojaArbol* raiz = new NodoHojaArbol();
	raiz->setId(0);

	raiz->agregarLibro(999);
	raiz->agregarLibro(512);
	raiz->agregarLibro(1024);

	//se crea un DatoNodo y se le setea un Nodo
	//o sea se seraliza la info de raiz en dNodo
	DatoNodo* dNodo = new DatoNodo();
	dNodo->setDatoNodo(raiz);

	delete(raiz);

	//se crea un nHoja auxliar para hidratarlo con el DatoNodo
	//para testear que se haya serializado y se hidrate bien
	NodoHojaArbol* nHoja = new NodoHojaArbol();
	dNodo->hidratar(nHoja);

	cout<<"Id Nodo: "<<nHoja->getId()<<endl;
	cout<<"Tipo Nodo: "<<nHoja->getTipoNodo()<<endl;
	list<uint32_t>* aux = nHoja->getIdLibros();
	for (list<uint32_t>::const_iterator ci = aux->begin(); ci != aux->end(); ci++)
		cout<<"Libro: "<<*ci<<endl;

	delete(nHoja);
	delete(dNodo);
}

void TestArbol()
{
	testCrearArbol();
	testSetHidratacionHoja();
}

#endif /* TESTARBOL_CPP_ */
