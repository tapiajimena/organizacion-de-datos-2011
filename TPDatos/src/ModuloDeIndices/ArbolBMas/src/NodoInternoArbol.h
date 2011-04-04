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

class NodoInternoArbol: NodoArbol {
private:
	list<int> claves;
	list<int> hijos;

public:
	NodoInternoArbol();

	/* Getters y Setters */
    list<int> getClaves() const;
    list<int> getHijos() const;
    void setClaves(list<int> claves);
    void setHijos(list<int> hijos);

	virtual ~NodoInternoArbol();
};

#endif /* NODOINTERNOARBOL_H_ */
