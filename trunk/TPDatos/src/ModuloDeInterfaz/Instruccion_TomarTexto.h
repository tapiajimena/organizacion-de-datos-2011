/*
 * Instruccion_TomarTexto.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Encapsula la logica que se encarga de levantar un archivo
 *	de texto correspondiente a un libro y lo indexa.
 *	Comando:
 *	./ejecutable -i "archivo de texto"
 *
 */

#ifndef INSTRUCCION_TOMARTEXTO_H_
#define INSTRUCCION_TOMARTEXTO_H_

#include "Instruccion.h"

class Instruccion_TomarTexto: public Instruccion {
private:
	string libroNuevo;
public:
	Instruccion_TomarTexto(char id, string pathLibro);

	virtual void ejecutar();

	virtual ~Instruccion_TomarTexto();
};

#endif /* INSTRUCCION_TOMARTEXTO_H_ */
