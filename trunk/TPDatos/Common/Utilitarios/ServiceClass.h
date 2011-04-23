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
#include <string.h>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



using namespace std;

class ServiceClass {
public:
	ServiceClass();

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

	/* Metodo que devuelve la fecha y la hora local */
	static string getFechaHora();

	/* Metodos de formato */
	static string toUppercase(string s);
	static string toDowncase(string s);

	/* Devuelve las palabras de una línea en un vector de palabras.
	 * Se toman como separadores de palabra los caracteres incluidos en
	 * el segundo parámetro.
	 *
	 * Separadores sugeridos: " ,.-"
	 */
	static vector<string> obtenerListaPalabras(string linea, string separadores);


	/* Separa el texo pasado por parámetro en renglones y los devuelve enlistados en
	 * un vector.
	 */
	vector<string> obtenerListaRenglones(string texto, char caracterFinDeLinea);

	/*
	 * Convierte a numero en un string
	 * @param numero nro a convertir
	 */
	static string toString(uint32_t numero);


	/**
	 * Normaliza todos los caracteres de la cadena de caracteres
	 * Quita las tildes y pone todos los caracteres en minúsculas.
	 */
	static string normalizarString(string cadena);

	/**
	 *
	 */
	static uint32_t convertirAUint32(string aux);

	/**
	 * Devuelve un string con los datos del vector separados por el
	 * separador indicado por parametro.
	 */
	static string toStringData(vector<string>* datos, string separador);

	virtual ~ServiceClass();
};

#endif /* SERVICECLASS_H_ */
