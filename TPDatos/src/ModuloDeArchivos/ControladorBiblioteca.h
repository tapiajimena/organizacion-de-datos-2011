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

#ifndef CONTROLADORBIBLIOTECA_H_
#define CONTROLADORBIBLIOTECA_H_

#include "ArchivoLibro.h"
#include "ArchivoControlLibro.h"

class ControladorBiblioteca {
private:
	ArchivoLibro* arcLibro;
	ArchivoControlLibro* arcControl;

public:
	ControladorBiblioteca();

	/*
	 * crea el ArchivoLibro y su archivo de control, con los path indicados.
	 * @param pathBiblioteca path del archivo de biblioteca
	 * @param pathControlBiblioteca path de control de la biblioteca
	 */
	ControladorBiblioteca(string pathBiblioteca, string pathControlBiblioteca);


	/*
	 * agrega un libro a la biblioteca y su data de control en el archivo de control
	 * @param pathLibro ruta del libro a agregar
	 */
	bool ingresarLibro(string pathLibro);


	/*
	 * elimina un libro a la biblioteca y su data de control en el archivo de control
	 * @param offset id del libro a eliminar
	 */
	bool eliminarLibro(uint32_t offset);


	string getPathBiblioteca();
	string getPathControlBiblioteca();




	virtual ~ControladorBiblioteca();
};

#endif /* CONTROLADORBIBLIOTECA_H_ */
