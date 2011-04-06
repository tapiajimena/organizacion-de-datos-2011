/*
 * ManejadorArchivo.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#ifndef ManejadorArchivo_H
#define ManejadorArchivo_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


using namespace std;

class ManejadorArchivo
{


public:
	/**
	 * Crea un archivo y lo deja abierto
	 */
	static bool Crear(const char* pathArchivo, fstream* arc);

	/*
	 * Solamente abre un archivo existente
	 */
	static bool Abrir(char* pathArchivo, fstream* arc);

	/**
	 * se escriben los bytes contenido al final del archivo arc
	 * arc debe estar abierto
	 */
	static bool EscribirBytes(fstream *arc, char* contenido);

	/*
	 * se escriben los bytes contenido en arc con un corrimiento offset
	 * arc debe estar abierto
	 */
	static bool RecuperarEstructura(fstream *arc, iostream* ios,long offset, long cantidadALeer);

	/**
	 * Escribe en el archivo arc un registro estructura al final
	 * arc debe estar abierto
	 */
	static bool EscribirEstructura(fstream *arc, iostream* ios, long tamanio);

	/**
	 * Escribe en el archivo arc un registro estructura con un corrimiento offset.
	 * arc debe estar abierto
	 */
	static bool EscribirEstructura(fstream *arc, iostream* ios, long offset, long tamanio);


	//lee un archivo abierto
	static string LeerCaracteres(fstream *arc, int tamanio);

	/**
	 * Lee la estructura (de tamano tamanioEstructura) de un archivo ubicada en una posicion posEst
	 * Devuelve un void*
	 * arc debe estar abierto
	 */
	static void* RecuperarEstructura(fstream *arc, long posEscructura, long tamanioEsctructura);


	//cierra el archivo arc
	static bool Cerrar(fstream* arc);


};

#endif // ManejadorArchivo_H

