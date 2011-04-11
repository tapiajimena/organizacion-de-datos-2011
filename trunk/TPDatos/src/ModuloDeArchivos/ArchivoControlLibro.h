/*
 * ArchivoControlLibro.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  Mantiene en un archivo el control de los libros almacenados en la biblioteca.
 *  La estructura del archivo de control sera:
 *  idLibro|sizeLibre|TagAutor|TagEditorial|TagTitulo|TagPalabras (se inicializan en 0 los tags)
 *      Donde:
 *      	-idLibro: offset a la biblioteca
 *      	-sizeLibre: espacio libre en el bloque.
 *      	-flags: un char de 4 donde cada uno represente un tipo de clave (editorial, autor, tit, palabra)
  *
 */

#ifndef ARCHIVOCONTROLLIBRO_H_
#define ARCHIVOCONTROLLIBRO_H_

#include <map>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "ManejadorArchivo.h"
#include "./Common/Constantes.h"
#include "../ModuloDeTipos/DatoControlLibro.h"


class ArchivoControlLibro {
private:
	fstream archivoControlLibro;
	map<uint32_t, DatoControlLibro> controlLibros;

public:
	ArchivoControlLibro();
	ArchivoControlLibro(string path);

	/**
	 *
	 */
	bool chequearIndexado(uint32_t idLIbro);

	/*
	 *
	 */
	uint32_t dondeEscribo(uint32_t sizeAlmacenar);

	/*
	 *Escribe en el registro de control que un libro agregarse en la biblioteca.
	 */
	void registrarLibro(uint32_t idLibro);

	/*
	 *
	 */
	void registrarIndexado(uint32_t idLibro, char tipoClave);



	virtual ~ArchivoControlLibro();
};

#endif /* ARCHIVOCONTROLLIBRO_H_ */
