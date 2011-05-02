/*
 * Hash.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *     Estructura que administra un Ã­ndice para acceder a registros libros.
 *
 */

#ifndef HASH_H_
#define HASH_H_

#include <iostream>
#include <list>
#include <stdint.h>
#include <vector>
#include <string>

#include "ElementoHash.h"
#include "../../ModuloEstructuras/Libro.h"
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

//Clase que administra una tabla de dispersión dinámica y almacena los valores dispersados.
class Hash {
private:

	//Cantidad de bloques direccionables por la función de HASH. Dos bloques distintos pueden
	//direccionar a una misma cubeta en el archivo de cubetas.
	unsigned int cantidadDeBloques;

	//Cantidad de bloques efectivamente creados y que contienen alguna información
	unsigned int cantidadDeCubetas;

	//Estructuras de archivo
	fstream 	archivoTabla;
	fstream 	archivoCubetas;

	//Nombres en disco de los archivos (path)
	std::string nombreArchivoTabla;
	std::string nombreArchivoCubetas;

	//Función de HASH usada para la dispersión. Convierte un string en un numero entero positivo
	unsigned int funcionHash(std::string claveADispersar);

	//Devuelve el numero de bloque que corresponde a un valor dispersado por la funcion hash en funcion de la cantida de cubetas
	unsigned int obtenerNumeroDeBloque(unsigned int valorDispersado, unsigned int cantidadDeCubetas);

	//Devuelve el numero de cubeta que le corresponde a una clave string segun funcion hash y cantidad de cubetas
	unsigned int obtenerNumeroDeBloque(std::string claveADispersar);

	DatoTablaHash* levantarDatoTabla(uint32_t offsetDatoTabla);

	DatoCubetaHash* levantarDatoCubeta(uint32_t offsetCubeta);

	void escribirDatoCubeta(DatoCubetaHash* datoCubeta, uint32_t offsetCubeta);

	void escribirDatoTabla(DatoTablaHash* datoTabla, uint32_t offsetDatoTabla);

	std::vector<uint32_t> acumularResultados(DatoCubetaHash* datoCubeta, std::string palabra);

	uint32_t calcularOffsetBloqueEnTabla(unsigned int numeroBloque);

	//Agrega una nueva cubeta en el archivo de cubetas, le escribe la información contenida en datoCubeta y devuelve
	//el offset a esta nueva cubeta.
	uint32_t nuevaCubetaAlFinal(DatoCubetaHash* datoCubeta);

	//Duplica la cantidad de bloques que puede almacenar la tabla y hace que los nuevos bloques
	//apunten a las cubetas que les corresponderían según la función de hash sin expandir la tabla.
	//Luego se modifica el valor "cantidadDeCubetas" que determina el direccionamiento de la función de hash.
	void duplicarTablaHash();

	void manejarDesbordeCubeta(ElementoHash* elemento, DatoCubetaHash* datoCubetaDesbordada, DatoTablaHash* datoTablaDesbordada, uint32_t offsetDatoTabla);

public:
	//Hash();

	Hash(std::string nombreArchivoTabla, std::string nombreArchivoCubetas);

	virtual ~Hash();

	//Ingresa un libro por su clave. El libro de
	void insertarClaveLibro(Libro* libro);

	//Agrega la palabra
	void insertarClave(std::pair<std::string, uint32_t> registroHash);

	//Devuelve el resultado de la búsqueda con la clave contenida en el libro
	std::vector<uint32_t> buscarPalabraEnHash(std::string palabraClave);

	//Hace un 'AND' lógico entre las palabras y devuelve referencias que contengan todas
	//las palabras contenidas en la frase pasada por parámetro.
	std::vector<uint32_t> buscarFraseEnHash(std::string fraseConPalabrasClave);

	unsigned int getCantidadDeBloques();

	std::string getNombreArchivoTabla();

	std::string getNombreArchivoCubetas();
};

#endif /* HASH_H_ */
