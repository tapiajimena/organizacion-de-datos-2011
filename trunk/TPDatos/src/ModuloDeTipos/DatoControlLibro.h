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
#include "../../Common/Utilitarios/Logger.h"
#include "../../Common/Constantes.h"

using namespace std;

class DatoControlLibro: public Dato {
private:
	uint32_t id_Libro;
	uint32_t espacioLibre;
	list<char>* indexado;
	uint32_t offset;
public:
	DatoControlLibro();
	DatoControlLibro(DatoControlLibro* d);
	DatoControlLibro(uint32_t id_Libro, uint32_t espacioLibre,
			list<char>* indexado, uint32_t offset);

	friend bool operator< (const DatoControlLibro  &primero, const DatoControlLibro &segundo);

	/*
	 * Devuelve si el libro esta indexado por un tipo.
	 * @param tipo puede ser A, T, E, P refiriendose a los tipos de indexacion que hay
	 */
	bool isIndexadoPor(char tipo);

	string serializar();

	/* Getters y Setters */
	uint32_t getEspacioLibre() const;
	uint32_t getId_Libro() const;
	list<char> * getIndexado() const;
	uint32_t getOffset() const;
	void setEspacioLibre(uint32_t espacioLibre);
	void setId_Libro(uint32_t id_Libro);
	void setIndexado(list<char> *indexado);
	void setOffset(uint32_t offset);

	virtual ~DatoControlLibro();
};

#endif /* DATOCONTROLLIBRO_H_ */

