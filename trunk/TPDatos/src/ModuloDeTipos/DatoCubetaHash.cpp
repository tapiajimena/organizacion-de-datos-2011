/*
 * DatoCubetaHash.cpp
 *
 *  Created on: 22/04/2011
 *      Author: santi
 */

#include "DatoCubetaHash.h"

DatoCubetaHash::DatoCubetaHash()
{
	this->cantidadElementos = 0;
	this->offsetProxCubeta = 0;
	this->bytesLibres = TAMANIOCUBETA - METADATACUBETA; //12 bytes de metadata: bytes libres, cantidad de elementos y offset a prox. cubeta.
}

DatoCubetaHash::DatoCubetaHash(std::stringstream* datoStream)
{
	//Formato de dato en disco:
	//<bytesLibre: 4><offsetProxCubeta: 4><cantidadElementos: 4>< <ElementosHash: n>...<ElementoHash:m>: x>

	//this->datoCubeta = datoStream->str();

	datoStream->read(reinterpret_cast<char *>(&this->bytesLibres), sizeof(this->bytesLibres));

	datoStream->read(reinterpret_cast<char *>(&this->offsetProxCubeta), sizeof(this->offsetProxCubeta));

	datoStream->read(reinterpret_cast<char *>(&this->cantidadElementos), sizeof(this->cantidadElementos));


	//std::cout<<"BytesLibres: "<<this->bytesLibres<<std::endl;
	//std::cout<<"CantidadElementos: "<<this->cantidadElementos<<std::endl;

	//Si se usó la cubeta antes, se liberan recursos. No debería usarse de esa manera.
	if (!this->ElementosHash.empty())
	{
		this->ElementosHash.clear();
	}

	unsigned int posicionActual = 12; //Desde posición 12.
	unsigned int numeroElemento = 1;
	while (posicionActual <= TAMANIOCUBETA-8 && numeroElemento <= cantidadElementos)
	{
		//PERSISTIR ELEMENTOHASH

		//Tamanio
		unsigned int tamanioElemento;
		datoStream->read(reinterpret_cast<char *> (&tamanioElemento), sizeof(tamanioElemento));
		//std::cout<<"TamanioElemento: "<<tamanioElemento<<std::endl;

		//Offset
		uint32_t offsetALibro;
		datoStream->read(reinterpret_cast<char *> (&offsetALibro), sizeof(offsetALibro));
		//std::cout<<"OffsetLibro: "<<offsetALibro<<std::endl;

		//Palabra
		string aux="";
		char* palabra = new char[tamanioElemento-8];
		datoStream->read(palabra, (tamanioElemento-8));//8 bytes son 4 de offsetALibro y 4 de tamanioElemento.
		aux.append(palabra,(tamanioElemento-8));
		//std::cout<<"LPM: "<<aux <<std::endl;
		delete[] palabra;

		//Tamaño elemento es para saber cuánto leer en disco, pero elementoHash lo sabe por la
		//longitud de su palabra + 4 bytes del offset, por lo tanto no se le pasa. Al persistir, lo escribe.
		ElementoHash elementoHash(aux, offsetALibro);

		this->ElementosHash.push_back(elementoHash);

		posicionActual = posicionActual + tamanioElemento;
		numeroElemento++;
	}

}

DatoCubetaHash::~DatoCubetaHash() {
}

std::vector<ElementoHash> DatoCubetaHash::getElementos()
{
	return this->ElementosHash;
}

bool DatoCubetaHash::insertarElementoHash(ElementoHash elemento)
{
	unsigned int tamanioElemento = elemento.getTamanioBytesEnDisco();

	if ( tamanioElemento < this->bytesLibres)
	{
		this->ElementosHash.push_back(elemento);
		this->cantidadElementos++;
		this->bytesLibres = this->bytesLibres - tamanioElemento;

		return true;
	}

	return false;
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

void DatoCubetaHash::serializarCubeta(std::iostream* ios)
{
	//Bytes libres: unsigned int (4 bytes)
	ios->write(reinterpret_cast<char *> (&this->bytesLibres), sizeof(this->bytesLibres));

	//Offset a proxima cubeta: uint32_t(4 bytes)
	ios->write(reinterpret_cast<char *> (&this->offsetProxCubeta), sizeof(this->offsetProxCubeta));

	//Cantidad de elementos: unsigned int (4 bytes)
	ios->write(reinterpret_cast<char *> (&this->cantidadElementos), sizeof(this->cantidadElementos));

	std::vector<ElementoHash>::iterator it_elementos;
	for( it_elementos = this->ElementosHash.begin(); it_elementos != this->ElementosHash.end(); it_elementos++)
	{
		stringstream ssElemento;
		it_elementos->serializarElementoHash(&ssElemento);

		//Revisar esto, parece andar bien. ¿se duplica la escritura?
		*ios<<ssElemento.str();
		//Sino, usar algo del estilo ios->write(...) ver si hay que cambiar clase ios.
	}

	//Hash se debe encargar de rellenar los bytes que falten para llegar a TAMANIOCUBETA al escribir en disco.
}
