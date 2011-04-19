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

class NodoInternoArbol : public NodoArbol {
private:
	list<string>* claves;
	list<int>* hijos;

public:
	NodoInternoArbol();

	virtual int insertar(Dato* dato);
	virtual void partir(NodoArbol* hermano, int sizeBloque, string clavePromovida, int idNodoPromovido);
	virtual int remover(Dato* dato, uint32_t offset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter);

	virtual bool isOverflowded(int blockSize);
    virtual bool isUnderflowded(int blockSize);


	/* Getters y Setters */
    void setClaves(list<string>* claves);
    void setHijos(list<int>* hijos);

    list<string>* getClaves() const;
    list<int>* getHijos() const;


	virtual ~NodoInternoArbol();
};

#endif /* NODOINTERNOARBOL_H_ */
