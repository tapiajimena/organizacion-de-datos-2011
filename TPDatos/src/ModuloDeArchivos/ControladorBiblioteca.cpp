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


ControladorBiblioteca::ControladorBiblioteca()
{


}

ControladorBiblioteca::ControladorBiblioteca(string pathBiblioteca, string pathControlBiblioteca)
{
    arcLibro = new ArchivoLibro(pathBiblioteca);
    arcControl = new ArchivoControlLibro(pathControlBiblioteca);
}

bool ControladorBiblioteca::ingresarLibro(string pathLibro)
{
	arcControl->registrarLibro(arcLibro->getPosicionActual());
	arcLibro->agregarLibro((char*)pathLibro.c_str());
}


bool ControladorBiblioteca::eliminarLibro(uint32_t offset)
{
	//TODO actualizar el estado del control del archivo
	arcLibro->eliminar(offset);
}

string ControladorBiblioteca::getPathControlBiblioteca()
{
	return arcControl->getPathArchivoControlLibro();
}

string ControladorBiblioteca::getPathBiblioteca()
{
	return arcLibro->getPath();
}


ControladorBiblioteca::~ControladorBiblioteca() {
	delete arcLibro;
	delete arcControl;
}
