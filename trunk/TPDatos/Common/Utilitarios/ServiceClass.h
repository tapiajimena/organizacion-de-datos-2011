/*
 * ServiceClass.h
 *
 *    Autor		 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 * Clase estatica utilizada para agrupar funciones que brindan
 * servicios a los objetos que la utilizan como por ejemplo
 * validacion, formato, convercion de tipos, etc.
 *
 */

#ifndef SERVICECLASS_H_
#define SERVICECLASS_H_

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <time.h>

using namespace std;

class ServiceClass {
public:
	ServiceClass();

	/* Metodos para manejo de archivos */
	static string agregarExtensionArchivo(string valor);
	static string obtenerNombreArchivo(string valor);

	/* Metodos usados para realizar casteos */
	static string obtenerString(unsigned int valor);
	static unsigned int obtenerNumero(string valor);
	static const unsigned char* obtenerPuntero(const string & valor);

	/* Chequea si esta en el rango */
	static bool estaEntre(unsigned int valor1, unsigned int valor2, unsigned int valor);

	/* Recibe una fecha con formato string DD MM AAAA
	 * y la devuelve en int como AAAA MM DD
	 */
	static int devolverFechaInt(string valor);

	/* Metodo que devuelve la cantidad de lineas
	 * en el string
	 */
	static int getLineas(string texto);

	/* Metodo que devuelve el largo de la linea
	 * mas larga en el texto
	 */
	static unsigned int getMaxLargoLinea(string texto);

	/* Metodo que devuelve la fecha y la hora local */
	static string getFechaHora();

	/* Metodos de formato */
	static string toUppercase(string s);
	static string toDowncase(string s);

	virtual ~ServiceClass();
};

#endif /* SERVICECLASS_H_ */
