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
	ArchivoTriadas* 		arcTriadas;
	ArchivoControlTriadas* 	arcControl;
	list<DatoTriada*>* 		triadas;
	uint32_t				offsetAEscribir;
public:
	ControladorTriadas();
	ControladorTriadas(string pathTriadas, string pathControlTriadas);

	/**
	 * Actualiza el archivo de control de triadas
	 */
	void actualizarArchivoDeControl();

	/**
	 * Inserta la triada al final del archivo de triadas
	 * y se actualiza el archivo de control.
	 * @param triada dato a insertar
	 */
	void insertarTriadaAlFinal(DatoTriada* triada);

	/**
	 * Inserta la triada en el archivo de triadas
	 * y se actualiza el archivo de control.
	 * @param triada: dato a insertar
	 * @param offset: offset donde escribir la nueva triada.
	 */
	void insertarTriada(DatoTriada* triada, uint32_t offset);

	/**
	 * Inserta nuevo dato de control de triadas.
	 * @param datoControlTriada: dato de control a ser agregado.
	 */
	void insertarDatosControlTriadas(DatoControlTriada* datoControlTriada);

	/**
	 * Eliminar un libro del indice de terminos y su data de control
	 * en el archivo de control de terminos.
	 * @param offset id del libro a eliminar
	 */
	bool eliminarLibro(uint32_t offset);

	/**
	 * Devuelve todas las triadas de terminos pertenecientes a un libro.
	 * @param id_Libro: id del libro del que se quieren obtener las triadas.
	 */
	list<DatoTriada*>* getTriadas(uint32_t id_Libro);

	/**
	 * Devuelve todas las triadas que corresponden con los offsets.
	 * @param offsets: lista de identificados de triadas que se corresponde con
	 * 				   la posicion de la triada en el archivo de triadas.
	 */
	list<DatoTriada*>* getTriadas(list<uint32_t> offsets);

	/**
	 * Devuelve la triada que esta en la posicion (offset) pasada por
	 * parametro en la lista de triadas.
	 * @param offsetTriada offset en archivo de triadas.
	 */
	DatoTriada* getTriada(uint32_t offsetTriada);

	/**
	 * Devuelve el offset donde se comenzaran a escribir las triadas
	 * de un libro especifico.
	 * @param cantidadTriadas: cantidad de triadas en el libro.
	 */
	uint32_t dondeEscribo(int cantidadTriadas, uint32_t idLibro);

	uint32_t getSiguienteIdTriada();


	/**
	 * Devuelve el tamanio del archivo de triadas.
	 */
	uint32_t getSizeArchivoTriadas();

	string getPathBiblioteca();
	string getPathControlBiblioteca();

	void setDatoControlEliminado(bool e);
	bool getDatoControlEliminado();


	virtual ~ControladorTriadas();
};

#endif /* CONTROLADORTRIADAS_H_ */
