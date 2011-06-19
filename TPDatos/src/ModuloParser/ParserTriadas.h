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
#include "../ModuloDeTipos/DatoTriada.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"
#include "../Common/Utilitarios/Logger.h"
#include "../Common/Utilitarios/ServiceClass.h"
#include "../../Common/Constantes.h"

#include <list>
#include <stdint.h>

using namespace ManejadorArchivo;

class ParserTriadas {
protected:
	list<Dato*>::iterator it;
	list<Dato*>* triadas;
	DatoTriada* triada;
	string separador;
	int contadorLinea;
public:
	ParserTriadas(string token);

	/*Getters y Setters */
	list<Dato*>* getTriadas(fstream* archivo);
	list<Dato*>* getTriadas(fstream* archivo, uint32_t offset);

	virtual ~ParserTriadas();
};

#endif /* PARSERTRIADAS_H_ */
