/*
 * RegistroFijo.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#ifndef REGISTROFIJO_H_
#define REGISTROFIJO_H_

#include "Registro.h"

/*
 *
 */
class RegistroFijo: public Registro {
public:
	RegistroFijo();
	RegistroFijo(const Datos& dato);

	virtual Datos serializarse();
	virtual void hidratarse(const Datos& d);
	virtual uint32_t getTamanioSerializado();


	virtual ~RegistroFijo();
};

#endif /* REGISTROFIJO_H_ */
