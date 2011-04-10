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
	stringstream auxStream;
	uint32_t size 		= rv.getDato().getSize();

	auxStream.write(reinterpret_cast<char *> (&size), sizeof(size));
	auxStream.write(rv.getDato().toCharPointer(), size);
	Escribir(archivoVariable, &auxStream);
}


void ArchivoVariable::irAInicio()
{
	IrAlInicio(archivoVariable);
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


string ArchivoVariable::leerRegistroVariable()
{
	string rdo ="";
	uint32_t size = 0;
	char* contenido	= (char*)malloc(0);

	if (!this->finArchivo())
		return LeerDato(archivoVariable);
}


uint32_t ArchivoVariable::getSizeArchivo(fstream & arc)
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

ArchivoVariable::~ArchivoVariable()
{
	Cerrar(archivoVariable);
}




