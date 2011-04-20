/*
 * Instruccion_ProcesarTitulo.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Se encarga de encapsular la logica con la que se genera un
 *  indice en funcion de los titulos de los libros.
 *	Comando:
 *	./ejecutable –t
 */

#ifndef INSTRUCCION_PROCESARTITULO_H_
#define INSTRUCCION_PROCESARTITULO_H_

#include "Instruccion.h"

class Instruccion_ProcesarTitulo: public Instruccion {
public:
	Instruccion_ProcesarTitulo(char id);

	virtual void ejecutar();

	virtual ~Instruccion_ProcesarTitulo();
};

#endif /* INSTRUCCION_PROCESARTITULO_H_ */
