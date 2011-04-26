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
	/* Se actualiza la insercion en el archivo de control */
	uint32_t nuevoOffset = arcControl->registrarLibro(
			GetSizeArchivo(pathLibro), arcLibro->getSizeArchivo());



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

	arcControl->cargarLibros();
	map<uint32_t,DatoControlLibro*>* librosControl = arcControl->getLibros();

	if (!librosControl->empty())
	{

		it = librosControl->begin();
		while (it != librosControl->end())
		{
			dControlLibro = (*it).second;
			if (!dControlLibro->isIndexadoPor(tipoIndice))
				idLibros.push_back((*it).first);
			it++;
		}
	}
	else
		Logger::log("ControladorBiblioteca", "recuperarLibrosNoIndexadosPor","la lista de control esta vacia");
	return idLibros;
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
