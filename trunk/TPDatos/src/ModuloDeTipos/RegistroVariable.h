/*
 * RegistroVariable.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */


#ifndef REGISTROVARIABLE_H_
#define REGISTROVARIABLE_H_

#include <stdlib.h>
#include "Registro.h"



class RegistroVariable : public Registro{


public:
	RegistroVariable(const Datos& dato);
	virtual ~RegistroVariable();

	void eliminar();
	Datos serializarse();
	void hidratarse(const Datos& cadena);

	void setDato(const Datos& dato);
	Datos getDato() const;
	uint32_t getTamanioSerializado();

};

#endif /* REGISTROVARIABLE_H_ */
