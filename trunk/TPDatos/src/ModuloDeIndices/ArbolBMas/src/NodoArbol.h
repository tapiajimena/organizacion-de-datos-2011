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
#include "../../../ModuloDeTipos/Dato.h"

using namespace std;
class NodoArbol {
protected:
	int id;
	long int nodoPadre;

public:
	NodoArbol();

	virtual int insertar(Dato* dato)=0;
	virtual void partir(NodoArbol* hermano, int sizeBloque, Dato* keyPromovida, int idPromovido)=0;
	virtual int eliminar(Dato* dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int cantidadNodosLibres)=0;

	virtual bool isOverflowded(int sizeBloque)=0;
	virtual bool isUnderflowded(int sizeBloque)=0;

	/* Setters y Getters */
    void setId(int id);
    int getId() const;

	virtual ~NodoArbol();

};

#endif /* NODOARBOL_H_ */
