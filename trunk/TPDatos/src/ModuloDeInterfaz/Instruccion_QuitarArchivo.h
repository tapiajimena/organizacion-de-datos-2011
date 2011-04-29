/*
 * Instruccion_QuitarArchivo.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Se encarga de encapsular la logica con la que se elimina
 *  el archivo pasado por parametro.
 *	Tambien de los indices en los cuales se encuentra.
 *	Comando:
 *	./ejecutable -q ID_Archivo
 *
 */

#ifndef INSTRUCCION_QUITARARCHIVO_H_
#define INSTRUCCION_QUITARARCHIVO_H_

#include "Instruccion.h"
#include "../ModuloEstructuras/Configuracion.h"

class Instruccion_QuitarArchivo: public Instruccion {
private:
	uint32_t idArchivo;
public:
	Instruccion_QuitarArchivo(char id, uint32_t idArchivo);

	virtual void ejecutar();

	virtual ~Instruccion_QuitarArchivo();
};

#endif /* INSTRUCCION_QUITARARCHIVO_H_ */
