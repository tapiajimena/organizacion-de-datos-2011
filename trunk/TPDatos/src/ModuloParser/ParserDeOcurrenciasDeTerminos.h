/*
 * ParserDeOcurrencias.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#ifndef PARSERDEOCURRENCIASDETERMINOS_H_
#define PARSERDEOCURRENCIASDETERMINOS_H_

#include "ParserDeAtributo.h"
#include "../Common/Utilitarios/ServiceClass.h"
#include "../ModuloEstructuras/Diccionario.h"

class ParserDeOcurrenciasDeTerminos : public ParserDeAtributo {

private:
	//Procesa la línea de caracteres y carga los datos obtenidos en la estructura del libro
	void procesarLineaLibro(std::string linea, Libro* libro);

	Diccionario* diccionarioStopWords;

public:
	ParserDeOcurrenciasDeTerminos(std::string nombreArchivoStopWords);
	virtual ~ParserDeOcurrenciasDeTerminos();

	Libro* parsear(DatoLibro* datoLibro);
};

#endif /* PARSERDEOCURRENCIASDETERMINOS_H_ */
