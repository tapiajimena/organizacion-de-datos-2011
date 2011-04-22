/*
 * FabricaDeNodos.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#ifndef FABRICADENODOS_H_
#define FABRICADENODOS_H_

#include"NodoArbol.h"

/*
 *
 */
class FabricaDeNodos
{
public:
	FabricaDeNodos();

	void asignarId(NodoArbol* nodo, unsigned int* cantidadNodos, unsigned int* nodosLibres, fstream* fs);


	virtual ~FabricaDeNodos();
};

#endif /* FABRICADENODOS_H_ */
