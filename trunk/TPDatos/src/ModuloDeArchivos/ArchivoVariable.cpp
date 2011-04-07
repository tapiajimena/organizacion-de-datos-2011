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



void ArchivoVariable::escribirAlFinal(RegistroVariable &rv)
{
	uint32_t size 		= rv.getDato().getSize();

	archivoVariable.write(reinterpret_cast<char *> (&size), sizeof(size));
	archivoVariable.write(rv.getDato().toCharPointer(), size);
	archivoVariable.flush();
}


void ArchivoVariable::irAInicio()
{
	this->archivoVariable.seekp(0, ios_base::beg);
}


char* ArchivoVariable::leer(fstream & arcLibro, uint32_t & size)
{
	char* contenidoLibro = (char*)(malloc(0));

	size  = getSizeArchivo(arcLibro);
    arcLibro.seekp(0, ios_base::beg);

    //se lee
    contenidoLibro = (char*)(realloc(contenidoLibro, size));
    arcLibro.read(contenidoLibro, size);
    return contenidoLibro;
}

void ArchivoVariable::agregarLibro(char* pathLibro)
{
	string rdo;
	Datos dato;
	uint32_t sizeAux;
	fstream arcLibro(pathLibro, ios::in | ios::binary);

	//se lee en contenidoLibro el libro completo
    char* contenidoLibro = leer(arcLibro, sizeAux);

	//se procesa
	rdo = contenidoLibro;
	rdo = rdo.substr(0,sizeAux);
	dato.setDatos(rdo);
	RegistroVariable* rv = new RegistroVariable(dato);

	arcLibro.close();//se cierra el arcLibro
	escribirAlFinal(*rv);//se escribe en la biblioteca
	delete (rv);
	arcLibro.close();
}


char* ArchivoVariable::leerRegistroVariable()
{
	string rdo ="";
	uint32_t size = 0;
	char* contenido	= (char*)malloc(0);

	archivoVariable.read(reinterpret_cast<char *>(&size), sizeof(size));
	contenido = (char*)realloc(contenido, size);
	archivoVariable.read(contenido, size);

	rdo = contenido;
	rdo = rdo.substr(0,size);
	return contenido;
}


uint32_t ArchivoVariable::getSizeArchivo(fstream arc)
{
    arc.seekp(0, ios_base::end);
	return arc.tellg();//pide cual es el tamanio del archivo
}

uint32_t ArchivoVariable::getSizeArchivoVariable()
{
    archivoVariable.seekp(0, ios_base::end);
	return archivoVariable.tellg();//pide cual es el tamanio del archivo
}

bool ArchivoVariable::finArchivo()
{
	return this->archivoVariable.eof();
}

ArchivoVariable::~ArchivoVariable() {
	this->archivoVariable.close();
}




