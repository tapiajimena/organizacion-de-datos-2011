/*
 * ParserDeLibros.cpp
 *
 */

#include "ParserDeLibros.h"
#include <iostream>
#include <fstream>
#include <string.h>

ParserDeLibros::ParserDeLibros(std::string nombreArchivoStopWords)
{

	//Cargamos lista de stopwords

	std::ifstream archivoStopWords;
	archivoStopWords.open( nombreArchivoStopWords.c_str() );

	std::string linea;

	if (archivoStopWords.is_open())
	{
	    while ( archivoStopWords.good() )
	    {
	      getline (archivoStopWords, linea);

	      procesarLineaStopWords(linea);
	      //cout << line << endl; //TODO salida al log
	    }
	    archivoStopWords.close();
	}
	else
	{
		throw "No se pudo abrir el archivo de stopwords";
	}
};

ParserDeLibros::~ParserDeLibros()
{

};

void ParserDeLibros::procesarLineaLibro(std::string linea, Libro* libro)
{
	//Definir si la cadena tiene el formato especial de alguno de los campos especiales...


	//Si tiene alguno de esos formatos, levantar el atributo correspondiente y cargarlo en el libro.

	//En caso contrario, agregar las palabras que correspondan a la lista de palabras del libro.
	//Se ignoran las stopwords y se pasan los filtros downcase y
}

void ParserDeLibros::procesarLineaStopWords(std::string linea)
{

	//Definimos los separadores de los stop words
	std::string separadoresStopWords = " ,.-";

	std::vector<std::string> listaPalabras = ServiceClass::obtenerListaPalabras(linea, separadoresStopWords);

	//Incorporamos la nueva lista de palabras a la estructura del parser que las agrupa
	this->listaStopWords.insert(this->listaStopWords.end(), listaPalabras.begin(), listaPalabras.end());
}

Libro* ParserDeLibros::parsearLibro(std::string nombreArchivo)
{
	Libro* libro = new Libro;

	std::ifstream archivoLibro;

	archivoLibro.open(nombreArchivo.c_str());

	std::string lineaLibro;

	if (archivoLibro.is_open())
	{
	    while ( archivoLibro.good() )
	    {
	      getline (archivoLibro, lineaLibro);

	      procesarLineaLibro(lineaLibro, libro);
	      //cout << line << endl; //salida al log
	    }
	    archivoLibro.close();
	}
	else
	{
		throw "No se pudo abrir el archivo de libro";
	}

	return libro;
};
