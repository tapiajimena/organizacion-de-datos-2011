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
#include "../../../ModuloDeTipos/DatoNodo.h"
#include "../../../ModuloDeTipos/DatoElementoNodo.h"
#include "../../../../Common/Constantes.h"
#include "NodoArbol.h"
#include "NodoHojaArbol.h"
#include "NodoInternoArbol.h"

using namespace ManejadorArchivo;
class ArbolBMas {
private:
	NodoArbol* 	raiz;
	uint32_t	offsetRaiz;
	fstream 	arcIndice;
	fstream 	arcNodosLibres;
	string		pathArcIndice;
	uint32_t	cantidadBloques;
	uint32_t	cantidadBloquesLibres;
	int 		orden;
	uint32_t	sizeBloque;
	int 		sizeMetaDataControl;
    int 		maxCantidadHijos;
    int 		minCantidadClaves;

public:
    ArbolBMas();
    ArbolBMas(string pathIndice, int sizeBloque);
    int insertar(DatoElementoNodo elemento);

    NodoArbol* leerNodo(int idNodo);

    void setDatoNodo(NodoArbol *nodo);

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

    int setMetaDataControl();
    string getMetaDataControl();

    void setOffsetRaiz(uint32_t offsetRaiz);
    void setPathArcIndice(string pathArcIndice);
    void setRaiz(NodoArbol *raiz);
    void setSizeBloque(int sizeBloque);
    int getSizeMetaDataControl() const;
    void setSizeMetaDataControl(int metaDataControl);

private:
	int insertarDatoRecursivo(DatoElementoNodo elemento, NodoArbol* nodoActual, DatoElementoNodo clavePromovida, int idNodoPromovido);
	void escribirNodo(NodoArbol* nodo);

public:
	virtual ~ArbolBMas();

};

#endif /* ARBOLBMAS_H_ */
