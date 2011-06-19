/*
 * Termino.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#ifndef TERMINO_H_
#define TERMINO_H_

#include <list>
#include <string>
#include <stdint.h>
#include <math.h>
#include "MockDatoTriada.h"

using namespace std;

typedef struct {
	uint32_t id_libro;
	long posicion;
} PosicionTerminoEnLibro;

typedef struct {
	long posicionMasProximaTerminoAnterior;
	long posicionMasProximaTerminoPosterior;
} PosicionesMasProximasTermino;


class Termino {
private:
	string nombre;
	uint32_t id_termino;
	list<PosicionTerminoEnLibro*>* posicionesTerminoEnLibros;
	list<PosicionTerminoEnLibro*>::const_iterator ci_posicionTerminoEnLibro;

public:
	Termino();

	Termino(string nombre, list<DatoTriada*>* triadasDelTermino);

	uint32_t obtenerId();

	string obtenerNombre();

	list<uint32_t>* obtenerLibros();

	int obtenerCantidadLibros();

	int obtenerCantidadAparicionesEnLibro(uint32_t id_libro);

	float obtenerPesoGlobal(int totalDocumentos);

	list<long>* obtenerPosicionesEnLibro(uint32_t id_libro);

	bool estaEnLibro(uint32_t id_libro);

	/*
	 * dado un libro y los terminos que anteceden y preceden al termino actual en la cosulta
	 * restorna las posición del termino que antecede junto con la posición del término que
	 * precede de modo tal que las distancia entre los tres sea mínima
	 *
	 * en caso de retornar -1, -1 es que los términos no estaban en orden en el libro
	 */
	PosicionesMasProximasTermino* obtenerMejoresPosiciones(uint32_t id_libro, Termino* terminoAnterior, Termino* terminoSiguiente);

	//devuelve -1 en caso de no haberla podido encontrar
	long obtenerPosicionAnteriorMasProxima(uint32_t id_libro, long posicion);

	//devuelve -1 en caso de no haberla podido encontrar
	long obtenerPosicionPosteriorMasProxima(uint32_t id_libro, long posicion);

	virtual ~Termino();
};

#endif /* TERMINO_H_ */
