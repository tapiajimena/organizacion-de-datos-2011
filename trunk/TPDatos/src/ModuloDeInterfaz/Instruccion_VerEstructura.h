/*
 * Instruccion_VerEstructura.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Genera archivos en forma de texto plano, que describen las
 *	estructuras y contenidos de los archivos de almacenamiento y
 *  control del sistema.
 */

#ifndef INSTRUCCION_VERESTRUCTURA_H_
#define INSTRUCCION_VERESTRUCTURA_H_

#include "Instruccion.h"

class Instruccion_VerEstructura: public Instruccion {
public:
	Instruccion_VerEstructura(char id, string argvs[]);

	virtual void ejecutar();

	virtual ~Instruccion_VerEstructura();
};

#endif /* INSTRUCCION_VERESTRUCTURA_H_ */
