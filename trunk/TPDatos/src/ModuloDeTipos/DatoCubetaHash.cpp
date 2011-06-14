/*
 * DatoCubetaHash.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Estructura encargada de la persistencia de una cubeta, de su serialización y de proveer servicios
 *	para operar con ella.
 *
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
	if (!this->elementosHash.empty())
	{
		this->elementosHash.clear();
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

		this->elementosHash.push_back(elementoHash);

		posicionActual = posicionActual + tamanioElemento;
		numeroElemento++;
	}

}

DatoCubetaHash::~DatoCubetaHash() {
}

std::vector<ElementoHash> DatoCubetaHash::getElementos()
{
	return this->elementosHash;
}

bool DatoCubetaHash::contieneElemento(ElementoHash elemento)
{
	bool elementoYaIngresado = false;
	for( std::vector<ElementoHash>::iterator it_elementos = this->elementosHash.begin(); it_elementos != this->elementosHash.end() && !elementoYaIngresado; it_elementos++)
	{
		elementoYaIngresado = elemento.esIgualAElemento(*it_elementos);
	}

	return elementoYaIngresado;
}

bool DatoCubetaHash::contieneElementoConIgualClave(ElementoHash elemento)
{
	bool claveYaAparecida = false;

	for( std::vector<ElementoHash>::iterator it_elementos = this->elementosHash.begin(); it_elementos != this->elementosHash.end() && !claveYaAparecida; it_elementos++)
	{
		if (elemento.getPalabra() == (*it_elementos).getPalabra())
		{
			claveYaAparecida = true;
		}
	}

	return claveYaAparecida;
}

bool DatoCubetaHash::insertarElementoHash(ElementoHash elemento)
{
	unsigned int tamanioElemento = elemento.getTamanioBytesEnDisco();

	if ( tamanioElemento < this->bytesLibres)
	{
		this->elementosHash.push_back(elemento);
		this->cantidadElementos++;
		this->bytesLibres = this->bytesLibres - tamanioElemento;

		return true;
	}

	return false;
}

void DatoCubetaHash::eliminarElementoHash(ElementoHash elemento)
{
	bool encontrado = false;
	for(std::vector<ElementoHash>::iterator it_elementos = this->elementosHash.begin(); it_elementos != this->elementosHash.end() && !encontrado ; it_elementos++)
	{
		if( it_elementos->esIgualAElemento(elemento) )
		{
			encontrado = true;
			this->elementosHash.erase(it_elementos);
			this->cantidadElementos = this->cantidadElementos - 1;
			this->bytesLibres = this->bytesLibres + elemento.getTamanioBytesEnDisco();
		}
	}
}

void DatoCubetaHash::vaciarCubeta()
{
	this->bytesLibres = TAMANIOCUBETA - METADATACUBETA;
	this->cantidadElementos = 0;
	this->elementosHash.clear();
}

uint32_t DatoCubetaHash::getOffsetCubetaContinuacion()
{
	return this->offsetProxCubeta;
}

void DatoCubetaHash::setOffsetCubetaContinacion(uint32_t offsetCubetaContinuacion)
{
	this->offsetProxCubeta = offsetCubetaContinuacion;
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
	for( it_elementos = this->elementosHash.begin(); it_elementos != this->elementosHash.end(); it_elementos++)
	{
		stringstream ssElemento;
		it_elementos->serializarElementoHash(&ssElemento);

		//Revisar esto, parece andar bien. ¿se duplica la escritura?
		*ios<<ssElemento.str();
		//Sino, usar algo del estilo ios->write(...) ver si hay que cambiar clase ios.
	}

	//Hash se debe encargar de rellenar los bytes que falten para llegar a TAMANIOCUBETA al escribir en disco.
}
