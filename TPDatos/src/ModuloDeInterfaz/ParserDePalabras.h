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

#ifndef PARSERDEPALABRAS_H_
#define PARSERDEPALABRAS_H_

#include "ParserDeAtributo.h"
#include "../Common/Utilitarios/ServiceClass.h"
#include "../ModuloEstructuras/Diccionario.h"

class ParserDePalabras : public ParserDeAtributo {
private:

	//Procesa la línea de caracteres y carga los datos obtenidos en la estructura del libro
	void procesarLineaLibro(std::string linea, Libro* libro);

	Diccionario* diccionarioStopWords;

public:
	ParserDePalabras(std::string nombreArchivoStopWords);
	virtual ~ParserDePalabras();

	Libro* parsear(DatoLibro* datoLibro);
};

#endif /* PARSERDEPALABRAS_H_ */
