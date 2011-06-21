/*
 * Instruccion_ConsultarOcurrenciaPosicional
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

#ifndef INSTRUCCION_CONSULTAROCURRENCIAPOSICIONAL_H_
#define INSTRUCCION_CONSULTAROCURRENCIAPOSICIONAL_H_

#include "Instruccion.h"
#include "../ModuloDeIndices/ConsultaIndice.h"


class Instruccion_ConsultarOcurrenciaPosicional: public Instruccion {
private:
	string titulo;
public:
	Instruccion_ConsultarOcurrenciaPosicional(char id, string consulta);

	virtual void ejecutar();

	virtual ~Instruccion_ConsultarOcurrenciaPosicional();
};

#endif /* INSTRUCCION_CONSULTAROCURRENCIAPOSICIONAL_H_ */
