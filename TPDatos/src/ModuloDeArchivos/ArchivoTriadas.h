/*
 * ArchivoTriadas.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *	Contiene las triadas con la informacion que relaciona documentos,
 *	terminos y posiciones relativas.
 *
 */

#ifndef ARCHIVOTRIADAS_H_
#define ARCHIVOTRIADAS_H_

#include "../ModuloDeTipos/DatoTriada.h"
#include "../ModuloParser/ParserArchivoTriadas.h"

#include <fstream>
#include <iostream>
#include <list>
#include <stdint.h>

class ArchivoTriadas {
private:
	list<DatoTriada*>* triadas;
	ParserArchivoTriadas* parser;
	string pathArchivoTriadas;
	fstream archivoTriadas;
public:
	ArchivoTriadas(string path);

	list<DatoTriada*>* getTriadas();
	list<DatoTriada*>* getTriadas(uint32_t id);

	//TODO metodos que consulten cosas particulares de cada triada.

	virtual ~ArchivoTriadas();
};

#endif /* ARCHIVOTRIADAS_H_ */