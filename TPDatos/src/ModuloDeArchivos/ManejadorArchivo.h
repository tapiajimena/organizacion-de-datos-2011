/*
 * ManejadorArchivo.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *	Clase ea que nos provee los servicios para acceder a disco
 *
 */

#ifndef ManejadorArchivo_H
#define ManejadorArchivo_H

#include <sstream>
#include <fstream>
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "../ModuloDeTipos/Dato.h"


using namespace std;

namespace ManejadorArchivo
{

	/**
	 * Crea un archivo y lo deja abierto
	 */
	 bool Crear(const char* pathArchivo, fstream &arc, bool binario);

	/*
	 * Solamente abre un archivo existente
	 * binario: si es true lo abre como binario
	 */
	 bool Abrir(const char* pathArchivo, fstream &arc, bool binario);

	/*
	 * devuelve si existe o no el archivo.
	 */
	 bool Existe(const char* pathArchivo, fstream &arc);

	/**
	 * se escriben los datos contenido al final del archivo arc
	 * arc debe estar abierto
	 */
	 bool EscribirDato(fstream &arc, Dato *d);

	 /*
	 * se escriben los datos contenido con un corrimiento offset
	 * arc debe estar abierto
	  */
	 bool EscribirDato(fstream &arc, Dato* d, uint32_t offset);


	 /**
	 * Escribe en el archivo arc un flujo de datos (ss).
	 * arc debe estar abierto
	 */
	 bool Escribir(fstream &arc, stringstream* ss);

	/**
	 * Escribe en el archivo arc un flujo de datos (ss).
	 * arc debe estar abierto
	 */
	 bool Escribir(fstream &arc, stringstream* ss, long offset);


	/*
	 * se leen los datos de arc con un corrimiento offset en ss
	 * arc debe estar abierto
	 * ss se almacena la estructura recuperada
	 * offset lugar a posicionarse al leer
	 */
	 bool RecuperarEstructura(fstream &arc, stringstream &ss,uint32_t offset);


	/**
	 * Lee la estructura (de tamano tamanioEstructura) de un archivo ubicada en una posicion posEst
	 * Devuelve un void*
	 * arc debe estar abierto
	 */
	 bool RecuperarEstructura(fstream &arc, stringstream &ss,uint32_t posEstructura, long tamanioEstructura);

	 string LeerDato(fstream &arc);

	//lee un archivo abierto
	 string LeerCaracteres(fstream &arc, int tamanio);


	 uint32_t GetSizeArchivo(fstream & arc);


	/**
	 *posiciona el puntero del archivo en el inicio.
	 */
	 void IrAlInicio(fstream &arc);

	//cierra el archivo arc
	 bool Cerrar(fstream &arc);

};

#endif // ManejadorArchivo_H

