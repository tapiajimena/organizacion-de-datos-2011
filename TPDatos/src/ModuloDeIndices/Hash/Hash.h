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

//Clase que administra una tabla de dispersi�n din�mica y almacena los valores dispersados.
class Hash {
//private:
public: //solo para debuggear, esto es private.

	//Cantidad de bloques direccionables por la funci�n de HASH. Dos bloques distintos pueden
	//direccionar a una misma cubeta en el archivo de cubetas.
	unsigned int cantidadDeBloques;

	//Cantidad de bloques efectivamente creados y que contienen alguna informaci�n (incluye cubetas de extensi�n).
	unsigned int cantidadDeCubetas;

	//Estructuras de archivo
	fstream 	archivoTabla;
	fstream 	archivoCubetas;

	//Nombres en disco de los archivos (path)
	std::string nombreArchivoTabla;
	std::string nombreArchivoCubetas;

	//Funci�n de HASH usada para la dispersi�n. Convierte un string en un numero entero positivo
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
	 * Devuelve todas las entradas de la tabla que apuntan a la misma cubeta de datos que el bloque indicado por par�metro.
	 * Las devuelve en un std::pair en que el 1er elemento es el puntero al datoTabla y el segundo el n�mero de dicho dato en la tabla.
	 * Se deben destruir todos los DatoTablaHash* del vector desup�s de usar.
	 */
	std::vector< unsigned int > obtenerBloquesConMismaCubeta(unsigned int nroDeBloque, unsigned int offsetCubeta);

	//Agrega una nueva cubeta en el archivo de cubetas, le escribe la informaci�n contenida en datoCubeta y devuelve
	//el offset a esta nueva cubeta.
	uint32_t nuevaCubetaAlFinal(DatoCubetaHash* datoCubeta);

	//Duplica la cantidad de bloques que puede almacenar la tabla y hace que los nuevos bloques
	//apunten a las cubetas que les corresponder�an seg�n la funci�n de hash sin expandir la tabla (comparten cubetas).
	//Luego se modifica el valor "cantidadDeBloques" que determina el direccionamiento de la funci�n de hash.
	void duplicarTablaHash();

	//Redispersa en la tabla todos los elementos de una serie de cubetas enganchada (o sea, que pertenecen a un mismo bloque o entrada de la tabla.
	//Cuando una tabla no se reorganiza toda, sino s�lo el bloque que rebals�, por lo tanto los otros bloques comparten cubetas. Con esto se
	//hace que cada bloque abra su cubeta y reciba sus datos.
	void redispersarSucesionCubetas(std::vector<DatoCubetaHash*> cubetasSucesivas, unsigned int numeroDeBloque, DatoTablaHash* datoTabla);

	void manejarDesbordeCubeta(ElementoHash* elemento, DatoCubetaHash* datoCubetaDesbordada, DatoTablaHash* datoTablaDesbordada, unsigned int numeroDeBloque);

	//Inserta un elemento de hash.
	void insertarElemento(ElementoHash elemento);

	void escribirArchivoIndice(fstream &archivoSalidaIndice);

	void escribirArchivosTablaDatosYEspaciosLibres(fstream &archivoSalidaTabla, fstream &archivoSalidaDatos, fstream &archivoSalidaEspaciosLibres);

	void eliminarElemento(ElementoHash elemento);
	void eliminarElementoCubetaEnDisco(uint32_t offsetCubetaActual, DatoCubetaHash* datoCubetaActual);

public:
	//Hash();

	Hash(std::string nombreArchivoTabla, std::string nombreArchivoCubetas);

	virtual ~Hash();

	//Agrega la palabra
	void insertarClave(std::pair<std::string, uint32_t> registroHash);

	//Devuelve el resultado de la b�squeda con la clave contenida en el libro
	std::vector<uint32_t> buscarPalabraEnHash(std::string palabraClave);

	//Hace un 'AND' l�gico entre las palabras y devuelve referencias que contengan todas
	//las palabras contenidas en la frase pasada por par�metro.
	std::vector<uint32_t> buscarFraseEnHash(std::string fraseConPalabrasClave);

	unsigned int getCantidadDeBloques();

	std::string getNombreArchivoTabla();

	std::string getNombreArchivoCubetas();

	//Pasar s�lo las 1eras letras que identifican a los archivos generados. Se termina de formar sus nombres
	//en el algoritmo.
	void escribirEstructuraEnArchivos(std::string baseNombreArchivo);
};

#endif /* HASH_H_ */
