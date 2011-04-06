/*
 * ArchivoVariable.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "ArchivoVariable.h"

ArchivoVariable::ArchivoVariable() {

}


ArchivoVariable::ArchivoVariable(string pathArchivo)
{
	this->path = pathArchivo;
	abrir();
}

void ArchivoVariable::abrir()
{
	//se abre el archivo de forma binaria, si no existe lo crea si existe lo borra...
	this->archivoVariable.open(this->path.c_str(), ios::in | ios::out | ios::trunc| ios::binary);//es "la linea"
}


void ArchivoVariable::escribir(RegistroVariable & rv, uint32_t offset)
{
	Datos 	aux 		= rv.getDato();
	string 	buffer 		= aux.toString();
	uint32_t size 		= buffer.size();


	this->archivoVariable.seekp(offset, ios_base::beg);

	archivoVariable.write(reinterpret_cast<char *> (&size), sizeof(size));
	archivoVariable.write(buffer.c_str(), size);
	this->archivoVariable.flush();
}


/**
 * escribe el contenido al final del archivo prueba.dat abriendo y cerrando el archivo
 */
void ArchivoVariable::escribirAlFinal(RegistroVariable &rv)
{
	uint32_t size 		= rv.getDato().getSize();

	//arcVariable.open("prueba.dat", ios::in | ios::out |ios::binary|ios::ate);
	//archivoVariable.seekp(0, ios_base::end);

	archivoVariable.write(reinterpret_cast<char *> (&size), sizeof(size));
	archivoVariable.write(rv.getDato().toCharPointer(), size);
	archivoVariable.flush();
	//arcVariable.close();
}


void ArchivoVariable::irAInicio()
{
	this->archivoVariable.seekp(0, ios_base::beg);
}

char* ArchivoVariable::leer()
{
	string rdo ="";
	uint32_t size = 0;
	char* contenido	= (char*)malloc(0);

	//arcVariable.seekp(offset);
	archivoVariable.read(reinterpret_cast<char *>(&size), sizeof(size));

	contenido = (char*)realloc(contenido, size);
	archivoVariable.read(contenido, size);

	rdo = contenido;
	rdo = rdo.substr(0,size);
	return contenido;
}

uint32_t ArchivoVariable::getSizeArchivo()
{
	return this->archivoVariable.tellg();//pide cual es el tamanio del archivo
}

bool ArchivoVariable::finArchivo()
{
	return this->archivoVariable.eof();
}

ArchivoVariable::~ArchivoVariable() {
	this->archivoVariable.close();
}




