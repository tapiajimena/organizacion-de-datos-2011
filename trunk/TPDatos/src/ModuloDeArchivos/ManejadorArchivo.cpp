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



bool ManejadorArchivo::Crear(const char *pathArchivo, fstream &arc, bool binario)
{
	if (binario)
		arc.open(pathArchivo, ios::in | ios::out | ios::trunc| ios::binary);//es "la linea"
	else
		arc.open(pathArchivo, ios::in | ios::out | ios::trunc);//es "la linea"
	if (arc.is_open())
		return true;
	return false;
}


bool ManejadorArchivo::Abrir(const char *pathArchivo, fstream &arc, bool binario)
{
	if (binario)
		arc.open(pathArchivo, fstream::in | fstream::out | fstream::binary);
	else
		arc.open(pathArchivo, fstream::in | fstream::out);

	if (arc.is_open())
		return true;
	return false;
}

bool ManejadorArchivo::Existe(const char* pathArchivo, fstream & arc)
{
	bool aux = Abrir(pathArchivo, arc, true);
	Cerrar(arc);

	return aux;
}

bool ManejadorArchivo::EscribirDato(fstream &arc, Dato* d)
{
	stringstream aux;
	aux << d->getDato();
	Escribir(arc, &aux);
}

bool ManejadorArchivo::EscribirDato(fstream &arc, Dato* d, uint32_t offset)
{
	arc.seekg(offset, ios_base::beg);
	stringstream aux;
	aux << d->getDato();
	Escribir(arc, &aux);
}

bool ManejadorArchivo::Escribir(fstream &arc, stringstream * ss)
{
	if(arc.good() && ss->good())
	{
		arc<< ss->str();
		arc.flush();
	}
	else
		return false;
}


bool ManejadorArchivo::Escribir(fstream &arc, stringstream * ss, long offset)
{
	arc.seekg(offset, ios_base::beg);
	Escribir(arc, ss);
}

string ManejadorArchivo::LeerDato(fstream &arc)
{
	string 		rdo;
	uint32_t 	size;
	char* 		contenido	= (char*)malloc(0);

	arc.read(reinterpret_cast<char *>(&size), sizeof(size));
	contenido = (char*)realloc(contenido, size);
	arc.read(contenido, size);
	rdo = contenido;
	rdo = rdo.substr(0,size);

	return rdo;
}

string ManejadorArchivo::LeerCaracteres(fstream &arc, int tamanio)
{
	if (arc.eof())
		return "";
	else
	{
		char* buffer = new char[tamanio+1];
		stringstream sin;
		arc.get(buffer,tamanio+1);
		sin << buffer;
		delete[] buffer;

		return sin.str();
	}
}


uint32_t ManejadorArchivo::GetSizeArchivo(fstream & arc)
{
    arc.seekp(0, ios_base::end);
	return arc.tellg();//pide cual es el tamanio del archivo
}


bool ManejadorArchivo::RecuperarEstructura(fstream &arc, stringstream &ss,uint32_t offset)
{
	string 		rdo;
	uint32_t 	size;
	char* 		contenido	= (char*)malloc(0);

	arc.seekg(offset, ios_base::beg);//se posiciona el ptro en offset
	arc.read(reinterpret_cast<char *>(&size), sizeof(size));//se lee el size del dato
	contenido = (char*)realloc(contenido, size);
	arc.read(contenido, size);
	rdo = contenido;
	rdo = rdo.substr(0,size);

	ss.write(rdo.c_str(), rdo.length());

	if (arc.good() && ss.good())
		return true;
	else
		return false;

}

bool ManejadorArchivo::RecuperarEstructura(fstream &arc, stringstream &ss,uint32_t posEstructura, long tamanioEstructura)
{
	string 		rdo;
	char* 		contenido	= (char*)malloc(0);

	arc.seekg(posEstructura, ios_base::beg);//se posiciona el ptro en offset
	contenido = (char*)realloc(contenido, tamanioEstructura);
	arc.read(contenido, tamanioEstructura);
	rdo = contenido;
	rdo = rdo.substr(0,tamanioEstructura);

	ss.write(rdo.c_str(), rdo.length());

	if (arc.good() && ss.good())
		return true;
	else
		return false;
}

void ManejadorArchivo::IrAlInicio(fstream &arc)
{
	arc.seekp(0, ios_base::beg);
}


bool ManejadorArchivo::Cerrar(fstream &arc)
{
	arc.close();
	return true;
}





