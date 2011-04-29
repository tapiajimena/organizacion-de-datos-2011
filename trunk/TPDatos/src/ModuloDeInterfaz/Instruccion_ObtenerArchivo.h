/*
 * Instruccion_ObtenerArchivo.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Encapsula la logica con la cual se obtienen los archivos
 *	que se reciben por parametro.
 *	Comando:
 *	./ejecutable -o ID_Archivo
 */

#ifndef INSTRUCCION_OBTENERARCHIVO_H_
#define INSTRUCCION_OBTENERARCHIVO_H_

#include "Instruccion.h"

class Instruccion_ObtenerArchivo: public Instruccion {
private:
	uint32_t idLibro;
public:
	Instruccion_ObtenerArchivo(char id, uint32_t idLibro);

	virtual void ejecutar();

	virtual ~Instruccion_ObtenerArchivo();
};

#endif /* INSTRUCCION_OBTENERARCHIVO_H_ */
