/*
 * ParserArchivoControl.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *  Parseador de archivos del tipo texto. Que representen la estructura
 *  de control del archivo de control.
 *
 */

#ifndef PARSERARCHIVOCONTROL_H_
#define PARSERARCHIVOCONTROL_H_

#include <fstream>
#include <map>
#include <iostream>
#include <stdint.h>

#include "../../Common/Constantes.h"
#include "../Common/Utilitarios/Logger.h"
#include "../ModuloParser/ParserAuxiliar.h"
#include "../ModuloDeTipos/DatoControlLibro.h"

using namespace std;

class ParserArchivoControl : ParserAuxiliar{
private:
	map<uint32_t,DatoControlLibro*>::iterator it;
	map<uint32_t,DatoControlLibro*>* libros;
	int contadorLinea;
public:
	ParserArchivoControl(string token);

	virtual void leerArchivo(fstream* archivo);
	virtual void cargarEstructura(string dato);

	map<uint32_t,DatoControlLibro*>* getLibros(fstream* archivo);

	/*Getters y Setters */
    string getEspacioLibre() const;
    string getId() const;
    list<char>* getTipoIndice(vector<string> datos) const;

	virtual ~ParserArchivoControl();
};

#endif /* PARSERARCHIVOCONTROL_H_ */
