/*
 * DatoElementoNodo.h
 *
 *  Created on: 21/04/2011
 *      Author: paulo
 */

#ifndef DATOELEMENTONODO_H_
#define DATOELEMENTONODO_H_

#include "Dato.h"
#include "../Common/Utilitarios/ServiceClass.h"
#include <list>
#include <fstream>
#include <string.h>
#include <stdint.h>

class DatoElementoNodo: public Dato {

private:
	string clave;
	list<uint32_t> idLibros;
	list<uint32_t>::iterator it;

public:
	DatoElementoNodo();

	DatoElementoNodo(string clave);

	DatoElementoNodo(string clave, uint32_t idLibro);

	DatoElementoNodo(string clave, list<uint32_t> idLibros);

	//se llama en las hojas
	void serializar(iostream* stream);

	//se llama en las hojas
	//<TamanioClave><Clave><Cantidad_Id_Libros><Id_Libro>[]
	void hidratar(iostream* stream);

	//obtiene el tamanio que ocuparia en disco
	int getSize();

	DatoElementoNodo* clonar();

	void editar(string clave, iostream* ios);

	void setClave(string clave);

	int comparar(DatoElementoNodo* ele);

	string getClave();

	list<uint32_t> getLibros();

	int getCantidadLibros();

	void agregarLibro(uint32_t idLibro);

	void quitarLibro(uint32_t idLibro);

	void toString(iostream* ios, int rootLevel);

	string setTabs(int level);

	virtual ~DatoElementoNodo();
};

#endif /* DATOELEMENTONODO_H_ */
