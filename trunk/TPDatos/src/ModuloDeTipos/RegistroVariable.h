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

#include "Registro.h"



class RegistroVariable : public Registro
{


public:
	RegistroVariable();
	RegistroVariable(const Datos& dato);

	virtual void eliminar();
	virtual Datos serializarse();
	virtual void hidratarse(const Datos& cadena);

	virtual void setDato(const Datos& dato);
	virtual Datos getDato();
	virtual uint32_t getTamanioSerializado();


	virtual ~RegistroVariable();
};

#endif /* REGISTROVARIABLE_H_ */
