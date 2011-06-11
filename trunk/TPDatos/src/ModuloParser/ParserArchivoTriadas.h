/*
 * ParserArchivoTriadas.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *  Parser de archivos del tipo texto que representen la estructura
 *  de las triadas de control de datos que relacionan terminos con
 *  documentos.
 *
 */

#ifndef PARSERARCHIVOTRIADAS_H_
#define PARSERARCHIVOTRIADAS_H_

#include "../../Common/Constantes.h"
#include "../ModuloDeTipos/DatoTriada.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"
#include "../Common/Utilitarios/Logger.h"
#include "../Common/Utilitarios/ServiceClass.h"
#include "../ModuloParser/ParserAuxiliar.h"
#include "../ModuloDeTipos/DatoControlTriada.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"

#include <list>
#include <stdint.h>

using namespace ManejadorArchivo;

class ParserArchivoTriadas: public ParserAuxiliar {
private:
	list<DatoTriada*>::iterator it;
	list<DatoTriada*>* triadas;
	DatoTriada* datoNuevo;
	int contadorLinea;
public:
	ParserArchivoTriadas(string token);

	virtual void leerArchivo(fstream* archivo);
	void leerArchivo(fstream* archivo, uint32_t offset);
	virtual void cargarEstructura(string dato);

	/*Getters y Setters */
	list<DatoTriada*>* getTriadas(fstream* archivo);
	list<DatoTriada*>* getTriadas(fstream* archivo, uint32_t offset);

	virtual ~ParserArchivoTriadas();
};

#endif /* PARSERARCHIVOTRIADAS_H_ */
