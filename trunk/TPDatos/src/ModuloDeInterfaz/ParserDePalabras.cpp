/*
 * ParserDePalabras.cpp
 *
 *  Created on: 12/04/2011
 *      Author: santi
 */

#include "ParserDePalabras.h"

ParserDePalabras::ParserDePalabras(std::string nombreArchivoStopWords) {

	this->diccionarioStopWords = new Diccionario(nombreArchivoStopWords);

	this->diccionarioStopWords->cargarDiccionario();
}

ParserDePalabras::~ParserDePalabras() {
	delete this->diccionarioStopWords;
}

void ParserDePalabras::procesarLineaLibro(std::string linea, Libro* libro)
{
	//Definir si la cadena tiene el formato especial de alguno de los campos especiales...

	{

Libro* ParserDePalabras::parsear(DatoLibro* datoLibro)
{

	//Creamos un libro vacío. Se le carga sólo la editorial.
   	Libro* libro = new Libro();

	//bool tituloEncontrado = false;
	bool finCadena = false;
				finCadena = true;
				if(posicionInicio < cadenaLibro.size()-1)
				{
					renglonLibro = cadenaLibro.substr(posicionInicio, cadenaLibro.size()-1);
				}
				else
					renglonLibro = "";
				}


}