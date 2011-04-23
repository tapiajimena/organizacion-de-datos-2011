/*
 * Hash.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *     Estructura que administra un índice para acceder a registros libros.
 *
 */

#ifndef HASH_H_
#define HASH_H_

#include <iostream>
#include <list>
#include <stdint.h>
#include <vector>
#include <string>

#include "../../ModuloDeInterfaz/Libro.h"
#include "../../ModuloDeTipos/Dato.h"
#include "../../ModuloDeTipos/DatoCubetaHash.h"
#include "../../ModuloDeTipos/DatoTablaHash.h"
#include "../../ModuloDeArchivos/ManejadorArchivo.h"
//#include "../../ModuloDeTipos/DatoHash.h"
#include "../../../Common/Utilitarios/ServiceClass.h"
#include "../../../Common/Constantes.h"


 //cantidad de bytes que almacena una cubeta = 256 numeros de 4 bytes
//el 1er es unsigned int->cantidad de registros (n)
//n uint32_t offsets
//al final un offset puntero a otra cubeta, si no cuperon los datos que esta debia almacenar, o cero.

//Tipo de dato que se escribe en la tabla de HASH
//typedef struct
//{
//	uint32_t OffSetArchivoCubetas;
//	int cantidadRegistrosCubeta;
//}RegitroTabla;

using namespace ManejadorArchivo;

//Clase que administra una tabla de dispersi�n din�mica y almacena los valores dispersados.
class Hash {
private:

	//Cantidad de bloques o cubetas direccionables por la funci�n de HASH.
	unsigned int cantidadDeCubetas;

	//Estructuras de archivo
	fstream 	archivoTabla;
	fstream 	archivoCubetas;

	//Nombres en disco de los archivos (path)
	std::string nombreArchivoTabla;
	std::string nombreArchivoCubetas;

	//std::list<BloqueHash> listaBloques;

	//Funci�n de HASH usada para la dispersi�n. Convierte un string en un numero entero positivo
	unsigned int funcionHash(std::string claveADispersar);

	unsigned int obtenerNumeroDeCubeta(unsigned int valorDispersado, unsigned int cantidadDeCubetas);

	DatoCubetaHash levantarCubeta(uint32_t offsetCubeta);

public:
	//Hash();

	Hash(std::string nombreArchivoTabla, std::string nombreArchivoCubetas);

	virtual ~Hash();

	//Ingresa un libro por su clave. El libro de
	void insertarClaveLibro(Libro* libro);

	//Devuelve el resultado de la b�squeda con la clave contenida en el libro
	std::vector<uint32_t> buscarPalabraEnHash(std::string palabraClave);

	//Hace un 'AND' l�gico entre las palabras y devuelve referencias que contengan todas
	//las palabras contenidas en la frase pasada por par�metro.
	std::vector<uint32_t> buscarFraseEnHash(std::string fraseConPalabrasClave);

	unsigned int getCantidadDeCubetas();

	std::string getNombreArchivoTabla();

	std::string getNombreArchivoCubetas();
};

#endif /* HASH_H_ */
