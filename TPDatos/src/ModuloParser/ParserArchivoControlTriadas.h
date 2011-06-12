/*
 * ParserArchivoControlTriadas.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 */

#ifndef PARSERARCHIVOCONTROLTRIADAS_H_
#define PARSERARCHIVOCONTROLTRIADAS_H_

#include "ParserTriadas.h"
#include "../ModuloDeTipos/DatoControlTriada.h"

class ParserArchivoControlTriadas: public ParserTriadas {
private:
	DatoControlTriada* datoNuevo;
public:
	ParserArchivoControlTriadas(string token);

	bool determinarEliminado();
	virtual void cargarEstructura(string dato);

	virtual ~ParserArchivoControlTriadas();
};

#endif /* PARSERARCHIVOCONTROLTRIADAS_H_ */
