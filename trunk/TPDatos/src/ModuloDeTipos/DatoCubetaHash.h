/*
 * DatoCubetaHash.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Estructura encargada de la persistencia de una cubeta, de su serialización y de proveer servicios
 *	para operar con ella.
 *
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

#define METADATACUBETA 12 //Bytes de metadata que almacena la cubeta: 3 enteros de 4 bytes cada uno:
//bytesLibres
//offsetProximaCubeta
//cantidadDeElementos

class DatoCubetaHash : Dato{

private:

	unsigned int cantidadElementos;
	unsigned int bytesLibres;

	//Puntero a la próxima cubeta, en que continúan los datos de esta cubeta, en caso de que no
	//alcance su espacio para sus datos. Si no se usa se setea en cero ('0').
	uint32_t offsetProxCubeta;

	std::vector<ElementoHash> elementosHash;

public:

	DatoCubetaHash();

	//Creador con datos serializados. Se hidrata la estructura.
	DatoCubetaHash(std::stringstream* datoStream);

	//Devuelve UNA COPIA DEL VECTOR de elementos
	std::vector<ElementoHash> getElementos();

	//Si tiene lugar disponible, inserta el elemento y devuelve true, caso contrario,
	//devuelve false y no hace nada.
	bool insertarElementoHash(ElementoHash elemento);

	//Si existe el elemento ingresado
	void eliminarElementoHash(ElementoHash elemento);

	//Borra los elementos de adentro, pero no pierde el offset a la próxima cubeta (si se quiere resetear eso se puede setear a mano en cero).
	void vaciarCubeta();

	uint32_t getOffsetCubetaContinuacion();

	void setOffsetCubetaContinacion(uint32_t offsetCubetaContinuacion);

	unsigned int getCantidadDeElementos();

	bool contieneElemento(ElementoHash elemento);

	unsigned int getBytesLibres();

	virtual ~DatoCubetaHash();

	void serializarCubeta(std::iostream* ios);

};

#endif /* DATOCUBETAHASH_H_ */
