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

#ifndef PARSERDETITULO_H_
#define PARSERDETITULO_H_

#include "ParserDeAtributo.h"

class ParserDeTitulo : public ParserDeAtributo {
private:
	void ProcesarRenglonLibro(std::string renglonLibro, Libro* libro, bool &tituloEncontrado);

public:
	ParserDeTitulo();
	virtual ~ParserDeTitulo();

	Libro* parsear(DatoLibro* datoLibro);
};

#endif /* PARSERDETITULO_H_ */
