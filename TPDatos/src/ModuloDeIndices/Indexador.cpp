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
	CrearDirectorios(pathCarpeta);
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
	Libro *libroAutor, *libroEditorial, *libroTitulo,*libroPalabras, *libroRemover;
	DatoLibro* dLibro;
	ParserDeAtributo *parserAutor, *parserEditorial, *parserPalabras, *parserTitulo;
	pair<Libro*,uint32_t>	parLibroOffset;


	//se recupera el libro a eliminar
	dLibro = new DatoLibro(controlBiblioteca->recuperarLibro(idLibro));
	libroRemover = new Libro();



	//TODO refactorizar y modularizar estaria bueno poder parser en el mismo libro distintos parsers
	//se parsea para obtener la clave y luego eliminarla del indice
	parserAutor = new ParserDeAutor();
	libroAutor 	= new Libro();
	libroAutor 	=parserAutor->parsear(dLibro);

	libroRemover->setAutor(libroAutor->getAutor());
	delete(libroAutor);
	delete(parserAutor);

	cout<<"LIBRO PARSEADO IMPRIME AUTOR: "<<libroRemover->getAutor()<<endl;


	//se parsea para obtener la clave y luego eliminarla del indice
	parserEditorial = new ParserDeEditorial();
	libroEditorial 	= new Libro();
	libroEditorial 	= parserEditorial->parsear(dLibro);

	libroRemover->setEditorial(libroEditorial->getEditorial());
	delete(libroEditorial);
	delete(parserEditorial);

	cout<<"LIBRO PARSEADO IMPRIME EDITORIAL: "<<libroRemover->getEditorial()<<endl;

	parserTitulo= new ParserDeTitulo();
	libroTitulo	= new Libro();
	libroTitulo	= parserTitulo->parsear(dLibro);

	libroRemover->setTitulo(libroTitulo->getTitulo());
	delete(libroTitulo);
	delete(parserTitulo);

	cout<<"LIBRO PARSEADO IMPRIME TITULO: "<<libroRemover->getTitulo()<<endl;

/*
 	 //TODO terminar de eliminar la lista de palabras
	parserPalabras	= new ParserDePalabras(ARCHIVO_STOPWORDS);
	libroPalabras 	= new Libro();
	libroPalabras 	= parserPalabras->parsear(dLibro);

	libroRemover->setPalabras(libroAutor->getAutor());
	delete(libroAutor);
	delete(parserAutor);

	cout<<"LIBRO PARSEADO IMPRIME: "<<libroPalabras->getPalabrasClave()->back()<<endl;
*/


	controlIndice->eliminarIndexado(libroRemover);

	//por ultimo se elimina el libro
	controlBiblioteca->eliminarLibro(idLibro);


}


Indexador::~Indexador()
{
	delete(controlIndice);
	delete(controlBiblioteca);
}






















