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

	DatoCubetaHash(std::stringstream* datoStream);

	std::vector<ElementoHash> getElementos();

	uint32_t getOffsetCubetaContinuacion();

	unsigned int getCantidadDeElementos();

	unsigned int getBytesLibres();

	virtual ~DatoCubetaHash();

	std::string serializarCubeta();

};

#endif /* DATOCUBETAHASH_H_ */
