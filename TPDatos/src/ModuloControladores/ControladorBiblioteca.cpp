/*
 * ControladorBiblioteca.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ControladorBiblioteca.h"

ControladorBiblioteca::ControladorBiblioteca() {

}

ControladorBiblioteca::ControladorBiblioteca(string pathBiblioteca,
		string pathControlBiblioteca) {
	arcLibro = new ArchivoLibro(pathBiblioteca);
	arcControl = new ArchivoControlLibro(pathControlBiblioteca);

	Logger::log("ControladorBiblioteca", "ControladorBiblioteca",
			"Se cargan los libros.");
}

bool ControladorBiblioteca::ingresarLibro(string pathLibro) {
	uint32_t sizeLibroIngresado = GetSizeArchivo(pathLibro);

	if (sizeLibroIngresado > 0)
	{
		/* Se actualiza la insercion en el archivo de control */
		uint32_t nuevoOffset = arcControl->registrarLibro(
				sizeLibroIngresado, arcLibro->getSizeArchivo());

		Logger::log("ControladorBiblioteca", "ingresarLibro",
				"Se registra el libro en el archivo de control.");

		Logger::log("ControladorBiblioteca", "ingresarLibro",
				ServiceClass::toString(nuevoOffset));

		/* Se agrega el libro en el archivo de registros variables */
		arcLibro->agregarLibro((char*) pathLibro.c_str(), nuevoOffset);

		Logger::log("ControladorBiblioteca", "ingresarLibro",
				"Se agrega un libro en el archivo de registros variables.");

		arcControl->actualizarArchivo();

		Logger::log("ControladorBiblioteca", "ingresarLibro",
				"Se actualiza el archivo de control.");
	}
	else
		Logger::log("ControladorBiblioteca", "ingresarLibro","El libro a ingresar no existe, verifique.");
}

bool ControladorBiblioteca::eliminarLibro(uint32_t offset) {
	DatoLibro datoLibro = recuperarLibro(offset);

	/* Actualiza el estado del archivo de control */
	arcControl->eliminarLibro(offset, datoLibro.getSize());

	Logger::log("ControladorBiblioteca", "eliminarLibro",
			"Se elimina el libro.");

	arcControl->actualizarArchivo();

	Logger::log("ControladorBiblioteca", "eliminarLibro",
			"Se actualiza el archivo de control.");
}

DatoLibro ControladorBiblioteca::recuperarLibro(uint32_t offset) {
	return arcLibro->recuperarLibro(offset);
}


list<uint32_t> ControladorBiblioteca::recuperarLibrosNoIndexadosPor(char tipoIndice)
{
	//TODO como se hace para obtener el offset a libro del controlBiblioteca
	list<uint32_t> idLibros;
	DatoControlLibro* dControlLibro;
	map<uint32_t,DatoControlLibro*>::iterator it;

	//arcControl->cargarLibros();
	map<uint32_t,DatoControlLibro*>* librosControl = arcControl->getLibros();

	if (!librosControl->empty())
	{

		it = librosControl->begin();
		while (it != librosControl->end())
		{
			dControlLibro = (*it).second;
			//si no fue borrado y tiene el indice deseado => se agrega
			if ((!dControlLibro->isIndexadoPor(tipoIndice))&& (dControlLibro->getEspacioLibre()==0))
				idLibros.push_back((*it).first);
			it++;
		}
	}
	else
		Logger::log("ControladorBiblioteca", "recuperarLibrosNoIndexadosPor","la lista de control esta vacia");
	return idLibros;
}



list<uint32_t> ControladorBiblioteca::recuperarLibrosDeBiblioteca()
{
	//TODO como se hace para obtener el offset a libro del controlBiblioteca
	//TODO REFACTORIZAR CON RECUPERARLIBROSNOINDEXADOSPOR
	list<uint32_t> idLibros;
	DatoControlLibro* dControlLibro;
	map<uint32_t,DatoControlLibro*>::iterator it;

	//arcControl->cargarLibros();
	map<uint32_t,DatoControlLibro*>* librosControl = arcControl->getLibros();

	if (!librosControl->empty())
	{

		it = librosControl->begin();
		while (it != librosControl->end())
		{
			dControlLibro = (*it).second;
			//si no fue borrado => se agrega
			if (dControlLibro->getEspacioLibre()==0)
				idLibros.push_back((*it).first);
			it++;
		}
	}
	else
		Logger::log("ControladorBiblioteca", "recuperarLibrosNoIndexadosPor","la lista de control esta vacia");
	return idLibros;
}

Libro* ControladorBiblioteca::cargarNuevoLibroParseado(uint32_t idLibro)
{
	Libro *libroAutor, *libroEditorial, *libroTitulo,*libroPalabras, *libroNuevo;
	DatoLibro* dLibro;
	ParserDeAtributo *parserAutor, *parserEditorial, *parserPalabras, *parserTitulo;
	pair<Libro*,uint32_t>	parLibroOffset;


	//se recupera el libro a eliminar
	dLibro = new DatoLibro(this->recuperarLibro(idLibro));
	libroNuevo = new Libro();


	//TODO refactorizar y modularizar estaria bueno poder parser en el mismo libro distintos parsers
	//se parsea para obtener la clave y luego eliminarla del indice
	parserAutor = new ParserDeAutor();
	libroAutor 	= new Libro();
	libroAutor 	=parserAutor->parsear(dLibro);

	libroNuevo->setAutor(libroAutor->getAutor());
	delete(libroAutor);
	delete(parserAutor);

	//se parsea para obtener la clave y luego eliminarla del indice
	parserEditorial = new ParserDeEditorial();
	libroEditorial 	= new Libro();
	libroEditorial 	= parserEditorial->parsear(dLibro);

	libroNuevo->setEditorial(libroEditorial->getEditorial());
	delete(libroEditorial);
	delete(parserEditorial);


	parserTitulo= new ParserDeTitulo();
	libroTitulo	= new Libro();
	libroTitulo	= parserTitulo->parsear(dLibro);

	libroNuevo->setTitulo(libroTitulo->getTitulo());
	delete(libroTitulo);
	delete(parserTitulo);

/*
 	 //TODO terminar de eliminar la lista de palabras
	parserPalabras	= new ParserDePalabras(ARCHIVO_STOPWORDS);
	libroPalabras 	= new Libro();
	libroPalabras 	= parserPalabras->parsear(dLibro);

	libroNuevo->setPalabras(libroAutor->getAutor());
	delete(libroAutor);
	delete(parserAutor);

	cout<<"LIBRO PARSEADO IMPRIME: "<<libroPalabras->getPalabrasClave()->back()<<endl;
*/

	return libroNuevo;
}

void ControladorBiblioteca::actualizarArchivoDeControl()
{
	arcControl->actualizarArchivo();
}

void ControladorBiblioteca::registrarIndexadoArchivoControl(uint32_t idLibro, char tipoClave)
{
	arcControl->registrarIndexado(idLibro, tipoClave);
}


string ControladorBiblioteca::getPathControlBiblioteca() {
	return arcControl->getPathArchivoControlLibro();
}

string ControladorBiblioteca::getPathBiblioteca() {
	return arcLibro->getPath();
}

ControladorBiblioteca::~ControladorBiblioteca() {
	delete arcLibro;
	delete arcControl;
}
