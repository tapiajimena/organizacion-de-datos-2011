/*
 * Serializable.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include <iostream>

using namespace std;

class Serializable{

public:
	virtual void  serialize(iostream* ios)=0;
	virtual void deserialize(iostream* record)=0;
};


#endif /* SERIALIZABLE_H_ */
