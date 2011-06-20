/*
 * DatoLibro.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#ifndef DATOLIBRO_H_
#define DATOLIBRO_H_

#include "Dato.h"


class DatoLibro : public Dato {
public:
	DatoLibro();
	DatoLibro(char* c);
	DatoLibro(string d);
	DatoLibro(const DatoLibro & d);


	bool agregar(const Dato & d,unsigned int posicion);

	bool agregarAlFinal(const Dato & d);

	virtual ~DatoLibro();
};

#endif /* DATOLIBRO_H_ */
