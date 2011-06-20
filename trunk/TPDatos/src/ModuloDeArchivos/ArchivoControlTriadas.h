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
#include "../Common/Constantes.h"

using namespace ManejadorArchivo;

class ArchivoControlTriadas {
private:
	ParserArchivoControlTriadas* parser;
	string pathArchivoControlTriadas;
	fstream archivoControlTriadas;
	map<uint32_t,DatoControlTriada*>* datosControl;
	map<uint32_t,DatoControlTriada*>::iterator it;
	list<uint32_t>* offsets;
	bool datoEliminado;
public:
	ArchivoControlTriadas();
	ArchivoControlTriadas(string pathArchivoControlTriadas);

	void actualizarArchivo();
	void eliminarLibro(uint32_t idLibro);
	void eliminarDatoControl(uint32_t idLibro);
	DatoControlTriada* buscarEnMap(uint32_t idLIbro);

	uint32_t buscarOffsetDondeEscribir(int cantidadTriadas, uint32_t sizeArchivo);

	void agregarDatoControl(DatoControlTriada* nuevo);

	/**
	 * Devuelve el nuevo offset donde se guardara la nueva triada
	 * en el archivo de triadas.
	 */
	uint32_t calcularNuevoOffset();

	/**
	 * Se encarga de generar el map con los datos de control.
	 */
	void cargarDatosControl();

	/**
	 * Devuelve la lista de offsets correspondiente a todos las
	 * triadas que pertenecen a un libro.
	 * @param id_Libro: libro del cual se quieren obtener las triadas.
	 */
	list<uint32_t>* getTriadas(uint32_t id_Libro);

	void setDatoEliminado(bool e);

	bool getDatoEliminado();



	virtual ~ArchivoControlTriadas();
};

#endif /* ARCHIVOCONTROLTRIADAS_H_ */
