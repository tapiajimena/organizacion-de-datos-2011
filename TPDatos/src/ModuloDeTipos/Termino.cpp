/*
 * Termino.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */


#include "Termino.h"

Termino::Termino() {
	// TODO Auto-generated constructor stub
}

Termino::Termino(string nombre, list<DatoTriada*>* triadasDelTermino) {
	this->nombre = nombre;
	this->posicionesTerminoEnLibros = new list<PosicionTerminoEnLibro*>();
	PosicionTerminoEnLibro* posicionTerminoEnLibro = NULL;

	list<DatoTriada*>::const_iterator ci_triada;
	for (ci_triada = triadasDelTermino->begin(); ci_triada != triadasDelTermino->end(); ++ci_triada) {
		posicionTerminoEnLibro = new PosicionTerminoEnLibro;
		posicionTerminoEnLibro->id_libro = (*ci_triada)->getIdLibro();
		posicionTerminoEnLibro->posicion = (*ci_triada)->getPosicion();
		this->posicionesTerminoEnLibros->push_back(posicionTerminoEnLibro);
	}
}

string Termino::obtenerNombre(){
	return this->nombre;
}

list<uint32_t>* Termino::obtenerLibros() {
	list<uint32_t>* libros = new list<uint32_t>();

	for (ci_posicionTerminoEnLibro = this->posicionesTerminoEnLibros->begin(); ci_posicionTerminoEnLibro
			!= this->posicionesTerminoEnLibros->end(); ++ci_posicionTerminoEnLibro) {
		libros->push_back((*ci_posicionTerminoEnLibro)->id_libro);
	}
	//ordeno para obtener los unicos
	libros->sort();
	libros->unique();

	return libros;
}

int Termino::obtenerCantidadLibros(){
	list<uint32_t>* libros = this->obtenerLibros() ;
	int resultado = libros->size();
	delete (libros);
	return resultado;
}

float Termino::obtenerPesoGlobal(int totalDocumentos){
	float pesoGlobal = 0.0;
	int frecuenciaGlobal = this->obtenerCantidadLibros();
	if(frecuenciaGlobal != 0)
	{
		pesoGlobal = log10( (float)(totalDocumentos / frecuenciaGlobal));
	}

	return pesoGlobal;
}

list<long>* Termino::obtenerPosicionesEnLibro(uint32_t id_libro) {
	list<long>* posiciones = new list<long>();

	for (ci_posicionTerminoEnLibro = this->posicionesTerminoEnLibros->begin(); ci_posicionTerminoEnLibro
			!= this->posicionesTerminoEnLibros->end(); ++ci_posicionTerminoEnLibro) {
		if ((*ci_posicionTerminoEnLibro)->id_libro == id_libro) {
			posiciones->push_back((*ci_posicionTerminoEnLibro)->posicion);
		}
	}
	return posiciones;
}

int Termino::obtenerCantidadAparicionesEnLibro(uint32_t id_libro){
	list<long>* aux = this->obtenerPosicionesEnLibro(id_libro);
	int resultado = aux->size();
	delete (aux);
	return resultado;
}

bool Termino::estaEnLibro(uint32_t id_libro) {
	bool esta = false;

	for (ci_posicionTerminoEnLibro = this->posicionesTerminoEnLibros->begin(); ci_posicionTerminoEnLibro
			!= this->posicionesTerminoEnLibros->end(); ++ci_posicionTerminoEnLibro) {
		if ((*ci_posicionTerminoEnLibro)->id_libro == id_libro) {
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

	list<long>* posicionesEnLibro = this->obtenerPosicionesEnLibro(id_libro);
	list<long>::const_iterator ci_posicionEnLibro;

	for (ci_posicionEnLibro = posicionesEnLibro->begin();
		ci_posicionEnLibro != posicionesEnLibro->end();
			++ci_posicionEnLibro) {

		posicionAnteriorMasProximaActual =
			terminoAnterior->obtenerPosicionAnteriorMasProxima(id_libro, *ci_posicionEnLibro);
		posicionPosteriorMasProximaActual =
			terminoPosterior->obtenerPosicionPosteriorMasProxima(id_libro, *ci_posicionEnLibro);

		if (posicionResultado == -1) {
			posicionesMasProximasTermino->posicionMasProximaTerminoAnterior
					= posicionAnteriorMasProximaActual;
			posicionesMasProximasTermino->posicionMasProximaTerminoPosterior
					= posicionPosteriorMasProximaActual;
			posicionResultado = *ci_posicionEnLibro;
		} else {
			if (((*ci_posicionEnLibro) - posicionAnteriorMasProximaActual + posicionPosteriorMasProximaActual - (*ci_posicionEnLibro))
				< (posicionResultado - posicionesMasProximasTermino->posicionMasProximaTerminoAnterior
					+ posicionesMasProximasTermino->posicionMasProximaTerminoPosterior - posicionResultado)) {

				posicionesMasProximasTermino->posicionMasProximaTerminoAnterior
						= posicionAnteriorMasProximaActual;
				posicionesMasProximasTermino->posicionMasProximaTerminoPosterior
						= posicionPosteriorMasProximaActual;
				posicionResultado = *ci_posicionEnLibro;
			}
		}
	}

	delete (posicionesEnLibro);

	return posicionesMasProximasTermino;

}

long Termino::obtenerPosicionAnteriorMasProxima(uint32_t id_libro,
		long posicion) {
	long posicionAnteriorMasProxima = -1;

	for (ci_posicionTerminoEnLibro = this->posicionesTerminoEnLibros->begin(); ci_posicionTerminoEnLibro
			!= this->posicionesTerminoEnLibros->end(); ++ci_posicionTerminoEnLibro) {
		if (((*ci_posicionTerminoEnLibro)->id_libro == id_libro) &&
			(((*ci_posicionTerminoEnLibro)->posicion < posicion) &&
				((*ci_posicionTerminoEnLibro)->posicion > posicionAnteriorMasProxima))) {
			posicionAnteriorMasProxima = (*ci_posicionTerminoEnLibro)->posicion;
		}
	}

	return posicionAnteriorMasProxima;
}

long Termino::obtenerPosicionPosteriorMasProxima(uint32_t id_libro,
		long posicion) {
	long posicionPosteriorMasProxima = -1;

	for (ci_posicionTerminoEnLibro = this->posicionesTerminoEnLibros->begin(); ci_posicionTerminoEnLibro
			!= this->posicionesTerminoEnLibros->end(); ++ci_posicionTerminoEnLibro) {
		if (((*ci_posicionTerminoEnLibro)->id_libro == id_libro) &&
			(((*ci_posicionTerminoEnLibro)->posicion > posicion) &&
				(((*ci_posicionTerminoEnLibro)->posicion < posicionPosteriorMasProxima) || (posicionPosteriorMasProxima == -1)))) {
			posicionPosteriorMasProxima = (*ci_posicionTerminoEnLibro)->posicion;
		}
	}

	return posicionPosteriorMasProxima;
}

Termino::~Termino() {

	for (ci_posicionTerminoEnLibro = posicionesTerminoEnLibros->begin();
		ci_posicionTerminoEnLibro != posicionesTerminoEnLibros->end();
			++ci_posicionTerminoEnLibro){
				delete (*ci_posicionTerminoEnLibro);
	}

	delete (posicionesTerminoEnLibros);
}
