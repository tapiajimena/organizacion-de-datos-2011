/*
 * ManejadorArchivo.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#include "ManejadorArchivo.h"



/**
 * Vacia el buffer en el archivo, es decir escribe en arc sin necesidad de cerrarlo.
 */
bool escribirBuffer(fstream *arc, iostream* ios, long tamanio)
{
	char* buffer = new char[tamanio];

	ios->read(buffer, tamanio);
	arc->write(buffer, tamanio);

	if (arc->good() && ios->good())
	{
		delete [] buffer;
		return true;
	}
	else
	{
		delete [] buffer;
		return false;
	}
}


bool ManejadorArchivo::Crear(const char *pathArchivo, fstream *arc)
{
	arc->open(pathArchivo, ios::in | ios::out | ios::binary | ios::trunc );
	if (arc->is_open())
		return true;
	return false;
}


bool ManejadorArchivo::Abrir(char *pathArchivo, fstream *arc)
{
	arc->open(pathArchivo, fstream::in | fstream::out | fstream::binary);

	if (arc->is_open())
		return true;
	return false;
}


bool ManejadorArchivo::EscribirBytes(fstream *arc, char* contenido)
{
	//return escribirBuffer(arc,contenido, strlen(contenido));
}

/*
bool ManejadorArchivo::EscribirBytes(fstream *arc, iostream* ios, long offset, long tamanio)
{

}
*/

bool ManejadorArchivo::EscribirEstructura(fstream *arc, iostream* ios, long tamanio)
{
	escribirBuffer(arc, ios, tamanio);
}


bool ManejadorArchivo::EscribirEstructura(fstream *arc, iostream* ios, long offset, long tamanio)
{
	arc->seekp(offset, ios_base::beg);
	escribirBuffer(arc, ios, tamanio);
}


string ManejadorArchivo::LeerCaracteres(fstream *arc, int tamanio)
{
	if (arc->eof())
		return "";
	else
	{
		char* buffer = new char[tamanio+1];
		stringstream sin;
		arc->get(buffer,tamanio+1);
		sin << buffer;
		delete[] buffer;

		return sin.str();
	}
}


bool ManejadorArchivo::RecuperarEstructura(fstream *arc, iostream* ios,long offset, long cantidadALeer)
{
	arc->seekg(offset, ios_base::beg);
	char * buffer = new char[cantidadALeer];
	memset(buffer, 0, cantidadALeer);
	arc->read(buffer, cantidadALeer);

	ios->write(buffer, cantidadALeer);
	delete[] buffer;
	if (arc->good() && ios->good()) {
		return true;
	} else {
		return false;
	}
}


bool ManejadorArchivo::Cerrar(fstream *arc)
{
	arc->close();
	return true;
}





