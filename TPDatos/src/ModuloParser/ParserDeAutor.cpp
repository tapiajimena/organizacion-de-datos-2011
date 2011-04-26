/*
* ParserDeAutor.h
*
*	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
*	Catedra	: SERVETTO-FERRER-FERNANDEZ
*	Materia	: Organizacion de Datos (75.06) - FIUBA
*
*
*
*
*/

#include "ParserDeAutor.h"

ParserDeAutor::ParserDeAutor() {
}

ParserDeAutor::~ParserDeAutor() {
}

void ParserDeAutor::ProcesarRenglonLibro(std::string renglonLibro, Libro* libro, bool &autorEncontrado)
{
	//Separamos en palabras la línea y verificamos si se define en esta línea el título.
	//No nos interesa la puntuación del contexto -> SEPARADORES_DE_PALABRAS (sin puntuación).
	std::vector<std::string> listaPalabras = ServiceClass::obtenerListaPalabras(renglonLibro, SEPARADORES_DE_PALABRAS);

	if (listaPalabras.size() > 0)
	{
		if(listaPalabras.at(0) == IDENTIFICADOR_AUTOR) //Definido en Constantes.h
		{
			std::stringstream autorLibro;
			for (unsigned int numeroPalabra = 1; numeroPalabra < listaPalabras.size(); numeroPalabra++)
			{
				autorLibro<<listaPalabras.at(numeroPalabra);
				//Espacio entre palabras, salvo al final.
				if(numeroPalabra < listaPalabras.size()-1)
					autorLibro<<" ";
			}
			libro->setAutor( autorLibro.str());
			autorEncontrado = true;
		}
	}
}

Libro* ParserDeAutor::parsear(DatoLibro* datoLibro)
{
	//Creamos un libro vacío. Se le carga sólo el título.
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














