/*
 * Dato.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 * Clase abstracta que generaliza aquellos tipos de datos que
 * seran persistidos.
 *
 */

#ifndef DATO_H_
#define DATO_H_

#include <iostream>
#include <string>

using namespace std;

class Dato {
protected:
	string dato;

public:
	Dato();

	/**
	 * Indica si el dato esta vacio
	 */
	bool vacio();

	/**
	 * Vacia los datos
	 */
	void vaciar();

	virtual string toString() const = 0;
	char* toCharPointer();

	/**
	 * Agrega un String s en una posicion.
	 * Si la posicion es mayor al length devuelve false.
	 */
	bool agregar(const Dato & d, unsigned int posicion);
	bool agregarAlFinal(const Dato & d);

	string getDato();
	long int getSize();
	void setDato(string s);

	virtual ~Dato();
};

#endif /* DATO_H_ */
