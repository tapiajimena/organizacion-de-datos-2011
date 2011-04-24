/*
 * TestArchivoControlLibro.h
 *
 */

#ifndef TESTARCHIVOCONTROLLIBRO_H_
#define TESTARCHIVOCONTROLLIBRO_H_

#include <list>
#include <iostream>
#include "../src/ModuloDeArchivos/ArchivoControlLibro.h"
#include "../src/ModuloDeArchivos/ManejadorArchivo.h"

using namespace std;

class TestArchivoControlLibro {
private:
	ArchivoControlLibro* acl;
public:
	TestArchivoControlLibro(string pathArchivoControl);

	ArchivoControlLibro * getAcl() const;

	void testRegistrarIndexado();
	void testChequearIndexado();
	void testDondeEscribo();
	void testEliminarLibro();
	void testRegistrarLibro();

	void ejecutarPrueba();

	virtual ~TestArchivoControlLibro();
};

#endif /* TESTARCHIVOCONTROLLIBRO_H_ */
