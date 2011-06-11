/*
 * ParserArchivoControl.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *  Parser de archivos del tipo texto que representen la estructura
 *  de control del archivo de control.
 *
 */

#ifndef PARSERARCHIVOCONTROL_H_
#define PARSERARCHIVOCONTROL_H_

#include <fstream>
#include <map>
#include <list>
#include <iostream>
#include <stdint.h>

#include "../../Common/Constantes.h"
#include "../Common/Utilitarios/Logger.h"
#include "../ModuloParser/ParserAuxiliar.h"
#include "../ModuloDeTipos/DatoControlLibro.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"

using namespace std;
using namespace ManejadorArchivo;

class ParserArchivoControl : ParserAuxiliar{
private:
	map<uint32_t,DatoControlLibro*>::iterator it;
	map<uint32_t,DatoControlLibro*>* libros;
	DatoControlLibro* datoNuevo;
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
    void setTipoIndice(vector<string> datos);
    int getOffsetArchivo();

	virtual ~ParserArchivoControl();
};

#endif /* PARSERARCHIVOCONTROL_H_ */
