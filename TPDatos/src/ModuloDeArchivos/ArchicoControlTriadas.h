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

#ifndef ARCHICOCONTROLTRIADAS_H_
#define ARCHICOCONTROLTRIADAS_H_

#include "../ModuloParser/ParserArchivoControlTriadas.h"

class ArchicoControlTriadas {
private:
	ParserArchivoControlTriadas* parser;
	string pathArchivoControlTriadaas;
	fstream archivoControlTriadas;
public:
//
//	uint32_t dondeEscribo(uint32_t sizeAlmacenar);
//
//	/**
//	 * Escribe en el registro de control una triada nueva.
//	 */
//	uint32_t registrarTriada(uint32_t size, uint32_t finArcTriadas);
//
//	/**
//	 * @param idLibro: id del libro que se esta eliminando.
//	 */
//	void eliminarTriada(uint32_t idLibro);
//
//	/**
//	 * Actualiza el archivo de control con los cambios realizados
//	 * durante las consultas.
//	 */
//	void actualizarArchivo();
//
//	/**
//	 * Metodos utilizados para calculos necesarios para nuevas inserciones en
//	 * espacios anteriormente asignados a otros libros.
//	 */
//	uint32_t calcularNuevoOffset(uint32_t espacioLibre, uint32_t size,
//			uint32_t idLibro);
//	uint32_t calcularNuevoEspacioLibre(uint32_t espacioLibre,
//			uint32_t nuevoOffset);
//
//	string getPathArchivoControlTriadas() const;
//	void setPathArchivoControlTriadas(string path);
//
//	map<uint32_t, DatoControlLibro*> *getLibros();
//	void setLibros(map<uint32_t, DatoControlLibro*> *libros);

public:
	ArchicoControlTriadas();
	virtual ~ArchicoControlTriadas();
};

#endif /* ARCHICOCONTROLTRIADAS_H_ */
