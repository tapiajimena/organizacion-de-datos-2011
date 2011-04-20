/*
 * Instruccion_ProcesarPalabras.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Se encarga de encapsular la logica con la que se genera un
 *  indice en funcion de los autores de los libros.
 *	Comando:
 *	./ejecutable –p
 *
 */

#ifndef INSTRUCCION_PROCESARPALABRAS_H_
#define INSTRUCCION_PROCESARPALABRAS_H_

#include "Instruccion.h"

class Instruccion_ProcesarPalabras: public Instruccion {
public:
	Instruccion_ProcesarPalabras(char id);

	virtual void ejecutar();

	virtual ~Instruccion_ProcesarPalabras();
};

#endif /* INSTRUCCION_PROCESARPALABRAS_H_ */
