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
	std::string separadoresPalabras = " .-;:¿?¡!'<@>)(";
	std::vector<std::string> palabrasDeLinea = ServiceClass::obtenerListaPalabras(linea, separadoresPalabras);

	std::vector<std::string>::iterator it_PalabrasDeLinea;

	for(it_PalabrasDeLinea = palabrasDeLinea.begin(); it_PalabrasDeLinea != palabrasDeLinea.end(); it_PalabrasDeLinea++)
	{
		std::string palabra = *it_PalabrasDeLinea;

		EstructuraStopWords::iterator it_StopWords = this->listaStopWords.find(palabra);
		if( it_StopWords == this->listaStopWords.end() )
		{
			libro->agregarPalabraClave(palabra);
		}

	}

	//Si tiene alguno de esos formatos, levantar el atributo correspondiente y cargarlo en el libro.

	//En caso contrario, agregar las palabras que correspondan a la lista de palabras del libro.
	//Se ignoran las stopwords y se pasan los filtros downcase y
}

void ParserDeLibros::procesarLineaStopWords(std::string linea)
{

	//Definimos los separadores de los stop words
	std::string separadoresStopWords = " ,.-";

	std::vector<std::string> listaPalabras = ServiceClass::obtenerListaPalabras(linea, separadoresStopWords);

	for (std::vector<std::string>::iterator it_ListaPalabras = listaPalabras.begin(); it_ListaPalabras != listaPalabras.end(); it_ListaPalabras++)
	{
		std::string palabra = *it_ListaPalabras;
		//Incorporamos la nueva lista de palabras a la estructura del parser que las agrupa
		this->listaStopWords.insert( std::pair<std::string, int>(palabra, 0) ); //Si se repiten el map ignora la nueva entrada, y el segundo valor del map no interesa.

	}
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
