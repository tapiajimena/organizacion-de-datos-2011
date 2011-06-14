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

#include <fstream>
#include <iostream>
#include <map>
#include <stdint.h>

#include "../ModuloParser/ParserArchivoControlTriadas.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"

using namespace ManejadorArchivo;

class ArchivoControlTriadas {
private:
	ParserArchivoControlTriadas* parser;
	string pathArchivoControlTriadas;
	fstream archivoControlTriadas;
	map<uint32_t,DatoControlTriada*>* datosControl;
	map<uint32_t,DatoControlTriada*>::iterator it;
public:
	ArchivoControlTriadas();
	ArchivoControlTriadas(string pathArchivoControlTriadas);

	void actualizarArchivo();
	void eliminarLibro(uint32_t idLibro);
	DatoControlTriada* buscarEnMap(uint32_t idLIbro);

	/**
	 * Devuelve el nuevo offset donde se guardara la nueva triada
	 * en el archivo de triadas.
	 */
	uint32_t calcularNuevoOffset();

	/**
	 * Se encarga de generar el map con los datos de control.
	 */
	void cargarDatosControl();


	/* Getters y Setters */
	ParserArchivoControlTriadas *getParser() const;
	string getPathArchivoControlTriadas() const;
	void setArchivoControlTriadas(fstream archivoControlTriadas);
	void setParser(ParserArchivoControlTriadas *parser);
	void setPathArchivoControlTriadas(string pathArchivoControlTriadas);

	virtual ~ArchivoControlTriadas();
};

#endif /* ARCHIVOCONTROLTRIADAS_H_ */
