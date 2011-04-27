/*
 * ElementoHash.cpp
 *
 *  Created on: 22/04/2011
 *      Author: santi
 */

#include "ElementoHash.h"

ElementoHash::ElementoHash(std::string palabra, uint32_t offsetALibro) {
	this->palabra = palabra;
	this->offsetALibro = offsetALibro;

	//Tamaño: tamaño de string + tamaño unsigned int + tamaño uint32_t
	this->tamanioBytes = palabra.size()+4+4;
}

ElementoHash::~ElementoHash() {
}

unsigned int ElementoHash::getTamanioBytesEnDisco()
{
	return this->tamanioBytes;
}

std::string ElementoHash::getPalabra()
{
	return this->palabra;
}

uint32_t ElementoHash::getOffsetALibro()
{
	return this->offsetALibro;
}

void ElementoHash::serializarElementoHash(std::iostream* ios)
{
	//<tamanioBytes(n+8): 4bytes><offsetALibro: 4 bytes><palabra: n bytes>
	//std::stringstream ss;

	ios->write(reinterpret_cast<char *>(&this->tamanioBytes), sizeof(this->tamanioBytes));
	ios->write(reinterpret_cast<char *>(&this->offsetALibro), sizeof(this->offsetALibro));

	char* charPalabra = new char[palabra.size()+1];
	strcpy(charPalabra, palabra.c_str());
	ios->write(charPalabra, this->palabra.size()); //no se copia caracter final '\n'
	delete[] charPalabra;
	//manejador de archivos...

}

void ElementoHash::hidratarElementoHash(iostream* ios)
{
	//?
}
