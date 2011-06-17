/*
 * Termino.h
 *
 *  Created on: 12/06/2011
 *      Author: paulo
 */

#ifndef TERMINO_H_
#define TERMINO_H_

#include <list>
#include <string>
#include <stdint.h>
#include "DatoTriada.h"

using namespace std;

//<id_libro, posicionEnElLibro>
typedef list<pair<uint32_t,long> > ListaDeOcurrencias;

typedef struct {
	long posicionMasProximaTerminoAnterior;
	long posicionMasProximaTerminoPosterior;
} PosicionesMasProximasTermino;


class Termino {
private:
	string termino;
	uint32_t id_termino;
	ListaDeOcurrencias listaDeOcurrencias;
	float pesoGlobal;

public:
	Termino();

	Termino(string termino, list<DatoTriada> triadasDelTermino);

	list<uint32_t> obtenerLibros();

	list<long> obtenerPosiciones(uint32_t id_libro);

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
