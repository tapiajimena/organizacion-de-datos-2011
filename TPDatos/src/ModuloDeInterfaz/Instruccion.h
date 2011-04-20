/*
 * Instruccion.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Clase que representa cada una de las instrucciones ingresadas
 *	por teclado.
 *
 */

#ifndef INSTRUCCION_H_
#define INSTRUCCION_H_

#include <sstream>
#include <string>
#include <iostream>
#include "../../Common/Constantes.h"
#include "../../Common/Utilitarios/Logger.h"

using namespace std;

class Instruccion {
private:
	char idInstruccion;
public:
	Instruccion(char id);
	char getIDInstruccion() const;
	void setIDInstruccion(char idInstruccion);

	/* Método que representa la actividad principal de
	 * cada instrucción. Será redefinido dependiendo del tipo
	 * de instrucción correspondiente.
	 */
	virtual void ejecutar()=0;

	virtual ~Instruccion();
};


#endif /* INSTRUCCION_H_ */
