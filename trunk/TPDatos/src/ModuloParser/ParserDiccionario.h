/*
 * ParserDiccionario.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *  Parseador de archivos del tipo texto.
 *
 */


#ifndef PARSERDICCIONARIO_H_
#define PARSERDICCIONARIO_H_

#include <fstream>
#include <set>
#include <iostream>
#include <../Common/Utilitarios/ServiceClass.h> //Para pasar a minúsculas las palabras que se cargan.

#include "../../Common/Constantes.h"

using namespace std;

class ParserDiccionario {
private:
	string separador;
	set<string>* listaPalabras;
	set<string>::iterator it;
public:
	ParserDiccionario(string token);

	void leerArchivo(fstream* archivo);
	string getDato(string linea);
	set<string>* getLista();
	void cargarEstructura(string palabra);

	virtual ~ParserDiccionario();
};

#endif /* PARSERDICCIONARIO_H_ */
