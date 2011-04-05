/*
 * Registro.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <stdint.h>
#include <iostream>
#include <sstream>
#include "Datos.h"
#include "../Common/Constantes.h"

using namespace std;
class Registro {

protected:
	uint32_t id;
	Datos dato;
	bool eliminado;

public:
	Registro();
	Registro(const Datos& dato);


	void eliminar();
	virtual Datos serializarse() = 0;
	virtual void hidratarse(const Datos& d) = 0;

	void setDato(const Datos& dato);
	Datos getDato() const;

	void setId(const uint32_t& id);
	uint32_t getId() const;

	virtual uint32_t getTamanioSerializado() = 0;

	virtual ~Registro();
};

#endif /* REGISTRO_H_ */
