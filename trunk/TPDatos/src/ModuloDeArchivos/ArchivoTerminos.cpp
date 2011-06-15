/*
 * ArchivoTerminos.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ArchivoTerminos.h"

ArchivoTerminos::ArchivoTerminos(std::string nombreArchivo)
{
	ManejadorArchivo::CrearSiNoExiste( nombreArchivo.c_str(), archivoTerminos);
}

ArchivoTerminos::~ArchivoTerminos()
{
	ManejadorArchivo::Cerrar(archivoTerminos);
}

uint32_t ArchivoTerminos::ingresarTermino(std::string palabra)
{
	//iostream* ios;
	stringstream ss;

	unsigned int tamanioDato = palabra.length();
	uint32_t offsetDeTermino = ManejadorArchivo::GetSizeArchivo( this->archivoTerminos);

	//El Offset en archivo del t�rmino es su ID...
	uint32_t idTermino = offsetDeTermino;

	ss.write(palabra.c_str(), tamanioDato);

	//Agregamos el caracter de fin de termino
	ss << FIN_DE_TERMINO;

	ManejadorArchivo::Escribir(&this->archivoTerminos, &ss, offsetDeTermino, tamanioDato + 1);
	//cout<<"EL ARC DE TERMINOS ESCRIBE: "<< ss.str()<<endl;

	return idTermino;
}

std::string ArchivoTerminos::obtenerTermino(uint32_t idTermino)
{
	std::string termino;
	uint32_t tamanioDeArchivo = ManejadorArchivo::GetSizeArchivo(this->archivoTerminos);
	uint32_t PRR = idTermino; //Posicion de Registro Relativo de archivo.
	bool finTermino = false;
	char letraActual;

	stringstream ss;

	if( PRR < tamanioDeArchivo && PRR >= 0)
	{
		ManejadorArchivo::PosicionarPunteroLecturaEn(this->archivoTerminos, PRR);

		while (!finTermino)
		{
			letraActual = ManejadorArchivo::LeerCaracteres(this->archivoTerminos, 1).at(0);

			if (letraActual == FIN_DE_TERMINO)
			{
				finTermino = true;
			}
			else
			{
				ss.write(&letraActual, 1);
			}
		}
	}

	termino = ss.str();
	return termino;
}