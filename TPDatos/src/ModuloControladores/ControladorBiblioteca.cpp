/*
 * ControladorBiblioteca.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
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

	/* Tengo que preguntar donde escribo y despues pasarselo al registrar de
	 * archivo de control. Y despues guardarlo en el de archivo variables. */

	arcControl->registrarLibro(arcLibro->getPosicionActual());
	arcLibro->agregarLibro((char*) pathLibro.c_str());
}

bool ControladorBiblioteca::eliminarLibro(uint32_t offset) {
	//TODO actualizar el estado del control del archivo
	arcLibro->eliminar((uint32_t) offset);
}

DatoLibro ControladorBiblioteca::recuperarLibro(uint32_t offset) {
	return arcLibro->recuperarLibro(offset);
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
