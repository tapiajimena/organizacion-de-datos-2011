/*
 * ParserDeEditorial.h
 *
 *    Autor		 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *	Clase que ofrece el servicio de parseo de editorial para los libros. Hereda de ParserDeAtributo.
 */

#ifndef PARSERDEEDITORIAL_H_
#define PARSERDEEDITORIAL_H_

#include "ParserDeAtributo.h"

class ParserDeEditorial : public ParserDeAtributo{
private:
	void ProcesarRenglonLibro(std::string renglonLibro, Libro* libro, bool &editorialEncontrada);
public:
	ParserDeEditorial();
	virtual ~ParserDeEditorial();

	Libro* parsear(DatoLibro* datoLibro);
};

#endif /* PARSERDEEDITORIAL_H_ */
