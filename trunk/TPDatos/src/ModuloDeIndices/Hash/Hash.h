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
#include <algorithm>

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

//Clase que administra una tabla de dispersiï¿½n dinï¿½mica y almacena los valores dispersados.
class Hash {
private:

	//Cantidad de bloques direccionables por la funciï¿½n de HASH. Dos bloques distintos pueden
	//direccionar a una misma cubeta en el archivo de cubetas.
	unsigned int cantidadDeBloques;

	//Cantidad de bloques efectivamente creados y que contienen alguna informaciï¿½n
	unsigned int cantidadDeCubetas;

	//Estructuras de archivo
	fstream 	archivoTabla;
	fstream 	archivoCubetas;

	//Nombres en disco de los archivos (path)
	std::string nombreArchivoTabla;
	std::string nombreArchivoCubetas;

	//Funciï¿½n de HASH usada para la dispersiï¿½n. Convierte un string en un numero entero positivo
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

	/*
	 * Devuelve todas las entradas de la tabla que apuntan a la misma cubeta de datos que el bloque indicado por parámetro.
	 * Las devuelve en un std::pair en que el 1er elemento es el puntero al datoTabla y el segundo el número de dicho dato en la tabla.
	 * Se deben destruir todos los DatoTablaHash* del vector desupés de usar.
	 */
	std::vector< std::pair<DatoTablaHash*, unsigned int> > obtenerBloquesConMismaCubeta(unsigned int nroDeBloque, unsigned int offsetCubeta);

	//Agrega una nueva cubeta en el archivo de cubetas, le escribe la informaciï¿½n contenida en datoCubeta y devuelve
	//el offset a esta nueva cubeta.
	uint32_t nuevaCubetaAlFinal(DatoCubetaHash* datoCubeta);

	//Duplica la cantidad de bloques que puede almacenar la tabla y hace que los nuevos bloques
	//apunten a las cubetas que les corresponderï¿½an segï¿½n la funciï¿½n de hash sin expandir la tabla (comparten cubetas).
	//Luego se modifica el valor "cantidadDeBloques" que determina el direccionamiento de la funciï¿½n de hash.
	void duplicarTablaHash();

	void manejarDesbordeCubeta(ElementoHash* elemento, DatoCubetaHash* datoCubetaDesbordada, DatoTablaHash* datoTablaDesbordada, unsigned int numeroDeBloque);

public:
	//Hash();

	Hash(std::string nombreArchivoTabla, std::string nombreArchivoCubetas);

	virtual ~Hash();

	//Ingresa un libro por su clave. El libro de
	void insertarClaveLibro(Libro* libro);

	//Agrega la palabra
	void insertarClave(std::pair<std::string, uint32_t> registroHash);

	//Devuelve el resultado de la bï¿½squeda con la clave contenida en el libro
	std::vector<uint32_t> buscarPalabraEnHash(std::string palabraClave);

	//Hace un 'AND' lï¿½gico entre las palabras y devuelve referencias que contengan todas
	//las palabras contenidas en la frase pasada por parï¿½metro.
	std::vector<uint32_t> buscarFraseEnHash(std::string fraseConPalabrasClave);

	unsigned int getCantidadDeBloques();

	std::string getNombreArchivoTabla();

	std::string getNombreArchivoCubetas();
};

#endif /* HASH_H_ */
