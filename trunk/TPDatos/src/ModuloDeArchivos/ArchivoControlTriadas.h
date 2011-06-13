/*
 * ArchicoControlTriadas.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *  Mantiene en un archivo el control de las triadas almacenadas.
 *  La estructura del archivo de control sera:
 *
 *
 *  idLibro|offsetInicial|offsetFinal|borrado|
 *      Donde:
 *      	-idLibro: offset a la biblioteca - identificador de libro.
 *      	-offsetInicial: Limite inferior del rango de triadas que pertenecen al mismo libro.
 *      	-offsetSuperior: Limite superior del rango de triadas que pertenecen al mismo libro.
 *      	-borrado: flag que permite saber si ese termino/libro fue eliminado.
 *
 */

#ifndef ARCHIVOCONTROLTRIADAS_H_
#define ARCHIVOCONTROLTRIADAS_H_

#include "../ModuloParser/ParserArchivoControlTriadas.h"

class ArchivoControlTriadas {
private:
	ParserArchivoControlTriadas* parser;
	string pathArchivoControlTriadas;
	fstream archivoControlTriadas;
public:
	ArchivoControlTriadas();
	ArchivoControlTriadas(string pathArchivoControlTriadas);

	void actualizarArchivo();
	void eliminarLibro(uint32_t idLibro);

	/* Getters y Setters */
	fstream getArchivoControlTriadas() const;
	ParserArchivoControlTriadas *getParser() const;
	string getPathArchivoControlTriadas() const;
	void setArchivoControlTriadas(fstream archivoControlTriadas);
	void setParser(ParserArchivoControlTriadas *parser);
	void setPathArchivoControlTriadas(string pathArchivoControlTriadas);

	virtual ~ArchivoControlTriadas();
};

#endif /* ARCHIVOCONTROLTRIADAS_H_ */
