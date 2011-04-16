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
	NodoArbol* 	raiz;
	uint32_t	offsetRaiz;
	fstream 	arcIndice;
	string		pathArcIndice;
	int 		orden;//Maxima cantidad de claves por nodo
	int 		maxCantidadHijos;
	int 		minCantidadClaves;
	int			sizeBloque;


public:
	ArbolBMas();

	ArbolBMas(string pathIndice, int sizeBloque);

	int insertar(Dato* dato);

	/* Getters y Setters */
    int getMaxCantidadHijos() const;
    int getMinCantidadClaves() const;
    int getOrden() const;
    void setMaxCantidadHijos();
    void setMinCantidadClaves();
    void setOrden(int orden);
    uint32_t getOffsetRaiz() const;
    string getPathArcIndice() const;
    NodoArbol *getRaiz() const;
    int getSizeBloque() const;
    void setOffsetRaiz(uint32_t offsetRaiz);
    void setPathArcIndice(string pathArcIndice);
    void setRaiz(NodoArbol *raiz);
    void setSizeBloque(int sizeBloque);

	virtual ~ArbolBMas();


};

#endif /* ARBOLBMAS_H_ */
