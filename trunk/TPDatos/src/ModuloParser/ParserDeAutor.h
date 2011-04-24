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

#ifndef PARSERDEAUTOR_H_
#define PARSERDEAUTOR_H_

#include "ParserDeAtributo.h"

class ParserDeAutor : public ParserDeAtributo
{
private:
	void ProcesarRenglonLibro(std::string renglonLibro, Libro* libro, bool &autorEncontrado);

public:
	ParserDeAutor();
	virtual ~ParserDeAutor();

	Libro* parsear(DatoLibro* datoLibro);
};

#endif /* PARSERDEAUTOR_H_ */
