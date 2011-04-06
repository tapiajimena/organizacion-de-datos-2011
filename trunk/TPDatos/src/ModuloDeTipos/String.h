/*
 * String.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 * Clase wrapper del string.
 *
 */

#ifndef STRING_H_
#define STRING_H_

#include <iostream>
#include <string>
#include "Dato.h"

using namespace std;

class String: public Dato {
public:
	String();

	String(char* s);
	String(string s);
	String(const String & s);

	virtual string toString() const;

	virtual ~String();
};

#endif /* STRING_H_ */
