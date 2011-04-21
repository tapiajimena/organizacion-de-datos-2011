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
#include <fstream>
#include "Dato.h"
#include "../../Common/Constantes.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"
#include "../ModuloDeIndices/ArbolBMas/src/NodoHojaArbol.h"
#include "../ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.h"
#include <list>


class Dato;

using namespace ManejadorArchivo;
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

	/**
	 * se serializa la informacion del nodo en el atributo dato
	 */
	DatoNodo(const NodoInternoArbol* nodo);

	/*
	 * se serializa la informacion del nodo en el atributo dato
	 */
	DatoNodo(const NodoHojaArbol* nodo);


	/*
	* serializa la informacion del nodo en el atributo dato
	* @param nodo NodoHojaArbol a serializar
	*/
	void setDatoNodo(const NodoHojaArbol* nodo);

	/*
	 * TODO implementar
	* serializa la informacion del nodo en el atributo dato
	* @param nodo NodoInternoArbol a serializar
	*/
	void setDatoNodo(const NodoInternoArbol* nodo);

	/*
	 * se des-serializa la informacion contenida en el atributo dato y se
	 * completa esa informacion en nodoHoja
	 * @param nodoHoja NodoHoja a hidratar (completar con los datos de dato)
	 */
	void hidratar(NodoHojaArbol* nodoHoja);

	/**
	 * TODO implementar
	 */
	void  hidratar(NodoInternoArbol* nodoInterno);

	long int getSize();

	virtual ~DatoNodo();
};

#endif /* DATONODO_H_ */
