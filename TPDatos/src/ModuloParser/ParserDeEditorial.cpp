/*
 * ParserDeEditorial.cpp
 *
 *  Created on: 12/04/2011
 *      Author: santi
 */

#include "ParserDeEditorial.h"

ParserDeEditorial::ParserDeEditorial() {
}

ParserDeEditorial::~ParserDeEditorial() {
}

void ParserDeEditorial::ProcesarRenglonLibro(std::string renglonLibro, Libro* libro, bool &editorialEncontrada)
{
	//Separamos en palabras la línea y verificamos si se define en esta línea el título.
	std::vector<std::string> listaPalabras = ServiceClass::obtenerListaPalabras(renglonLibro, SEPARADORES_DE_PALABRAS_CON_PUNTUACION);

	if(listaPalabras.size() > 0)
	{
		if(listaPalabras.at(0) == IDENTIFICADOR_EDITORIAL) //Definido en Constantes.h
		{
			std::stringstream editorialLibro;
			for (unsigned int numeroPalabra = 1; numeroPalabra < listaPalabras.size(); numeroPalabra++)
			{
				editorialLibro<<listaPalabras.at(numeroPalabra);
				//Espacio entre palabras, salvo al final.
				if(numeroPalabra < listaPalabras.size()-1)
					editorialLibro<<" ";
			}
			libro->setEditorial( editorialLibro.str());
			editorialEncontrada = true;
		}
	}
}

Libro* ParserDeEditorial::parsear(DatoLibro* datoLibro)
{
	//Creamos un libro vacío. Se le carga sólo la editorial.
	Libro* libro = new Libro();

	bool tituloEncontrado = false;

	//Trabajamos con una copia del dato
	std::string cadenaLibro = datoLibro->getDato();

	std::string renglonLibro;

	size_t posicionFin = 0;
	size_t posicionInicio = 0;

	if (!cadenaLibro.empty())
	{
		while(posicionFin != string::npos && !tituloEncontrado)
		{
			posicionFin = cadenaLibro.find(CARACTER_FIN_DE_LINEA, posicionInicio);
			if (posicionFin != string::npos)
			{
				//subcadena desde posición inicio hasta (posiciónFin-1 -posicionInicio). Equivale a un renglón.
				renglonLibro = cadenaLibro.substr(posicionInicio, (posicionFin - 1)-posicionInicio);
			}
			else
			{
				renglonLibro = "";
			}

			this->ProcesarRenglonLibro(renglonLibro, libro, tituloEncontrado);

			//posición siguiente al último fin de línea; en caso de fin de cadena, no se usa.
			posicionInicio = posicionFin+1;
		}
	}

	return libro;
}
