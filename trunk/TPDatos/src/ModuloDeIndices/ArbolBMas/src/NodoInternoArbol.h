/*
 * NodoInternoArbol.h
 *
 *    Autor   	 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 * Clase que representa los nodos internos (no hoja) del arbol.
 *
 */

#ifndef NODOINTERNOARBOL_H_
#define NODOINTERNOARBOL_H_

#include "NodoArbol.h"
#include <list>

using namespace std;

class NodoInternoArbol: public NodoArbol {
private:
	list<string> claves;
	list<int> hijos;

public:
	NodoInternoArbol();

	/* Getters y Setters */

    void setClaves(list<string> claves);
    void setHijos(list<int> hijos);

    virtual bool isOverflowded(int blockSize);
    virtual list<string> getClaves() const;
    virtual list<int> getHijos() const;

	virtual ~NodoInternoArbol();
};

#endif /* NODOINTERNOARBOL_H_ */
