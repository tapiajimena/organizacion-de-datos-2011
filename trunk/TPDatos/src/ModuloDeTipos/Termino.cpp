/*
 * Termino.cpp
 *
 *  Created on: 12/06/2011
 *      Author: paulo
 */

#include "Termino.h"

Termino::Termino() {
	// TODO Auto-generated constructor stub
}

Termino::Termino(string termino, list<DatoTriada> triadasDelTermino) {
	this->termino = termino;

	list<DatoTriada>::const_iterator triada;
	for (triada = triadasDelTermino.begin(); triada != triadasDelTermino.end(); ++triada) {
		this->listaDeOcurrencias.push_back(
				make_pair((*triada).getIdLibro(), (*triada).getPosicion()));
	}
}

list<uint32_t> Termino::obtenerLibros() {
	list<uint32_t> libros;

	ListaDeOcurrencias::const_iterator ocurrencia;
	for (ocurrencia = this->listaDeOcurrencias.begin(); ocurrencia
			!= this->listaDeOcurrencias.end(); ++ocurrencia) {

		libros.push_back((*ocurrencia).first);

	}
	//ordeno para obtener los unicos
	libros.sort();
	libros.unique();

	return libros;
}

list<long> Termino::obtenerPosiciones(uint32_t id_libro) {
	list<long> posiciones;

	ListaDeOcurrencias::const_iterator ocurrencia;
	for (ocurrencia = this->listaDeOcurrencias.begin(); ocurrencia
			!= this->listaDeOcurrencias.end(); ++ocurrencia) {
		if ((*ocurrencia).first == id_libro) {
			posiciones.push_back((*ocurrencia).second);
		}

	}
	return posiciones;

}

bool Termino::estaEnLibro(uint32_t id_libro) {
	bool esta = false;

	ListaDeOcurrencias::const_iterator ocurrencia;
	for (ocurrencia = this->listaDeOcurrencias.begin(); ocurrencia
			!= this->listaDeOcurrencias.end(); ++ocurrencia) {
		if ((*ocurrencia).first == id_libro) {
			esta = true;
		}

	}
	return esta;
}

PosicionesMasProximasTermino* Termino::obtenerMejoresPosiciones(uint32_t id_libro,
		Termino* terminoAnterior, Termino* terminoPosterior) {

	PosicionesMasProximasTermino* posicionesMasProximasTermino =
			new PosicionesMasProximasTermino;
	posicionesMasProximasTermino->posicionMasProximaTerminoAnterior = -1;
	posicionesMasProximasTermino->posicionMasProximaTerminoPosterior = -1;

	long posicionResultado = -1;

	long posicionAnteriorMasProximaActual = 0;
	long posicionPosteriorMasProximaActual = 0;

	list<long> posicionesEnLibro = this->obtenerPosiciones(id_libro);
	list<long>::const_iterator posicionEnLibro;

	for (posicionEnLibro = posicionesEnLibro.begin(); posicionEnLibro
			!= posicionesEnLibro.end(); ++posicionEnLibro) {
		posicionAnteriorMasProximaActual
				= terminoAnterior->obtenerPosicionAnteriorMasProxima(id_libro,
						*posicionEnLibro);
		posicionPosteriorMasProximaActual
				= terminoPosterior->obtenerPosicionPosteriorMasProxima(
						id_libro, *posicionEnLibro);

		if (posicionResultado == -1) {
			posicionesMasProximasTermino->posicionMasProximaTerminoAnterior
					= posicionAnteriorMasProximaActual;
			posicionesMasProximasTermino->posicionMasProximaTerminoPosterior
					= posicionPosteriorMasProximaActual;
			posicionResultado = *posicionEnLibro;
		} else {
			if (((*posicionEnLibro) - posicionAnteriorMasProximaActual
					+ posicionPosteriorMasProximaActual - (*posicionEnLibro))
					< (posicionResultado
							- posicionesMasProximasTermino->posicionMasProximaTerminoAnterior
							+ posicionesMasProximasTermino->posicionMasProximaTerminoPosterior
							- posicionResultado)) {
				posicionesMasProximasTermino->posicionMasProximaTerminoAnterior
						= posicionAnteriorMasProximaActual;
				posicionesMasProximasTermino->posicionMasProximaTerminoPosterior
						= posicionPosteriorMasProximaActual;
				posicionResultado = *posicionEnLibro;
			}
		}
	}

	return posicionesMasProximasTermino;

}

long Termino::obtenerPosicionAnteriorMasProxima(uint32_t id_libro,
		long posicion) {
	long posicionAnteriorMasProxima = -1;

	ListaDeOcurrencias::const_iterator ocurrencia;
	for (ocurrencia = this->listaDeOcurrencias.begin(); ocurrencia
			!= this->listaDeOcurrencias.end(); ++ocurrencia) {
		if (((*ocurrencia).first == id_libro) && ((*ocurrencia).second
				< posicion) && ((*ocurrencia).second
				> posicionAnteriorMasProxima)) {
			posicionAnteriorMasProxima = (*ocurrencia).second;
		}

	}

	return posicionAnteriorMasProxima;
}

long Termino::obtenerPosicionPosteriorMasProxima(uint32_t id_libro,
		long posicion) {
	long posicionPosteriorMasProxima = -1;

	ListaDeOcurrencias::const_iterator ocurrencia;
	for (ocurrencia = this->listaDeOcurrencias.begin(); ocurrencia
			!= this->listaDeOcurrencias.end(); ++ocurrencia) {

		if (((*ocurrencia).first == id_libro) && ((*ocurrencia).second
				> posicion) && ((((*ocurrencia).second
				< posicionPosteriorMasProxima)) || (posicionPosteriorMasProxima
				== -1))) {
			posicionPosteriorMasProxima = (*ocurrencia).second;
		}

	}

	return posicionPosteriorMasProxima;
}

Termino::~Termino() {
	// TODO Auto-generated destructor stub
}
