/*
 * DatoElementoNodo.h
 *
 *  Created on: 21/04/2011
 *      Author: paulo
 */

#ifndef DATOELEMENTONODO_H_
#define DATOELEMENTONODO_H_

#include "Dato.h"
#include <list>
#include <fstream>
#include <string.h>
#include <stdint.h>

class DatoElementoNodo: public Dato {

private:
	string clave;
	list<uint32_t> idLibros;

public:
	DatoElementoNodo();

	//se llama en las hojas
	void serializar();

	//se llama en las hojas
	//<TamanioClave><Clave><Cantidad_Id_Libros><Id_Libro>[]
	void hidratar(stringstream* datoElementoNodo);

	void setClave(string clave);

	string getClave();

	list<uint32_t> getLibros();

	void agregarLibro(uint32_t idLibro);


	virtual ~DatoElementoNodo();
};

#endif /* DATOELEMENTONODO_H_ */
