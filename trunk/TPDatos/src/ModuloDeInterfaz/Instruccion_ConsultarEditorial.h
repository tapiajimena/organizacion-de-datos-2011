/*
 * Instruccion_ConsultarEditorial.h
 *
 *	Editorial	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Se encarga de encapsular la logica con la que se genera un
 *  indice en funcion de los titulos de los libros.
 *	Comando:
 *	./ejecutable –t
 */

#ifndef INSTRUCCION_CONSULTAREDITORIAL_H_
#define INSTRUCCION_CONSULTAREDITORIALH_

#include "Instruccion.h"
#include "../ModuloDeIndices/ConsultaIndice.h"


class Instruccion_ConsultarEditorial: public Instruccion {
private:
	string editorial;
public:
	Instruccion_ConsultarEditorial(char id, string consulta);

	virtual void ejecutar();

	virtual ~Instruccion_ConsultarEditorial();
};

#endif /* INSTRUCCION_CONSULTAREDITORIAL_H_ */
