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

#include <list>
#include "../ModuloDeTipos/DatoTriada.h"
#include "../ModuloDeTipos/DatoControlTriada.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"

using namespace ManejadorArchivo;

class ParserArchivoTriadas {
private:
	DatoTriada* triada;
	string separador;
	list<DatoTriada*>* triadas;
public:
	ParserArchivoTriadas(string token);

	void cargarEstructura(uint32_t idLibro, uint32_t idTermino, long posicionRelativa);

	void leerArchivo(fstream* archivo, uint32_t offset);


	/*Getters y Setters */
	list<DatoTriada*>* getTriadas(fstream* archivo);
	list<DatoTriada*>* getTriadas(fstream* archivo, uint32_t offset);
	DatoTriada* getTriada(fstream* archivo, uint32_t offset);

	virtual ~ParserArchivoTriadas();
};

#endif /* PARSERARCHIVOTRIADAS_H_ */
