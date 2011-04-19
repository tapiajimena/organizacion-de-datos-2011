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

#include <fstream>
#include <stdint.h>
#include "./src/ModuloDeArchivos/ManejadorArchivo.h"
#include "./src/ModuloDeTipos/DatoNodo.h"
#include "./Common/Constantes.h"
#include "NodoArbol.h"
#include "NodoHojaArbol.h"
#include "NodoInternoArbol.h"

using namespace ManejadorArchivo;
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

	/*
	 * se prepara Dato para insertar en el arc con la informacion de Nodo.
	 */
	void setDatoNodo(NodoHojaArbol* nodo);


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

private:
	int insertarDatoRecursivo(Dato* dato, NodoArbol* nodoActual, string clavePromovida, int idNodoPromovido);

};

#endif /* ARBOLBMAS_H_ */
