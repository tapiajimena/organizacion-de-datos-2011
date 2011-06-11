/*
 * ParserDePalabras.h
 *
 *    Autor		 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *	Clase que ofrece el servicio de parseo de palabras para los libros. Hereda de ParserDeAtributo.
 */


#include "ParserDePalabras.h"

ParserDePalabras::ParserDePalabras(std::string nombreArchivoStopWords) {

	this->diccionarioStopWords = new Diccionario();

	this->diccionarioStopWords->cargarDiccionario();
}

ParserDePalabras::~ParserDePalabras() {
	delete this->diccionarioStopWords;
}

void ParserDePalabras::procesarLineaLibro(std::string linea, Libro* libro)
{
	//Definir si la cadena tiene el formato especial de alguno de los campos especiales...

	{
		palabra = ServiceClass::normalizarString(palabra);

Libro* ParserDePalabras::parsear(DatoLibro* datoLibro)
{

	//Creamos un libro vacío. Se le carga sólo la editorial.
   	Libro* libro = new Libro();

	//bool tituloEncontrado = false;
	bool finCadena = false;
				finCadena = true;
				if(posicionInicio < cadenaLibro.size()-1)
				{
					renglonLibro = cadenaLibro.substr(posicionInicio, cadenaLibro.size()-1);
				}
				else
					renglonLibro = "";
				}


}