/*
 * Diccionario.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Estructura que representa un diccionario.
 *
 */

#ifndef DICCIONARIO_H_
#define DICCIONARIO_H_

#include <set>
#include <fstream>
#include <iostream>

#include "../../Common/Constantes.h"
#include "../ModuloParser/ParserArchivoTexto.h"

using namespace std;

class Diccionario {
private:
	set<string>* diccionario;
	string nombreArchivo;
	ParserArchivoTexto* parser;
public:
	Diccionario(string nombreArchivo);

	//usar el manejador de archivo para levantar un archivo en .txt
	void cargarDiccionario();

	void mostrar();

	/**
	 * Metodo que verifica la existencia de una palabra dentro del
	 * diccionario
	 * @params palabra: palabra que se desea buscar.
	 */
	bool existePalabra(string palabra);

	virtual ~Diccionario();
};

#endif /* DICCIONARIO_H_ */
