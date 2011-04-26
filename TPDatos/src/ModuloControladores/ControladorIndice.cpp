/*
 * ControladorIndice.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#include "ControladorIndice.h"


ControladorIndice::ControladorIndice()
{
	this->pathCarpeta = CARPETA_DEFAULT_INDICES;
}


ControladorIndice::ControladorIndice(string pathCarpeta)
{
	this->pathCarpeta = pathCarpeta;
}


void ControladorIndice::nuevoIndiceAutor()
{
		this->indiceArbol = new ArbolBMas(pathCarpeta+ARCHIVO_INDICE_AUTOR, SIZE_BLOQUE);
}


void ControladorIndice::nuevoIndiceEditorial()
{
	this->indiceArbol = new ArbolBMas(pathCarpeta+ARCHIVO_INDICE_EDITORIAL, SIZE_BLOQUE);
}


void ControladorIndice::nuevoIndiceTitulo()
{
	this->indiceArbol = new ArbolBMas(pathCarpeta+ARCHIVO_INDICE_TITULO, SIZE_BLOQUE);
}


void ControladorIndice::nuevoIndicePalabras()
{
	this->indiceArbol = new ArbolBMas(pathCarpeta+ARCHIVO_INDICE_PALABRAS, SIZE_BLOQUE);
}


void ControladorIndice::indexarPorAutor(pair<Libro*,uint32_t> parLibroOffset)
{
	DatoElementoNodo* ele = new DatoElementoNodo();


	ele->setClave(((Libro*)(parLibroOffset.first))->getAutor());
	ele->agregarLibro(parLibroOffset.second);

	this->indiceArbol->insertar(ele);
	delete(ele);
}


void ControladorIndice::indexarPorEditorial(pair<Libro*,uint32_t> parLibroOffset)
{
	DatoElementoNodo* ele = new DatoElementoNodo();

	ele->setClave(((Libro*)(parLibroOffset.first))->getEditorial());
	ele->agregarLibro(parLibroOffset.second);

	this->indiceArbol->insertar(ele);
	delete(ele);
}


void ControladorIndice::indexarPorTitulo(pair<Libro*,uint32_t> parLibroOffset)
{
	pair<string,uint32_t> registroHash(parLibroOffset.first->getTitulo(), parLibroOffset.second);
	this->indiceHash->insertarClave(registroHash);
}


void ControladorIndice::indexarPorPalabras(pair<Libro*,uint32_t> parLibroOffset)
{
	string 	aux;
	pair<string,uint32_t> 				registroHash;
	EstructuraPalabrasClave::iterator 	it;

	for(it =parLibroOffset.first->getPalabrasClave()->begin();it!=parLibroOffset.first->getPalabrasClave()->end();++it)
	{
		aux = ServiceClass::normalizarString((*it).first);
		registroHash.first = aux;
		registroHash.second= parLibroOffset.second;
		this->indiceHash->insertarClave(registroHash);
	}
}


ControladorIndice::~ControladorIndice()
{
	delete (indiceHash);
	delete (indiceArbol);
}




