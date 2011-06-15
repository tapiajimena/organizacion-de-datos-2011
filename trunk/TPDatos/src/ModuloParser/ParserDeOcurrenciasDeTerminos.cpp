/*
 * ParserDeOcurrenciasDeTerminos.cpp
 *
 *  Created on: 15/06/2011
 *      Author: santi
 */

#include "ParserDeOcurrenciasDeTerminos.h"

ParserDeOcurrenciasDeTerminos::ParserDeOcurrenciasDeTerminos(std::string nombreArchivoStopWords)
{
	this->diccionarioStopWords = new Diccionario();

	this->diccionarioStopWords->cargarDiccionario();
}

ParserDeOcurrenciasDeTerminos::~ParserDeOcurrenciasDeTerminos() {
	delete this->diccionarioStopWords;
}

void ParserDeOcurrenciasDeTerminos::procesarLineaLibro(std::string linea, Libro* libro)
{
	//Definir si la cadena tiene el formato especial de alguno de los campos especiales...

	std::vector<std::string> palabrasDeLinea = ServiceClass::obtenerListaPalabras(linea, SEPARADORES_DE_PALABRAS);

	std::vector<std::string>::iterator it_PalabrasDeLinea;

	for(it_PalabrasDeLinea = palabrasDeLinea.begin(); it_PalabrasDeLinea != palabrasDeLinea.end(); it_PalabrasDeLinea++)
	{
		std::string palabra = *it_PalabrasDeLinea;

		//Trabajamos las palabras en minúsculas.
		//palabra = ServiceClass::toDowncase(palabra);
		palabra = ServiceClass::normalizarString(palabra);

		//EstructuraStopWords::iterator it_StopWords = this->listaStopWords.find(palabra);
		bool esStopWord = this->diccionarioStopWords->existePalabra(palabra);

		if (!esStopWord)
		{
			libro->cargarOcurrenciaDeTermino(palabra);
		}

	}
}

Libro* ParserDeOcurrenciasDeTerminos::parsear(DatoLibro* datoLibro)
{
	//Creamos un libro vacío. Se le carga sólo la editorial.
	   	Libro* libro = new Libro();

		//bool tituloEncontrado = false;
		//Trabajamos con una copia del dato
		std::string cadenaLibro = datoLibro->getDato();

		std::string renglonLibro;
		bool finCadena = false;

		size_t posicionFin = 0;
		size_t posicionInicio = 0;

		if (!cadenaLibro.empty())
		{
			while(posicionFin != string::npos) //&& !finCadena)
			{
				posicionFin = cadenaLibro.find(CARACTER_FIN_DE_LINEA, posicionInicio);
				if (posicionFin != string::npos)
				{
					//subcadena desde posición inicio hasta (posiciónFin-1 -posicionInicio). Equivale a un renglón.
					renglonLibro = cadenaLibro.substr(posicionInicio, (posicionFin - 1)-posicionInicio);
				}
				else
				{
					finCadena = true;
					if(posicionInicio < cadenaLibro.size()-1)
					{
						renglonLibro = cadenaLibro.substr(posicionInicio, cadenaLibro.size()-1);
					}
					else
					{
						renglonLibro = "";
					}
				}

				this->procesarLineaLibro(renglonLibro, libro);

				//posición siguiente al último fin de línea; en caso de fin de cadena, no se usa.
				posicionInicio = posicionFin+1;
			}
		}

	    return libro;

}
