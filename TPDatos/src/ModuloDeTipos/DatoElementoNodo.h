/*
 * DatoElementoNodo.h
 *
 *  Created on: 21/04/2011
 *      Author: paulo
 */

#ifndef DATOELEMENTONODO_H_
#define DATOELEMENTONODO_H_

#include "Dato.h"
#include "../Common/Utilitarios/Logger.h"
#include "../Common/Utilitarios/ServiceClass.h"
#include <list>
#include <fstream>
#include <string.h>
#include <stdint.h>

class DatoElementoNodo: public Dato {

private:
	/*
	 * used for front coding
	 */
	short int cantidadLetrasClaveAnterior;
	short int cantidadLetrasClaveActual;

	string clave;
	list<uint32_t> idLibros;
	list<uint32_t>::iterator it;

public:
	DatoElementoNodo();

	DatoElementoNodo(string clave);

	DatoElementoNodo(string clave, uint32_t idLibro);

	DatoElementoNodo(string clave, list<uint32_t> idLibros);

	//se llama en las hojas
	//<CantidadLetrasClaveAnterior><CantidadLetrasClaveActual><Clave><Cantidad_Id_Libros><Id_Libro>[]
	void serializar(iostream* stream);

	//se llama en las hojas
	//<CantidadLetrasClaveAnterior><CantidadLetrasClaveActual><Clave><Cantidad_Id_Libros><Id_Libro>[]
	void hidratar(iostream* stream);

	//obtiene el tamanio que ocuparia en disco
	int getSize();

	DatoElementoNodo* clonar();

	void setClave(string clave);

	int comparar(DatoElementoNodo* ele);

	string getClave();

	list<uint32_t> getLibros();

	int getCantidadLibros();

	void agregarLibro(uint32_t idLibro);

	void quitarLibro(uint32_t idLibro);

	void toString(iostream* ios, int rootLevel);

	short int getCantidadLetrasClaveAnterior();

	short int getCantidadLetrasClaveActual();

	void setCantidadLetrasClaveAnterior(short int cant);

	void setCantidadLetrasClaveActual(short int cant);

	string setTabs(int level);

	virtual ~DatoElementoNodo();
};

#endif /* DATOELEMENTONODO_H_ */
