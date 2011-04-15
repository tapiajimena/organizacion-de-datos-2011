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

#ifndef PARSERDEATRIBUTO_H_
#define PARSERDEATRIBUTO_H_

#include "Libro.h"
#include "../ModuloDeTipos/DatoLibro.h"
#include "../Common/Constantes.h"
#include "../Common/Utilitarios/ServiceClass.h"
#include "../ModuloEstructuras/Diccionario.h"
#include <iostream>
#include <sstream>
#include <string>

class ParserDeAtributo {
public:
	//ParserDeAtributo();
	//virtual ~ParserDeAtributo();

	//Método abstracto que reimplementan los herederos.
	//Devuelve un libro en el que solamente se carga el atributo que es propio del
	//parser según su tipo específico (el resto de los atributos del libro quedan vacíos).
	virtual Libro* parsear(DatoLibro* datoLibro) = 0;
};

#endif /* PARSERDEATRIBUTO_H_ */
