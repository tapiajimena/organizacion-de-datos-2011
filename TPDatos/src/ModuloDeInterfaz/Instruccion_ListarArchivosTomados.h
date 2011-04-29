/*
 * Instruccion_ListarArchivosTomados.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 * Encapsula la logica pertinente a mostrar identificador, Título, Autor,
 * Editorial y cantidad de palabras registradas para el libro pasado por
 * parametro.
 * Comando:
 * ./ejecutable -l
 */

#ifndef INSTRUCCION_LISTARARCHIVOSTOMADOS_H_
#define INSTRUCCION_LISTARARCHIVOSTOMADOS_H_

#include "../ModuloEstructuras/Configuracion.h"
#include "Instruccion.h"

class Instruccion_ListarArchivosTomados: public Instruccion {
public:
	Instruccion_ListarArchivosTomados(char id);

	void getLibro(uint32_t idLibro);
	virtual void ejecutar();

	virtual ~Instruccion_ListarArchivosTomados();
};

#endif /* INSTRUCCION_LISTARARCHIVOSTOMADOS_H_ */
