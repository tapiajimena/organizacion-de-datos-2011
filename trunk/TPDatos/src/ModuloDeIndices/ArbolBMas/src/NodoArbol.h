/*
 * NodoArbol.h
 *
 *    Autor   	 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 *	Clase utilizada como interfaz para los nodos del arbol.
 *
 */

#ifndef NODOARBOL_H_
#define NODOARBOL_H_

#include <list>

class NodoArbol {
protected:
	int id;
	long int nodoPadre;
public:
	NodoArbol();

	virtual bool isOverflowded(int blockSize)=0;

	/* Setters y Getters */
    void setId(int id);
    int getId() const;

    virtual list<int> getHijos() const=0;
    virtual list<string> getClaves() const=0;

	virtual ~NodoArbol();

};

#endif /* NODOARBOL_H_ */
