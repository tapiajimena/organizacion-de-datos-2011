/*
 * Dato.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Dato (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#ifndef DATO_H_
#define DATO_H_

#include <string>
#include <sstream>
#include <iostream>
#include <stdint.h>

using namespace std;
class Dato
{

public:
	stringstream dato;

public:
	Dato();
	Dato(char* d);
	Dato(string dato);
	Dato(const Dato & d);

	/**
	 *indica si el dato esta vacio
	 */
	bool estaVacio();


	/**
	 *vacia los dato
	 */
	void vaciar();

	string toString() const;
	char* toCharPointer();


	string getDato();
	void setDato(stringstream dato);
	void setDato(char* dato);
	void setDato(string dato);

	int getSize();



	virtual ~Dato();
};
#endif /* DATO_H_ */
