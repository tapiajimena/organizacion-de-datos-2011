/*
 * Instruccion_ConsultarAutor.h
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

#ifndef INSTRUCCION_CONSULTARAUTOR_H_
#define INSTRUCCION_CONSULTARAUTOR_H_

#include "Instruccion.h"
#include "../ModuloDeIndices/ConsultaIndice.h"


class Instruccion_ConsultarAutor: public Instruccion {
private:
	string autor;
public:
	Instruccion_ConsultarAutor(char id, string consulta);

	virtual void ejecutar();

	virtual ~Instruccion_ConsultarAutor();
};

#endif /* INSTRUCCION_CONSULTARAUTOR_H_ */
