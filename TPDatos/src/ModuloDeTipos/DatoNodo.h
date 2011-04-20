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
#include "../ModuloDeIndices/ArbolBMas/src/NodoHojaArbol.h"
#include "../ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.h"
#include <list>


class Dato;

class DatoNodo: public Dato {

private:
	//TODO REPLANTEAR ATRIBUTOS DE CLASE DELEGAR A NODO
	uint32_t 		offset_continuacion;

	string 			claves;
	int 			size_claves;
	list<int>* 		hijos;
	int 			cantidad_hijos;
	int 			cantidad_libros;
	list<uint32_t>* idLibros;


public:

	DatoNodo();

	DatoNodo(const NodoInternoArbol* nodo);

	DatoNodo(const NodoHojaArbol* nodo);

	long int getSize();

	virtual ~DatoNodo();
};

#endif /* DATONODO_H_ */
