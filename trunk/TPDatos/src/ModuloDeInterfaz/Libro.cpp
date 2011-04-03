/*
 * Libro.cpp
 *
 */

#include "Libro.h"

Libro::Libro()
{
};

Libro::~Libro()
{
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

std::string Libro::getISBN()
{
	return this->_ISBN;
};

void Libro::setISBN(std::string ISBN)
{
	this->_ISBN = ISBN;
};

std::vector<std::string> Libro::getListaPalabras()
{
	return this->_listaPalabras;
};

void Libro::agregarPalabra(std::string palabra)
{
	this->_listaPalabras.push_back(palabra);
};
