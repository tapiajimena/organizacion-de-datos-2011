/*
 * DatoTablaHash.h
 *
 *  Created on: 22/04/2011
 *      Author: santi
 */

#ifndef DATOTABLAHASH_H_
#define DATOTABLAHASH_H_

#include "Dato.h"
#include "stdint.h"
//#include "../ModuloDeIndices/Hash/Hash.h"

class DatoTablaHash: public Dato {

private:
	//Offset a su cubeta correspondiente en el archivo de cubetas (a la primera, en caso de que tenga que tener varias).
	uint32_t offsetCubeta;

	//Cantidad de elementos en su cubeta (si tiene 1 sola cubeta, coincide con el de la cubeta).
	unsigned int cantidadDeElementos;

public:
	DatoTablaHash();

	DatoTablaHash(std::stringstream* ss);

	virtual ~DatoTablaHash();

	uint32_t getOffsetCubeta();

	unsigned int getCantidadDeElementos();

	void setOffsetCubeta(uint32_t offsetCubeta);

	void setCantidadDeElementos(unsigned int cantidadDeElementos);

	void serializarDatoTabla(iostream* ios);

};

#endif /* DATOTABLAHASH_H_ */
