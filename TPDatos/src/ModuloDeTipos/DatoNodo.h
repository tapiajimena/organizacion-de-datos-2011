/*
 * DatoNodo.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#ifndef DATONODO_H_
#define DATONODO_H_

/*
 *
 */
#include "Dato.h"
#include "../ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.h"
#include <list>



class DatoNodo: public Dato {

private:
	//TODO Implementar cuando un nodo no entra en un bloque.
	uint32_t offset_continuacion;

	int cantidad_hijos;
	list<int>* hijos;
	int size_claves;
	string claves;


public:

	DatoNodo();

	DatoNodo(const NodoInternoArbol* nodo);

	virtual ~DatoNodo();
};

#endif /* DATONODO_H_ */
