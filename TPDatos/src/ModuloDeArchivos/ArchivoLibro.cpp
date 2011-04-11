/*
 * ArchivoLibro.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "ArchivoLibro.h"


using namespace ManejadorArchivo;

ArchivoLibro::ArchivoLibro()
{
	//esto hace maravillas...
}


ArchivoLibro::ArchivoLibro(string pathArchivo)
{
	this->path = pathArchivo;
	this->abrir();
}

void ArchivoLibro::abrir()
{
		//se abre el archivo de forma binaria, si no existe lo crea si existe lo borra...

		if (Existe(path.c_str(), archivoVariable))
			Abrir(path.c_str(), archivoVariable, true);
		else
			Crear(path.c_str(), archivoVariable, true);
}


void ArchivoLibro::escribir(DatoLibro & d, uint32_t offset)
{
	string 			buffer 	= d.toString();
	uint32_t 		size 	= buffer.size();


	this->archivoVariable.seekp(offset, ios_base::beg);

	archivoVariable.write(reinterpret_cast<char *> (&size), sizeof(size));
	archivoVariable.write(buffer.c_str(), size);
	this->archivoVariable.flush();
}



void ArchivoLibro::escribirAlFinal(DatoLibro &d)
{
	stringstream auxStream;
	string aux = d.toString();
	uint32_t size = d.getSize();


	auxStream.write(reinterpret_cast<char *> (&size), sizeof(size));
	auxStream.write(aux.c_str(), size);
	Escribir(archivoVariable, &auxStream);
}


void ArchivoLibro::irAlInicio()
{
	IrAlInicio(archivoVariable);
}


char* ArchivoLibro::leer(fstream & arcLibro, uint32_t & size)
{
	char* contenidoLibro = (char*)(malloc(0));

	size  = GetSizeArchivo(arcLibro);
    arcLibro.seekp(0, ios_base::beg);

    //se lee
    contenidoLibro = (char*)(realloc(contenidoLibro, size));
    arcLibro.read(contenidoLibro, size);
    return contenidoLibro;
}

void ArchivoLibro::agregarLibro(char* pathLibro)
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


string ArchivoLibro::leerRegistroVariable()
{
	if (!this->finArchivo())
		return LeerDato(archivoVariable);
}


uint32_t ArchivoLibro::getSizeArchivo()
{
	return GetSizeArchivo(archivoVariable);
}

bool ArchivoLibro::finArchivo()
{
	return this->archivoVariable.eof();
}

ArchivoLibro::~ArchivoLibro()
{
	Cerrar(archivoVariable);
}




