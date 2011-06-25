	/*
* Libro.cpp
*
*	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
*	Catedra	: SERVETTO-FERRER-FERNANDEZ
*	Materia	: Organizacion de Datos (75.06) - FIUBA
*
*
*
*
*/
#include "Libro.h"

Libro::Libro()
{
	this->_palabrasClave = new EstructuraPalabrasClave;
};

void Libro::setPalabrasClave(EstructuraPalabrasClave *_palabrasClave)
{
    this->_palabrasClave = _palabrasClave;
}

Libro::~Libro()
{
	delete this->_palabrasClave;
};

std::string Libro::getTitulo()
{
	return this->_titulo;
};

void Libro::setTitulo(std::string titulo)
{
	this->_titulo = titulo;
};

std::string Libro::getAutor()
{
	return this->_autor;
};

void Libro::setAutor(std::string autor)
{
	this->_autor = autor;
};

void Libro::setEditorial(std::string editorial)
{
	this->_editorial = editorial;
}

std::string Libro::getEditorial()
{
	return this->_editorial;
}

uint32_t Libro::getOffset() const
{
    return offset;
}

void Libro::setOffset(uint32_t offset)
{
    this->offset = offset;
}

/*
std::string Libro::getISBN()
{
	return this->_ISBN;
};

void Libro::setISBN(std::string ISBN)
{
	this->_ISBN = ISBN;
};
*/

EstructuraPalabrasClave* Libro::getPalabrasClave()
{
	return this->_palabrasClave;
};

void Libro::agregarPalabraClave(std::string palabra)
{
	EstructuraPalabrasClave::iterator it_mapaPalabras = this->_palabrasClave->find(palabra);
	if( it_mapaPalabras == this->_palabrasClave->end())
	{
		(*this->_palabrasClave)[palabra] = 1; //Se agrega la palabra y se pone el contador en uno
	}
	else
	{
		(*this->_palabrasClave)[palabra]++; // Se incrementa en uno el contador de apariciones de la palabra
	}
};

void Libro::copiarEstructuraDePalabrasClave(Libro* libroACopiar)
{
	EstructuraPalabrasClave* palabrasACopiar = libroACopiar->getPalabrasClave();

	EstructuraPalabrasClave::iterator it_palabras;

	std::string palabra;
	int ocurrenciasEnLibro;

	for (it_palabras = palabrasACopiar->begin(); it_palabras != palabrasACopiar->end(); it_palabras++)
	{
		palabra = (*it_palabras).first;
		ocurrenciasEnLibro = (*it_palabras).second;

		(*this->_palabrasClave)[palabra] = ocurrenciasEnLibro;
	}
}

std::vector<std::string> Libro::getOcurrenciasDeTerminos()
{
	return this->listaOcurrenciasDeTerminos;
}

void Libro::cargarOcurrenciaDeTermino(std::string termino)
{
	this->listaOcurrenciasDeTerminos.push_back(termino);
}
