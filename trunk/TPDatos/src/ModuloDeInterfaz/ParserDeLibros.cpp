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
	/*
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
	*/

	//this->nombreArchivoStopWords = nombreArchivoStopWords;//por si acaso... no va a hacer falta.

	this->diccionarioStopWords = new Diccionario(nombreArchivoStopWords);

	this->diccionarioStopWords->cargarDiccionario();
};

ParserDeLibros::~ParserDeLibros()
{
	delete this->diccionarioStopWords;
};

void ParserDeLibros::procesarLineaLibro(std::string linea, Libro* libro)
{
	//Definir si la cadena tiene el formato especial de alguno de los campos especiales...
	std::string separadoresPalabras = " .,-;:¿?¡!'<@>)(";

	std::vector<std::string> palabrasDeLinea = ServiceClass::obtenerListaPalabras(linea, separadoresPalabras);

	std::vector<std::string>::iterator it_PalabrasDeLinea;

	for(it_PalabrasDeLinea = palabrasDeLinea.begin(); it_PalabrasDeLinea != palabrasDeLinea.end(); it_PalabrasDeLinea++)
	{
		std::string palabra = *it_PalabrasDeLinea;

		//Trabajamos todo en minúsculas.
		palabra = ServiceClass::toDowncase(palabra);

		//EstructuraStopWords::iterator it_StopWords = this->listaStopWords.find(palabra);
		bool esStopWord = this->diccionarioStopWords->existePalabra(palabra);
		//if( it_StopWords == this->listaStopWords.end() )
		if (!esStopWord)
		{
			libro->agregarPalabraClave(palabra);
		}

	}

	//Si tiene alguno de esos formatos, levantar el atributo correspondiente y cargarlo en el libro.

	//En caso contrario, agregar las palabras que correspondan a la lista de palabras del libro.
	//Se ignoran las stopwords y se pasan los filtros downcase y
}


void ParserDeLibros::procesarLineaLibroAtributos(std::string lineaLibro, bool &hayAutor, bool &hayTitulo, bool &hayEditorial)
{
	/* Terminar esto...
	std::vector<std::string> listaPalabras = ServiceClass::obtenerListaPalabras(lineaLibro, " ");

	if (listaPalabras.at(0) == FLAG_AUTOR)
	{
		hayAutor = true;
	}
	else if (listaPalabras.at(0) == FLAG_TITULO)
	{
		hayTitulo = true;
	}
	else if (listaPalabras.at(0) == FLAG_EDITORIAL)
	{
		hayEditorial = true;
	}
	*/
}


/*
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
*/

Libro* ParserDeLibros::parsearLibro(std::string nombreArchivo)
{
	Libro* libro = new Libro;

	std::ifstream archivoLibro;

	archivoLibro.open(nombreArchivo.c_str());

	std::string lineaLibro;


	bool hayAutor = false;
	bool hayTitulo = false;
	bool hayEditorial = false;

	if (archivoLibro.is_open())
	{
		//Primero se procesa el encabezado del libro y se buscan los atributos 'primarios'.
		/*
		while ( archivoLibro.good() && (!hayAutor || !hayTitulo || !hayEditorial))
		{
			getline (archivoLibro, lineaLibro);
			//Como se especificó en la estrategia de resolución del parser, no se empieza a formar
			//la lista de palbras del texto hasta haber encontrado los atributos 'autor', 'titulo' y editorial'
			procesarLineaLibroAtributos(lineaLibro, hayAutor, hayTitulo, hayEditorial);
		}
		*/

		//Luego se considera que empieza el libro propiamente dicho, y se inicia el listado de palabras.
	    while ( archivoLibro.good())
	    {
	      getline (archivoLibro, lineaLibro);

	      procesarLineaLibro(lineaLibro, libro);
	    }
	    archivoLibro.close();
	}
	else
	{
		throw "No se pudo abrir el archivo de libro";
		//std::sstream mensaje<<"asdf";
	}

	return libro;
};
