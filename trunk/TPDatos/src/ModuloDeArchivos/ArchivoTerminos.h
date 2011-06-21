/*
 * ArchivoTerminos.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#ifndef ARCHIVOTERMINOS_H_
#define ARCHIVOTERMINOS_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "ManejadorArchivo.h"
#include "../../Common/Constantes.h"

using namespace std;

class ArchivoTerminos {
private:
	fstream archivoTerminos;

public:
	ArchivoTerminos(std::string nombreArchivo);
	virtual ~ArchivoTerminos();

	//Ingresa el término al final del archivo y escribe un separador de términos al final del archivo.
	//Devuelve el ID del término (palabra) ingresado, que es el offset por el cual se accede al archivo.
	uint32_t ingresarTermino(std::string palabra);

	//El ID es el offset en el archivo del primer caracter del término en disco. Ingresa al archivo con
	//ese offset y devuelve la cadena de caracteres desde esa posición hasta el primer FIN_DE_TERMINO (constante)
	string obtenerTermino(uint32_t idTermino);


	vector<pair<string, uint32_t> > obtenerTerminos();

};

#endif /* ARCHIVOTERMINOS_H_ */
