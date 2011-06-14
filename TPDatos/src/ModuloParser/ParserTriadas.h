/*
 * ParserTriadas.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#ifndef PARSERTRIADAS_H_
#define PARSERTRIADAS_H_

#include "ParserAuxiliar.h"
#include "../ModuloDeTipos/Dato.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"
#include "../Common/Utilitarios/Logger.h"
#include "../Common/Utilitarios/ServiceClass.h"
#include "../../Common/Constantes.h"

#include <list>
#include <map>
#include <stdint.h>

using namespace ManejadorArchivo;

class ParserTriadas: public ParserAuxiliar {
protected:
	list<Dato*>::iterator it;
	list<Dato*>* triadas;
	int contadorLinea;
public:
	ParserTriadas(string token);

	virtual void leerArchivo(fstream* archivo);
	void leerArchivo(fstream* archivo, uint32_t offset);
	virtual void cargarEstructura(string dato);

	/*Getters y Setters */
	list<Dato*>* getTriadas(fstream* archivo);
	list<Dato*>* getTriadas(fstream* archivo, uint32_t offset);

	virtual ~ParserTriadas();
};

#endif /* PARSERTRIADAS_H_ */
