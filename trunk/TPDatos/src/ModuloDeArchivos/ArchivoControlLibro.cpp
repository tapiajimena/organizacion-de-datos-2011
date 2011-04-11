/*
 * ArchivoControlLibro.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "ArchivoControlLibro.h"


using namespace ManejadorArchivo;

ArchivoControlLibro::ArchivoControlLibro() {
	// TODO Auto-generated constructor stub

}


ArchivoControlLibro::ArchivoControlLibro(string path) {
	Crear(path.c_str(),archivoControlLibro, false);

}

bool ArchivoControlLibro::chequearIndexado(uint32_t idLIbro)
{
	return false;
}

uint32_t ArchivoControlLibro::dondeEscribo(uint32_t sizeAlmacenar)
{
	return 0;
}

void ArchivoControlLibro::registrarIndexado(uint32_t idLibro, char tipoClave)
{
}

void ArchivoControlLibro::registrarLibro(uint32_t idLibro)
{
	string str;
	stringstream ssAux;
	char aux[11]; // 11 bytes: 10 for the digits, 1 for the null character

	snprintf(aux, sizeof aux, "%lu", (unsigned long)idLibro); /* Method 1 */

	if (idLibro>0)//si no es el primer archivo se le inserta un enter adelante
		str = "\n";

	//se arma el string:
	//offset|sizeLibre|TagAutor|TagEditorial|TagTitulo|TagPalabras (se inicializan en 0 los tags)
	str= str + aux +"|0|0|0|0|0";

	ssAux.write(str.c_str(), str.length());
	Escribir(archivoControlLibro, &ssAux);
}

ArchivoControlLibro::~ArchivoControlLibro() {
	// TODO Auto-generated destructor stub
}
