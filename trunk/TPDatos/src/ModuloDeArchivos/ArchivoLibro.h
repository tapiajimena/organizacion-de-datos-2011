/*
 * ArchivoLibro.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      Lee, escribe, maneja y controla los registros variables en archivos.
 *      
 */

#ifndef ARCHIVOVARIABLE_H_
#define ARCHIVOVARIABLE_H_

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "ManejadorArchivo.h"
#include "./Common/Utilitarios/Logger.h"
#include "../ModuloDeTipos/DatoLibro.h"


class ArchivoLibro {

private:
	string path;//lugar fisico donde se encuentra el archivoVariable
	fstream archivoVariable; //biblioteca donde se van a guardar los libros

public:
	ArchivoLibro();

	/**
	 * Abre de forma binaria el archivo de ruta pathArchivo, si no existe lo crea si existe lo borra e inicializa el path.
	 * pathArchivo: direccion + nombre de archivo + extension
	 */
	ArchivoLibro(string pathArchivo);


	/**
	 * Abre de forma binaria el archivo de path pathArchivo
	 */
	void abrir();

	/**
	 * ingresa el libro de path pathLibro a la libreria (archivoVariable).
	 * almacena el archivo al final de la libreria.
	 * pathLibro: ruta+nombre del archivo que se quiere agregar a la biblioteca
	 */
	void agregarLibro(char* pathLibro);


	DatoLibro recuperarLibro(uint32_t idLibro);

	/**
	 *lee un dato del archivo de biblioteca en la posicion que se encuentre el cursor del archivo.
	 *para recorrer toda la biblioteca habr�a que ir al inicio de la misma.
	 */
	string recuperarBiblioteca();

	/**
	 * TODO implementar
	 * eliminar registro que se encuentra en al posicion offset
	 */
	void eliminar(uint32_t offset);

	/**
	 *posiciona el puntero del archivo en el inicio.
	 */
	void irAlInicio();

	/**
	 * devuelve true si se llego al final del archivo
	 */
	bool finArchivo();

	/**
	 * devuelve el tamanio del archivo biblioteca.
	 *deja posicionado el puntero del archivo de biblioteca en el final
	 */
	uint32_t getSizeArchivo();

	/**
	 * devuelve la posicion actual del puntero del archivo
	 */
	uint32_t getPosicionActual();

    string getPath() const;
    void setPath(string path);


	/**
	 * cierra el archivo de biblioteca
	 */
	virtual ~ArchivoLibro();


private:
	/**
	 * lee cierta cantidad de caracteres (sizeAleer)
	 * lee el archivo (arcLibro) de texto completo y lo devuelve como char*
	 */
	char* leer(fstream & arcLibro, uint32_t & sizeALeer);


	/**
	 *escribe el dato de rv en la posicion offset
	 */
	void escribir(DatoLibro & d, uint32_t offset);

	/**
	 * escribe el contenido al final del archivo prueba.dat abriendo y cerrando el archivo
	 */
	void escribirAlFinal(DatoLibro & d);

	/**
	 * TODO implementar
	 * eliminar el numero de registro nroRegistro de la biblioteca
	 */
	void eliminar(int nroRegistro);

};


#endif /* ARCHIVOVARIABLE_H_ */
