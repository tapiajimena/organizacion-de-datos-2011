/*
 * Instruccion_ConsultaNormaInfinito.h
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

#ifndef INSTRUCCION_CONSULTARNORMAINFINITO_H_
#define INSTRUCCION_CONSULTARNORMAINFINITO_H_

#include "Instruccion.h"
#include "../ModuloControladores/ControladorBiblioteca.h"
#include "../ModuloEstructuras/CalculadorDeNormas.h"


class Instruccion_ConsultarNormaInfinito: public Instruccion {
private:
	string titulo;

	ControladorBiblioteca* controladorBiblioteca;

	ArchivoTerminos* archivoTerminos;

	ControladorIndice* controladorIndice;

	CalculadorDeNormas* calculadorDeNormas;

public:
	Instruccion_ConsultarNormaInfinito(char id, string consulta);

	virtual void ejecutar();

	virtual ~Instruccion_ConsultarNormaInfinito();
};

#endif /* INSTRUCCION_CONSULTARNORMAINFINITO_H_*/
