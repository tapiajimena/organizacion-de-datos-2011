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
}

bool ControladorBiblioteca::ingresarLibro(string pathLibro) {

	/* Se agrega el libro en el archivo de registros variables */
	arcLibro->agregarLibro((char*) pathLibro.c_str());

	/* Se actualiza la insercion en el archivo de control */
	//uint32_t nuevoOffset = arcControl->registrarLibro(size,finArchivoLibros);

	/* Tengo que preguntar donde escribo y despues pasarselo al registrar de
	 * archivo de control. Y despues guardarlo en el de archivo variables. */

}

bool ControladorBiblioteca::eliminarLibro(uint32_t offset) {
	//TODO actualizar el estado del control del archivo
	arcLibro->eliminar((uint32_t) offset);
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
	map<uint32_t,DatoControlLibro*>* librosControl = arcControl->getLibros();


	map<uint32_t, DatoControlLibro*>::iterator it_aux;

	while (it != librosControl->end())
	{
		dControlLibro = (*it).second;
		if (dControlLibro->isIndexadoPor(tipoIndice))
			idLibros.push_back((*it).first);
	}
	return idLibros;
}


string ControladorBiblioteca::getPathControlBiblioteca() {
	//return arcControl->getPathArchivoControlLibro();
}

string ControladorBiblioteca::getPathBiblioteca() {
	return arcLibro->getPath();
}

ControladorBiblioteca::~ControladorBiblioteca() {
	delete arcLibro;
	delete arcControl;
}
