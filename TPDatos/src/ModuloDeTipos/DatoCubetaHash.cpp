/*
 * DatoCubetaHash.cpp
 *
 *  Created on: 22/04/2011
 *      Author: santi
 */

#include "DatoCubetaHash.h"

DatoCubetaHash::DatoCubetaHash()
{
	std::string inicializacion(TAMANIOCUBETA, '0');

	this->datoCubeta = inicializacion;
	this->cantidadElementos = 0;
	this->offsetProxCubeta = 0;
}

DatoCubetaHash::DatoCubetaHash(std::stringstream* datoStream)
{
	//Formato de dato en disco:
	//<bytesLibre: 4><cantidadElementos: 4>< <ElementosHash: n>...<ElementoHash:m>: x><offsetProxCubeta: 4>

	//this->datoCubeta = datoStream->str();

	datoStream->read(reinterpret_cast<char *>(&this->bytesLibres), sizeof(this->bytesLibres));

	datoStream->read(reinterpret_cast<char *>(&this->cantidadElementos), sizeof(this->cantidadElementos));
	//cadenaNro = this->datoCubeta.substr(4, 4);
	//this->cantidadElementos = atoi(cadenaNro.c_str());
	std::cout<<"BytesLibres: "<<this->bytesLibres<<std::endl;
	std::cout<<"CantidadElementos: "<<this->cantidadElementos<<std::endl;
	unsigned int posicionActual = 8; //Desde posición 8.
	unsigned int numeroCubeta = 1;
	while (posicionActual <= TAMANIOCUBETA-4 && numeroCubeta <= cantidadElementos)
	{
		unsigned int tamanioElemento;
		datoStream->read(reinterpret_cast<char *> (&tamanioElemento), sizeof(tamanioElemento));
		std::cout<<"TamanioElemento: "<<tamanioElemento<<std::endl;

		uint32_t offsetALibro;
		string aux="";
		datoStream->read(reinterpret_cast<char *> (&offsetALibro), sizeof(offsetALibro));
		std::cout<<"OffsetLibro: "<<offsetALibro<<std::endl;
		char* palabra = new char[tamanioElemento-8];
		datoStream->read(palabra, (tamanioElemento-8));//8 bytes son 4 de offsetALibro y 4 de tamanioElemento.
		aux.append(palabra,(tamanioElemento-8));
		//palabra[tamanioElemento-8+1] = '\n';
		//std::string stringPalabra(palabra);
		std::cout<<"LPM: "<<aux <<std::endl; //son 15 caracteres, eso da ok, pero contienen basura... ??
		delete[] palabra;

		//Tamaño elemento es para saber cuánto leer en disco, pero elementoHash lo sabe por la
		//longitud de su palabra + 4 bytes del offset, por lo tanto no se le pasa. Al persistir, lo escribe.
		ElementoHash elementoHash(aux, offsetALibro);

		this->ElementosHash.push_back(elementoHash);

		posicionActual = posicionActual + tamanioElemento;
		numeroCubeta++;
	}

	datoStream->seekg(TAMANIOCUBETA-sizeof(this->offsetProxCubeta));

	datoStream->read(reinterpret_cast<char *>(&this->offsetProxCubeta), sizeof(this->offsetProxCubeta));
	std::cout<<"2"<<std::endl;
}

DatoCubetaHash::~DatoCubetaHash() {
}

std::vector<ElementoHash> DatoCubetaHash::getElementos()
{
	return this->ElementosHash;
}

uint32_t DatoCubetaHash::getOffsetCubetaContinuacion()
{
	return this->offsetProxCubeta;
}

unsigned int DatoCubetaHash::getCantidadDeElementos()
{
	return this->cantidadElementos;
}

unsigned int DatoCubetaHash::getBytesLibres()
{
	return this->bytesLibres;
}

std::string DatoCubetaHash::serializarCubeta()
{
	std::string cubetaSerializada;

	return cubetaSerializada;
}
