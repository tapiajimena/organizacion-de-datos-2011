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

using namespace std;
class Dato
{

private:
	stringstream dato;

public:
	Dato();
	Dato(char* d);
	Dato(string dato);
	Dato(const Dato & d);

	/**
	 * agrega Dato d en una posicion.
	 * Si la posicion es mayor al lenght devuelve false
	 */
	bool agregar(const Dato & d,unsigned int posicion);

	/**
	 *
	 */
	bool agregarAlFinal(const Dato & d);

	/**
	 *indica si el dato esta vacio
	 */
	bool vacio();


	/**
	 *vacia los dato
	 */
	void vaciar();

	string toString() const;
	char* toCharPointer();


	string getDatos();
    void setDatos(stringstream dato);
    void setDatos(char* dato);

    long int getSize();



	virtual ~Dato();
};
#endif /* DATO_H_ */
