/*
 * ParserDeLibros.h
 *
 *    Autor		 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *	Clase que ofrece el servicio de parseo de los libros. Sirve para cargar los registros de la
 *	estructura libro desde un archivo de libro en formato .txt
 */

#ifndef PARSERDELIBROS_H_
#define PARSERDELIBROS_H_

#include "Libro.h"
#include "../Common/Utilitarios/ServiceClass.h"

class ParserDeLibros {

private:

	//Procesa la línea de caracteres y carga los datos obtenidos en la estructura del libro
	void procesarLineaLibro(std::string linea, Libro* libro);

	//Obtiene las stopwords de la línea y las carga en la estructura del parser, para que las tenga en cuenta
	void procesarLineaStopWords(std::string linea);

	//Nombre archivo de texto que contiene las stopwords
	//Stopwords son las palabras que se ignoran en los libros para el listado de palabras.
	std::string nombreArchivoStopWords;

	//Estructura para almacenar las stopwords
	//TODO habria que implementar algo mas eficiente que un string para esto?
	std::vector<std::string> listaStopWords;

public:
	ParserDeLibros(std::string nombreArchivoStopWords);
	~ParserDeLibros();

	//Parsea el archivo de libro pasado por parametro
	Libro* parsearLibro(std::string nombreArchivo);

};

#endif /* PARSERDELIBROS_H_ */
