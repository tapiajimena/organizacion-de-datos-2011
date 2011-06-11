/*
 * DatoTriada.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *  Representa la triada que contiene los datos correspondientes al id de libro,
 *	id de termino, posicion relativa del termino en el libro correspondiente.
 *
 */

#ifndef DATOTRIADA_H_
#define DATOTRIADA_H_

#include "Dato.h"

class DatoTriada: public Dato {
private:
	uint32_t idLibro;
	uint32_t idTermino;
	long posicion;

	/* Representa el offset donde se encuentra esa triada en el archivo
	 * de triadas.
	 */
	uint32_t id;

public:
	DatoTriada();
	DatoTriada(DatoTriada* d);

	/* Setter y Getters */
    uint32_t getId() const;
    uint32_t getIdLibro() const;
    uint32_t getIdTermino() const;
    long getPosicion() const;
    void setId(uint32_t id);
    void setIdLibro(uint32_t idLibro);
    void setIdTermino(uint32_t idTermino);
    void setPosicion(long  posicion);

	virtual ~DatoTriada();
};

#endif /* DATOTRIADA_H_ */
