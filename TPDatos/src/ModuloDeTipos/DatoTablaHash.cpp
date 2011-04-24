/*
 * DatoTablaHash.cpp
 *
 *  Created on: 22/04/2011
 *      Author: santi
 */

#include "DatoTablaHash.h"

DatoTablaHash::DatoTablaHash() {
}

DatoTablaHash::DatoTablaHash(std::stringstream* ss)
{
	//Leemos offset a cubeta
	ss->read(reinterpret_cast<char *> (&this->offsetCubeta), sizeof(this->offsetCubeta));

	//Leemos cantidad de elementos del bloque, QUE PUEDE TENER VARIAS CUBETAS y es la
	//suma de las cantidades de sus cubetas
	ss->read( reinterpret_cast<char* > (&this->cantidadDeElementos), sizeof(this->cantidadDeElementos));
}

DatoTablaHash::~DatoTablaHash() {
}

uint32_t DatoTablaHash::getOffsetCubeta()
{
	return this->offsetCubeta;
}

unsigned int DatoTablaHash::getCantidadDeElementos()
{
	return this->cantidadDeElementos;
}

void DatoTablaHash::serializarDatoTabla(iostream* ios)
{
	ios->write(reinterpret_cast<char *>(&this->offsetCubeta), sizeof(this->offsetCubeta));
	ios->write(reinterpret_cast<char *>(&this->cantidadDeElementos), sizeof(this->cantidadDeElementos));

}
