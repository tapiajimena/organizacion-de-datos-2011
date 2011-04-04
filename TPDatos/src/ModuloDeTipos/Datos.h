/*
 * Datos.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#ifndef DATOS_H_
#define DATOS_H_

#include <iostream>
#include <string>

using namespace std;

class Datos {

private:
	string datos;

public:
	Datos();
	Datos(char* d);
	Datos(string datos);
	Datos(const Datos & d);

	/**
	 * agrega Datos d en una posicion.
	 * Si la posicion es mayor al lenght devuelve false
	 */
	bool agregar(const Datos & d,unsigned int posicion);

	/**
	 *
	 */
	bool agregarAlFinal(const Datos & d);

	/**
	 *indica si el dato esta vacio
	 */
	bool vacio();


	/**
	 *vacia los datos
	 */
	void vaciar();

	string toString() const;
	char* toCharPointer();


	string getDatos();
    void setDatos(string datos);



	virtual ~Datos();
};

#endif /* DATOS_H_ */
;
