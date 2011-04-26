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

#include <list>
#include "../ModuloDeArchivos/ArchivoLibro.h"
#include "../ModuloDeArchivos/ArchivoControlLibro.h"

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
	 *Devuelve un dato libro con el libro que se pidio.
	 * @param offset id del libro a recupertestControladorBiblioteca()ar
	 */
	DatoLibro recuperarLibro(uint32_t offset);


	/**
	 * Coloca el tipo de indexacion al libro correspondiente.
	 * @param idLibro: id del libro que se indexa.
	 * @param tipoClave: char que representa el tipo de indice.
	 */
	void registrarIndexadoArchivoControl(uint32_t idLibro, char tipoClave);

	/*
	 *Actualiza el archivo de control
	 */
	void actualizarArchivoDeControl();


	/*
	 * devuelve los libros no indexados por ese indice
	 * @param tipoIndice A E T P
	 */
	list<uint32_t> recuperarLibrosNoIndexadosPor(char tipoIndice);

	/*
	 * TODO implementar
	 * deberia recorrer a lista e ir insertando el tag en el archvio de control
	 */
	void registrarIndexado(list<DatoLibro> dLibros);

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
