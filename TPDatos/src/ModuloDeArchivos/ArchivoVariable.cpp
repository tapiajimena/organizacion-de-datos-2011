/*
 * ArchivoVariable.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de DatoLibro (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "ArchivoVariable.h"


using namespace ManejadorArchivo;

ArchivoVariable::ArchivoVariable()
{
	//esto hace maravillas...
}


ArchivoVariable::ArchivoVariable(string pathArchivo)
{
	this->path = pathArchivo;
	this->abrir();
}

void ArchivoVariable::abrir()
{
		//se abre el archivo de forma binaria, si no existe lo crea si existe lo borra...

		if (Existe(path.c_str(), archivoVariable))
			Abrir(path.c_str(), archivoVariable, true);
		else
			Crear(path.c_str(), archivoVariable, true);
}


void ArchivoVariable::escribir(DatoLibro & d, uint32_t offset)
{
	string 			buffer 	= d.toString();
	uint32_t 		size 	= buffer.size();


	this->archivoVariable.seekp(offset, ios_base::beg);

	archivoVariable.write(reinterpret_cast<char *> (&size), sizeof(size));
	archivoVariable.write(buffer.c_str(), size);
	this->archivoVariable.flush();
}



void ArchivoVariable::escribirAlFinal(DatoLibro &d)
{
	stringstream auxStream;
	string aux = d.toString();
	uint32_t size = d.getSize();


	auxStream.write(reinterpret_cast<char *> (&size), sizeof(size));
	auxStream.write(aux.c_str(), size);
	Escribir(archivoVariable, &auxStream);
}


void ArchivoVariable::irAlInicio()
{
	IrAlInicio(archivoVariable);
}


char* ArchivoVariable::leer(fstream & arcLibro, uint32_t & size)
{
	char* contenidoLibro = (char*)(malloc(0));

	size  = GetSizeArchivo(arcLibro);
    arcLibro.seekp(0, ios_base::beg);

    //se lee
    contenidoLibro = (char*)(realloc(contenidoLibro, size));
    arcLibro.read(contenidoLibro, size);
    return contenidoLibro;
}

void ArchivoVariable::agregarLibro(char* pathLibro)
{
	string rdo;
	DatoLibro dato;
	uint32_t sizeAux;
	fstream arcLibro(pathLibro, ios::in | ios::binary);

	//se lee en contenidoLibro el libro completo
    char* contenidoLibro = leer(arcLibro, sizeAux);

	//se procesa
	rdo = contenidoLibro;
	rdo = rdo.substr(0,sizeAux);
	dato.setDato(rdo);


	arcLibro.close();//se cierra el arcLibro
	escribirAlFinal(dato);//se escribe en la biblioteca

	arcLibro.close();
}


string ArchivoVariable::leerRegistroVariable()
{
	if (!this->finArchivo())
		return LeerDato(archivoVariable);
}


uint32_t ArchivoVariable::getSizeArchivo()
{
	return GetSizeArchivo(archivoVariable);
}

bool ArchivoVariable::finArchivo()
{
	return this->archivoVariable.eof();
}

ArchivoVariable::~ArchivoVariable()
{
	Cerrar(archivoVariable);
}




