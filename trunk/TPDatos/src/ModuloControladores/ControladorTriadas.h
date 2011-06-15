/*
 * ControladorTriadas.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "../ModuloDeArchivos/ArchivoTriadas.h"
#include "../ModuloDeArchivos/ArchivoControlTriadas.h"

#ifndef CONTROLADORTRIADAS_H_
#define CONTROLADORTRIADAS_H_

class ControladorTriadas {
private:
	ArchivoTriadas* arcTriadas;
	ArchivoControlTriadas* arcControl;
public:
	ControladorTriadas();
	ControladorTriadas(string pathTriadas, string pathControlTriadas);

	/**
	 * Actualiza el archivo de control de triadas
	 */
	void actualizarArchivoDeControl();

	/**
	 * Eliminar un libro del indice de terminos y su data de control
	 * en el archivo de control de terminos.
	 * @param offset id del libro a eliminar
	 */
	bool eliminarLibro(uint32_t offset);

	long int getSizeBiblioteca();
	string getPathBiblioteca();
	string getPathControlBiblioteca();

	virtual ~ControladorTriadas();
};

#endif /* CONTROLADORTRIADAS_H_ */