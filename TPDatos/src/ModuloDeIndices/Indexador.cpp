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
	Configuracion* conf = Configuracion::GetInstancia();
	pathCarpeta = conf->getPathCarpetaTrabajo();
	controlIndice = new ControladorIndice(pathCarpeta);
	controlBiblioteca = new ControladorBiblioteca(pathCarpeta+ARCHIVO_BIBLIOTECA,
			pathCarpeta+ARCHIVO_CONTROL_BIBLIOTECA);
}

Indexador::Indexador(string pathCarpeta)
{
	pathCarpeta = pathCarpeta;
	CrearDirectorios(pathCarpeta);
	controlIndice = new ControladorIndice(pathCarpeta);
	controlBiblioteca = new ControladorBiblioteca(pathCarpeta+ARCHIVO_BIBLIOTECA,
			pathCarpeta+ARCHIVO_CONTROL_BIBLIOTECA);
}


void Indexador::indexar(char tipoIndice)
{
	Libro*					libro;
	DatoLibro*				dLibro;
	list<uint32_t> 			idLibros;
	pair<Libro*,uint32_t>	parLibroOffset;


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

	if (!idLibros.empty())
	{
		list<uint32_t>::iterator it;
		for(it = idLibros.begin(); it != idLibros.end(); ++it)
		{
			libro = new Libro();
			dLibro = new DatoLibro(controlBiblioteca->recuperarLibro(*it));

			libro = parser->parsear(dLibro);

			parLibroOffset.first 	= libro;
			parLibroOffset.second 	= *it;
			controlIndice->indexar(parLibroOffset, tipoIndice);
			controlBiblioteca->registrarIndexadoArchivoControl(*it, tipoIndice);

			delete (libro);
			delete(dLibro);
		}
		this->controlBiblioteca->actualizarArchivoDeControl();
	}
	else
		Logger::log("Indexador","indexar","Todos los libros ya han sido indexados.");

	delete(parser);
}


void Indexador::eliminarIndexado(uint32_t idLibro)
{
	Libro *libroRemover = controlBiblioteca->cargarNuevoLibroParseado(idLibro);

	controlIndice->eliminarIndexado(libroRemover);

	//por ultimo se elimina el libro de control biblioteca
	controlBiblioteca->eliminarLibro(idLibro);
	delete(libroRemover);
}


Indexador::~Indexador()
{
	delete(controlBiblioteca);
	delete(controlIndice);

}






















