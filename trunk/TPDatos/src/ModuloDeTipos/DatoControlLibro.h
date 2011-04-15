/*
 * DatoControlLibro.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#ifndef DATOCONTROLLIBRO_H_
#define DATOCONTROLLIBRO_H_

#include <list>
#include <stdint.h>

#include "Dato.h"

using namespace std;

class DatoControlLibro: public Dato {
private:
	uint32_t id_Libro;
	uint32_t espacioLibre;
	list<char>* indexado;
	bool modificado;
	uint32_t offset;
public:
	DatoControlLibro();
	DatoControlLibro(uint32_t id_Libro, uint32_t espacioLibre,
			list<char>* indexado, bool modificado, uint32_t offset);

	/* Getters y Setters */
	uint32_t getEspacioLibre() const;
	uint32_t getId_Libro() const;
	list<char> * getIndexado() const;
	bool getModificado() const;
	uint32_t getOffset() const;
	void setEspacioLibre(uint32_t espacioLibre);
	void setId_Libro(uint32_t id_Libro);
	void setIndexado(list<char> *indexado);
	void setModificado(bool modificado);
	void setOffset(uint32_t offset);

	virtual ~DatoControlLibro();
};

#endif /* DATOCONTROLLIBRO_H_ */
