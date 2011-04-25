/*
 * Indexador.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "Indexador.h"

Indexador::Indexador()
{
	pathCarpeta = CARPETA_DEFAULT_INDICES;
	controlIndice = new ControladorIndice(pathCarpeta);
	CrearDirectorios(pathCarpeta);

}

Indexador::Indexador(string pathCarpeta)
{
	pathCarpeta = pathCarpeta;
	controlIndice = new ControladorIndice(pathCarpeta);
	CrearDirectorios(pathCarpeta);
}


void Indexador::indexar(char tipoIndice)
{
	Libro*					libro;
	DatoLibro*				dLibro;
	list<uint32_t> 			idLibros;
	pair<Libro*,uint32_t>	parLibroOffset;

	controlBiblioteca = new ControladorBiblioteca(pathCarpeta+ARCHIVO_BIBLIOTECA,
			pathCarpeta+ARCHIVO_CONTROL_BIBLIOTECA);

	switch(tipoIndice)
	{
		case INDICE_AUTOR:
			parser = new ParserDeAutor();
			controlIndice->nuevoIndiceAutor();
		break;
		case INDICE_EDITORIAL:
			parser = new ParserDeEditorial();
			controlIndice->nuevoIndiceEditorial();
		break;
		case INDICE_PALABRAS:
			parser = new ParserDePalabras(ARCHIVO_STOPWORDS);
			controlIndice->nuevoIndicePalabras();
		break;
		case INDICE_TITULO:
			parser = new ParserDeTitulo();
			controlIndice->nuevoIndiceTitulo();
		break;
	}

	idLibros = controlBiblioteca->recuperarLibrosNoIndexadosPor(tipoIndice);

	list<uint32_t>::iterator it;
	for(it = idLibros.begin(); it != idLibros.end(); ++it)
	{
		libro = new Libro();
		dLibro = new DatoLibro(controlBiblioteca->recuperarLibro(*it));
		libro = parser->parsear(dLibro);

		parLibroOffset.first 	= libro;
		parLibroOffset.second 	= *it;
		controlIndice->indexarPorAutor(parLibroOffset);

		delete (libro);
		delete(dLibro);
	}
}

/*
 //DEPROCATED
void Indexador::indexarAutores()
{
	Libro*					libro;
	DatoLibro				dLibro;
	list<uint32_t> 			idLibros;
	pair<Libro*,uint32_t>	parLibroOffset;

	parser = new ParserDeAutor();
	controlIndice->nuevoIndiceAutor();
	controlBiblioteca = new ControladorBiblioteca(pathCarpeta+ARCHIVO_BIBLIOTECA,
			pathCarpeta+ARCHIVO_CONTROL_BIBLIOTECA);

	idLibros = controlBiblioteca->recuperarLibrosNoIndexadosPor(INDICE_AUTOR);

	list<uint32_t>::iterator it;
	for(it = idLibros.begin(); it != idLibros.end(); ++it)
	{
		libro = new Libro();
		dLibro = controlBiblioteca->recuperarLibro(*it);
		libro = parser->parsear(&dLibro);

		parLibroOffset.first 	= libro;
		parLibroOffset.second 	= *it;
		controlIndice->indexarPorAutor(parLibroOffset);

		delete (libro);
	}
}
*/


Indexador::~Indexador()
{
	delete(parser);
	delete(controlIndice);
	delete(controlBiblioteca);
}
