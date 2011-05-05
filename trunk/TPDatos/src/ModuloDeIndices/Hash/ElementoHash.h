/*
 * ElementoHash.h
 *
 *  Created on: 22/04/2011
 *      Author: santi
 */

#ifndef ELEMENTOHASH_H_
#define ELEMENTOHASH_H_

#include "stdint.h"
#include <iostream>
#include <sstream>
#include <string>
#include "../../../Common/Utilitarios/ServiceClass.h"

class ElementoHash {
private:

	unsigned int tamanioBytes;
	std::string palabra;
	uint32_t offsetALibro;

public:

	bool esIgualAElemento(ElementoHash elemento);

	ElementoHash(std::string palabra, uint32_t offsetALibro);
	virtual ~ElementoHash();

	unsigned int getTamanioBytesEnDisco();
	std::string getPalabra();
	uint32_t getOffsetALibro();

	void serializarElementoHash(std::iostream* ios);

	void hidratarElementoHash(iostream* ios);
};

#endif /* ELEMENTOHASH_H_ */
