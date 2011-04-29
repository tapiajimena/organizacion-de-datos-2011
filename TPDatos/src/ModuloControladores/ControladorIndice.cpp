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


void ControladorIndice::indexar(pair<Libro*,uint32_t> parLibroOffset, char tipoIndice)
{
	//si queda tiempo crear clases
	if ((tipoIndice == INDICE_AUTOR)||(tipoIndice == INDICE_EDITORIAL))
		indexarPorAutorOEditorial(parLibroOffset);
	else if(tipoIndice == INDICE_TITULO)
		indexarPorTitulo(parLibroOffset);
	else if(tipoIndice == INDICE_PALABRAS)
		indexarPorPalabras(parLibroOffset);
	else
		Logger::log("ControladorIndice","indexar","El tipo de indice no existe, verifique que sea A,E,T,P");
}


void ControladorIndice::eliminarIndexado(Libro* libroRemover)
{
	//se remueven los indices de autor del arbol
	ArbolBMas* indiceAutorArbol = new ArbolBMas(pathCarpeta+ARCHIVO_INDICE_AUTOR, SIZE_BLOQUE);
	//indiceAutorArbol->eliminar(libroRemover->getAutor());
	delete(indiceAutorArbol);

	//se remueven los indices de editorial del arbol
	ArbolBMas* indiceEditorialArbol = new ArbolBMas(pathCarpeta+ARCHIVO_INDICE_EDITORIAL, SIZE_BLOQUE);
	//indiceEditorialArbol->eliminar(libroRemover->getEditorial());
	delete(indiceEditorialArbol);

	//se remueven los indices de titulo del hash
	Hash* indiceTituloHash= new Hash(pathCarpeta+ARCHIVO_INDICE_TITULO, pathCarpeta+ARCHIVO_CUBETAS);
	//indiceTituloHash->eliminar(libroRemover->getAutor());
	delete(indiceTituloHash);


	/*
	 //TODO hacer llegar la lista de palabras
	//se remueven los indices de palabras el hash
	Hash* indicePalabrasHash= new Hash(pathCarpeta+ARCHIVO_INDICE_PALABRAS, pathCarpeta+ARCHIVO_CUBETAS);
	indicePalabrasHash->eliminar(ACA LA LISTA DE PALABRAS);
	delete(indicePalabrasHash);
	*/

}


void ControladorIndice::indexarPorAutorOEditorial(pair<Libro*,uint32_t> parLibroOffset)
{
	DatoElementoNodo* ele = new DatoElementoNodo();

	ele->setClave(((Libro*)(parLibroOffset.first))->getAutor());
	ele->agregarLibro(parLibroOffset.second);

	//this->indiceArbol->insertar(ele);
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



