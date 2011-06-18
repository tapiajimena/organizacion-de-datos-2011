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

	//El Offset en archivo del término es su ID...
	uint32_t idTermino = offsetDeTermino;

	ss.write(palabra.c_str(), tamanioDato);

	//Agregamos el caracter de fin de termino
	ss << FIN_DE_TERMINO;

	ManejadorArchivo::Escribir(&this->archivoTerminos, &ss, offsetDeTermino, tamanioDato + 1);
	this->archivoTerminos.flush();
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

	if( PRR < tamanioDeArchivo)
	{
		ManejadorArchivo::PosicionarPunteroLecturaEn(this->archivoTerminos, PRR);

		while (!finTermino && PRR < tamanioDeArchivo)
		{
			//letraActual = ManejadorArchivo::LeerCaracteres(this->archivoTerminos, 1).at(0);

			this->archivoTerminos.read(&letraActual, 1);

			if (letraActual == FIN_DE_TERMINO)
			{
				finTermino = true;
			}
			else
			{
				ss.write(&letraActual, 1);
			}

			PRR = this->archivoTerminos.tellg();
		}
	}

	termino = ss.str();
	return termino;
}

std::vector<uint32_t> ArchivoTerminos::obtenerListaDeIdTerminos()
{
	//Para dejar el archivo en la misma posición, tras terminar el método.
	uint32_t offsetPrevio = this->archivoTerminos.tellg();

	uint32_t PRR = 0; //puntero local

	std::vector<uint32_t> listaIdTerminos;

	uint32_t tamanioArchivoTerminos = ManejadorArchivo::GetSizeArchivo(this->archivoTerminos);

	ManejadorArchivo::PosicionarPunteroLecturaEn(this->archivoTerminos, 0);

	bool caracterFinTerminoEncontrado = false;
	char letraChar;

	//El cero siempre es el Id del primer Termino.
	if( tamanioArchivoTerminos > 0)
	{
		listaIdTerminos.push_back(0);

		while( PRR < tamanioArchivoTerminos)
		{
			this->archivoTerminos.read(&letraChar, 1);

			if(caracterFinTerminoEncontrado && PRR < tamanioArchivoTerminos && letraChar != FIN_DE_TERMINO)
			{
				listaIdTerminos.push_back(PRR);
				caracterFinTerminoEncontrado = false;
			}
			else
			{
				if(letraChar == FIN_DE_TERMINO)
				{
					caracterFinTerminoEncontrado = true;
				}
			}

			PRR = this->archivoTerminos.tellg();
		}
	}

	this->archivoTerminos.seekg(offsetPrevio, ios::beg);
	return listaIdTerminos;
}

std::vector<std::string> ArchivoTerminos::obtenerListaDeTerminos()
{
	//Para dejar el archivo en la misma posición, tras terminar el método.
	uint32_t offsetPrevio = this->archivoTerminos.tellg();

	uint32_t PRR = 0; //puntero local

	std::vector<std::string> listaTerminos;

	uint32_t tamanioArchivoTerminos = ManejadorArchivo::GetSizeArchivo(this->archivoTerminos);

	ManejadorArchivo::PosicionarPunteroLecturaEn(this->archivoTerminos, 0);

	//ManejadorArchivo::PosicionarPunteroLecturaEn(this->archivoTerminos, PRR);

	std::string palabra = "";
	std::string letra = "";
	char letraChar;

	while( PRR < tamanioArchivoTerminos)
	{
		//este metodo de la clase leerCaracteres no anda bien, o se pisa, que se yo que corno le pasa
		//letraChar = ManejadorArchivo::LeerCaracteres(this->archivoTerminos, 1).at(0); //aca lee basura... ??

		this->archivoTerminos.read(&letraChar, 1);

		if(letraChar != FIN_DE_TERMINO)
		{
			letra = &letraChar;
			palabra.append(letra);
		}
		else
		{
			if(palabra.size() > 0)
			{
				listaTerminos.push_back(palabra);
			}
			palabra = "";
		}

		PRR = this->archivoTerminos.tellg();
	}

	this->archivoTerminos.seekg(offsetPrevio, ios::beg);
	return listaTerminos;
}

std::vector<std::pair<std::string, uint32_t> > ArchivoTerminos::obtenerTerminos()
{
	//Para dejar el archivo en la misma posición, tras terminar el método.
	uint32_t offsetPrevio = this->archivoTerminos.tellg();

	uint32_t PRR = 0; //puntero local

	std::vector<std::pair<std::string, uint32_t> > listaTerminos;

	uint32_t tamanioArchivoTerminos = ManejadorArchivo::GetSizeArchivo(this->archivoTerminos);

	ManejadorArchivo::PosicionarPunteroLecturaEn(this->archivoTerminos, 0);

	std::string palabra = "";
	std::string letra = "";
	char letraChar;
	uint32_t offsetTermino = 0;

	std::pair<std::string, uint32_t> elementoTermino;

	while( PRR < tamanioArchivoTerminos)
	{
		//este metodo de la clase leerCaracteres no anda bien, o se pisa, que se yo que corno le pasa
		//letraChar = ManejadorArchivo::LeerCaracteres(this->archivoTerminos, 1).at(0); //aca lee basura... ??

		this->archivoTerminos.read(&letraChar, 1);

		if(letraChar != FIN_DE_TERMINO)
		{
			letra = &letraChar;
			palabra.append(letra);
		}
		else
		{
			if(palabra.size() > 0)
			{
				elementoTermino.first = palabra;
				elementoTermino.second = offsetTermino;
				listaTerminos.push_back(elementoTermino);
			}
			palabra = "";
			offsetTermino = PRR + 1;
		}

		PRR = this->archivoTerminos.tellg();
	}

	this->archivoTerminos.seekg(offsetPrevio, ios::beg);
	return listaTerminos;
}
