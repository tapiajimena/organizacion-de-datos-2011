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

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "ManejadorArchivo.h"
#include "../../Common/Constantes.h"
#include "../ModuloDeTipos/DatoControlLibro.h"
#include "../ModuloParser/ParserArchivoControl.h"
#include "../../Common/Utilitarios/Logger.h"

using namespace ManejadorArchivo;
using namespace std;

class ArchivoControlLibro {

private:
	ParserArchivoControl* parser;
	string pathArchivoControlLibro;
	fstream archivoControlLibro;
	bool archivoFragmentado;
	map<uint32_t,DatoControlLibro*>* libros;
	map<uint32_t,DatoControlLibro*>::iterator it;

	/**
	 * Devuelve el mejor offset para almacenar un libro desperdiciando la menor cantidad
	 * de espacio posible. Si no hay lugar, devuelve FIN_DE_ARCHIVO.
	 * @param espaciosLibres: lugares donde puede llegar a entrar el libro
	 * @param sizeAlmacenar: tamanio del libro
	 */
	uint32_t getMejorAjuste(list<DatoControlLibro*>* espaciosLibres, uint32_t sizeAlmacenar);

	list<DatoControlLibro*>* getEspaciosLibres();

	list<DatoControlLibro*>* fusionarEspaciosLibres(list<DatoControlLibro*>* espaciosLibres);

	void actualizarEspaciosLibres(list<DatoControlLibro*>* espaciosLibres);

public:
	ArchivoControlLibro();
	ArchivoControlLibro(string path);

	DatoControlLibro* buscarEnMap(uint32_t idLIbro);

	/**
	 * Se encarga de generar el map con los datos de control.
	 */
	void cargarLibros();

	/**
	 * Se fija en el archivo si ese libro esta indexado bajo algun
	 * tipo de indice.
	 * @param idLibro: libro que se quiere saber su indexacion.
	 * @return la lista con los tipos de indexamiento.
	 */
	list<char>* chequearIndexado(uint32_t idLIbro);

	list<char>* chequearIndexadoSinCarga(uint32_t idLibro);

	/**
	 * Devuelve el offset en el cual se puede continuar con la escritura.
	 * @param sizeAlmacenar: tamaño del dato a ser almacenado.
	 */
	uint32_t dondeEscribo(uint32_t sizeAlmacenar);

	/**
	 * Escribe en el registro de control que un libro se agrega en la
	 * biblioteca.
	 *
	 */
	uint32_t registrarLibro(uint32_t size, uint32_t finArcLibros);

	/**
	 * Coloca el tipo de indexacion al libro correspondiente.
	 * @param idLibro: id del libro que se indexa.
	 * @param tipoClave: char que representa el tipo de indice.
	 */
	void registrarIndexado(uint32_t idLibro, char tipoClave);

	/**
	 * Coloca el size del libro como el tamaño del espacio libre de un offset.
	 * @param idLibro: id del libro que se esta eliminando.
	 */
    void eliminarLibro(uint32_t idLibro, uint32_t size);

    /**
     * Verifica si el libro se encuentra eliminado.
     * @param idLibro: libro consultado.
     */
    bool estaEliminado(uint32_t idLibro);

    /**
     * Actualiza el archivo de control con los cambios realizados
     * durante las consultas.
     */
    void actualizarArchivo();

    /**
     * Metodos utilizados para calculos necesarios para nuevas inserciones en
     * espacios anteriormente asignados a otros libros.
     */
    uint32_t calcularNuevoOffset(uint32_t espacioLibre, uint32_t size, uint32_t idLibro);
    uint32_t calcularNuevoEspacioLibre(uint32_t espacioLibre, uint32_t nuevoOffset);

    string getPathArchivoControlLibro() const;
    void setPathArchivoControlLibro(string pathArchivoControlLibro);

	virtual ~ArchivoControlLibro();

    map<uint32_t,DatoControlLibro*> *getLibros();
    void setLibros(map<uint32_t,DatoControlLibro*> *libros);
};

#endif /* ARCHIVOCONTROLLIBRO_H_ */
