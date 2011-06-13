/*
 * ArchivoTerminos.h
 *
 *  Created on: 12/06/2011
 *      Author: santi
 */

#ifndef ARCHIVOTERMINOS_H_
#define ARCHIVOTERMINOS_H_

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "ManejadorArchivo.h"
#include "../../Common/Constantes.h"

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
	std::string obtenerTermino(uint32_t id);

};

#endif /* ARCHIVOTERMINOS_H_ */
