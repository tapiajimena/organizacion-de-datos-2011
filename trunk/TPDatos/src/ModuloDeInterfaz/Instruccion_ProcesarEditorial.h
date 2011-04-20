/*
 * Instruccion_ProcesarEditorial.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Se encarga de encapsular la logica con la que se genera un
 *  indice en funcion de las editoriales de los libros.
 *  Procesa los libros no procesados.
 *	Comando:
 *	./ejecutable –e
 *
 */

#ifndef INSTRUCCION_PROCESAREDITORIAL_H_
#define INSTRUCCION_PROCESAREDITORIAL_H_

#include "Instruccion.h"

class Instruccion_ProcesarEditorial: public Instruccion {
public:
	Instruccion_ProcesarEditorial(char id);

	virtual void ejecutar();

	virtual ~Instruccion_ProcesarEditorial();
};

#endif /* INSTRUCCION_PROCESAREDITORIAL_H_ */
