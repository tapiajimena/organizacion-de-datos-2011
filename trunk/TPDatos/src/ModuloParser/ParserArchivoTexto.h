/*
 * ParserArchivoTexto.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *  Parseador de archivos del tipo texto.
 *
 */


#ifndef PARSERARCHIVOTEXTO_H_
#define PARSERARCHIVOTEXTO_H_

#include <fstream>
#include <set>
#include <iostream>

#include "Constantes.h"

using namespace std;

class ParserArchivoTexto {
private:
	string separador;
	set<string>* listaPalabras;
	set<string>::iterator it;
public:
	ParserArchivoTexto(string token);

	void leerArchivo(fstream* archivo);
	string getDato(string linea);
	set<string>* getLista();
	void cargarEstructura(string palabra);

	virtual ~ParserArchivoTexto();
};

#endif /* PARSERARCHIVOTEXTO_H_ */
