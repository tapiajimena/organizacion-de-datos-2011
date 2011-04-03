/*
 * Logger.h
 *
 *    Autor    : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 * Clase estatica utilizada para mostrar un mensaje de log.
 *
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include "ServiceClass.h"

using namespace std;

class Logger {
private:
	string mensaje;
public:
	Logger();

	/**
	 * Metodo que se encarga imprimir por pantalla el mensaje de log.
	 * @params	clase
	 * @params	metodo
	 * @params	mensaje
	 */
	static void log(string clase, string metodo, string mensaje);

	virtual ~Logger();
};

#endif /* LOGGER_H_ */
