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
	Datos aux = rv.serializarse();
	string buffer = aux.toString();
	this->archivoVariable.seekp(offset, ios_base::beg);


	this->archivoVariable.write((const char *)buffer.c_str(), 320);
	this->archivoVariable.flush();


}

RegistroVariable* ArchivoVariable::leer()
{
	return NULL;
}



ArchivoVariable::~ArchivoVariable() {
	// TODO Auto-generated destructor stub
}
