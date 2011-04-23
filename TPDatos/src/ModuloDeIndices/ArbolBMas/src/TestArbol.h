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
#include "./src/ModuloDeTipos/DatoElementoNodo.h"
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

	ss.write(arb->getMetaDataControl().c_str(), arb->getMetaDataControl().length());//se lee la metadata en ss

	ss.seekp(0, ios_base::beg);
	ss.read(reinterpret_cast<char *>(&sizeBloque), sizeof(sizeBloque));
	ss.read(reinterpret_cast<char *>(&cantidadBloques), sizeof(cantidadBloques));

	cout<<"Tamano bloque: "<<sizeBloque<<endl;
	cout<<"Cantidad de bloques: "<<cantidadBloques<<endl;

	delete(arb);
}


void testInsertarArbol()
{
	stringstream 	ss;
	uint32_t 		sizeBloque;
	int 			cantidadBloques;
	ArbolBMas* 		arb = new ArbolBMas("IndiceArbol", SIZE_BLOQUE);

	arb->insertar("666");
	arb->insertar("pe");
	arb->insertar("peludo");
	arb->insertar("pirulo en el bosque");

	delete(arb);
}

void testSetHidratacionHoja()
{
	DatoElementoNodo* elemento = new DatoElementoNodo();
	elemento->setClave("Atlantida");
	elemento->agregarLibro((uint32_t)21);

	elemento->serializar();
	cout<<"SERIALIZACION: "<<elemento->getDato()<<endl;

	delete(elemento);
}


void TestArbol()
{
	cout<<"HOLA"<<endl;
	testSetHidratacionHoja();

}

#endif /* TESTARBOL_CPP_ */
