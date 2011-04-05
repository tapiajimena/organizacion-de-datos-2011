/*
 * ArchivoVariable.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      Lee, escribe, maneja y controla los registros variables en archivos.
 *      
 */

#ifndef ARCHIVOVARIABLE_H_
#define ARCHIVOVARIABLE_H_

#include <fstream>
#include"../ModuloDeTipos/RegistroVariable.h"

class ArchivoVariable {

private:
	fstream archivoVariable;
	string path;

public:
	ArchivoVariable();

	/**
	 * Abre de forma binaria el archivo de ruta pathArchivo, si no existe lo crea si existe lo borra e inicializa el path.
	 * pathArchivo: direccion + nombre de archivo + extension
	 */
	ArchivoVariable(string pathArchivo);


	/**
	 * Abre de forma binaria el archivo de path pathArchivo
	 */
	void abrir();

	RegistroVariable* leer();
	void escribir(RegistroVariable & rv, uint32_t offset);

	virtual ~ArchivoVariable();
};





#endif /* ARCHIVOVARIABLE_H_ */
