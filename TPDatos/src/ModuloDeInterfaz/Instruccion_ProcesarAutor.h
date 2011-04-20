/*
 * Instruccion_ProcesarAutor.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Se encarga de encapsular la logica con la que se genera un
 *  indice en funcion de los autores de los libros.
 *	Comando:
 *	./ejecutable –a
 *
 */

#ifndef INSTRUCCION_PROCESARAUTOR_H_
#define INSTRUCCION_PROCESARAUTOR_H_

#include "Instruccion.h"

class Instruccion_ProcesarAutor: public Instruccion {
public:
	Instruccion_ProcesarAutor(char id);

	virtual void ejecutar();

	virtual ~Instruccion_ProcesarAutor();
};

#endif /* INSTRUCCION_PROCESARAUTOR_H_ */
