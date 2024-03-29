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

	/*
	 * si no existe crea el archivo y lo deja abierto, si existe lo abre.
	 * Lo abre siempre como binario
	 * @param pathArchivo ruta+nombre del archivo a crear/abrir
	 * @param arc referncia al archivo
	 * @return true si tuvo que crearlo, false si ya exitia
	 */
	 bool CrearSiNoExiste(const char* pathArchivo, fstream &arc);


	 /*
	  * Crea las carpetas de una direccion.
	  * @param pathCarpeta la direccion de carpetas
	  */
	 bool CrearDirectorios(string pathCarpeta);


	 /*
	  * Copia un archivo desde un origen a un destino
	  *@param origen ruta mas nombre del archivo a copiar
	  *@param destino ruta mas nombre donde se desea copiar
	  */
	 bool CopiarArchivo(string origen, string destino);


	 /*
	  *	Renombra el archivo con nombre nombreInicial a nombreFinal
	  */
	 bool RenombrarArchivo(string nombreInicial, string nombreFinal);

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
	 bool Escribir(fstream &arc, stringstream* ss, uint32_t offset);


	 bool Escribir(fstream* arc, iostream* ios, long offset, long size);

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


	 //el archivo debe existir
	 uint32_t GetSizeArchivo(fstream & arc);

	 uint32_t GetSizeArchivo(string path);

	/**
	 *posiciona el puntero del archivo en el inicio.
	 */
	 void IrAlInicio(fstream &arc);

	/**
	 *posiciona el puntero del archivo en el final.
	 */
	 void IrAlFinal(fstream &arc);

	 /*
	  * Posiciona el puntero de escritura en el offset parametro
	  */
	 void PosicionarPunteroEscrituraEn(fstream &arc, uint32_t offsetPosicion);

	 /*
	  * Posiciona el puntero de lectura en el offset parametro
	  */
	 void PosicionarPunteroLecturaEn(fstream &arc, uint32_t offsetPosicion);

	//cierra el archivo arc
	 bool Cerrar(fstream &arc);

};

#endif // ManejadorArchivo_H

