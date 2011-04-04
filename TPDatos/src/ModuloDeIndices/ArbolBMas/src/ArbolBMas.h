/*
 * ArbolBMas.h
 *
 *    Autor   	 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 *	Clase que representa la estructura del arbol.
 *
 */

#ifndef ARBOLBMAS_H_
#define ARBOLBMAS_H_

#include "NodoArbol.h"

class ArbolBMas {
private:
	NodoArbol* raiz;
	int maxCantidadHijos;
	int minCantidadClaves;
	/* Maxima cantidad de claves por nodo */
	int orden;
public:
	ArbolBMas();

	/* Getters y Setters */
    int getMaxCantidadHijos() const;
    int getMinCantidadClaves() const;
    int getOrden() const;
    void setMaxCantidadHijos();
    void setMinCantidadClaves();
    void setOrden(int orden);

	virtual ~ArbolBMas();

};

#endif /* ARBOLBMAS_H_ */
