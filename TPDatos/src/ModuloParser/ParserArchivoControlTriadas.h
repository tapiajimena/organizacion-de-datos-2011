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
	map<uint32_t,DatoControlTriada*>::iterator it;
	map<uint32_t,DatoControlTriada*>* datosControl;
public:
	ParserArchivoControlTriadas(string token);

	bool determinarEliminado(uint32_t eliminado);
	virtual void cargarEstructura(string dato);
	void leerArchivo(fstream* archivo);

	map<uint32_t,DatoControlTriada*>* getDatosControl(fstream* archivo);

	virtual ~ParserArchivoControlTriadas();
};

#endif /* PARSERARCHIVOCONTROLTRIADAS_H_ */
