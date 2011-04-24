/*
 * DatoCubetaHash.h
 *
 *  Created on: 22/04/2011
 *      Author: santi
 */

#ifndef DATOCUBETAHASH_H_
#define DATOCUBETAHASH_H_

#include "Dato.h"
#include "../../Common/Constantes.h"
#include "../ModuloDeIndices/Hash/ElementoHash.h"
#include "stdint.h"
#include <vector>
#include <stdlib.h>
//#include <iostream.h>
#include <string>

class DatoCubetaHash : Dato{

private:

	unsigned int cantidadElementos;
	unsigned int bytesLibres;
	std::vector<ElementoHash> ElementosHash;

	//Puntero a la próxima cubeta, en que continúan los datos de esta cubeta, en caso de que no
	//alcance su espacio para sus datos. Si no se usa se setea en cero ('0').
	uint32_t offsetProxCubeta;
public:

	DatoCubetaHash();

	//Creador con datos serializados. Se hidrata la estructura.
	DatoCubetaHash(std::stringstream* datoStream);

	//Devuelve UNA COPIA DEL VECTOR de elementos
	std::vector<ElementoHash> getElementos();

	//Si tiene lugar disponible, inserta el elemento y devuelve true, caso contrario,
	//devuelve false y no hace nada.
	bool insertarElementoHash(ElementoHash elemento);

	uint32_t getOffsetCubetaContinuacion();

	unsigned int getCantidadDeElementos();

	unsigned int getBytesLibres();

	virtual ~DatoCubetaHash();

	void serializarCubeta(std::iostream* ios);

};

#endif /* DATOCUBETAHASH_H_ */
