#include "Termino.h"

Termino::Termino() {

}

Termino::Termino(string nombre, list<DatoTriada*>* triadasDelTermino) {
	this->nombre = nombre;
	if (triadasDelTermino->size() > 0){
		this->id_termino = triadasDelTermino->front()->getIdTermino();
	}
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

uint32_t Termino::obtenerId(){
	return this->id_termino;
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

	PosicionesMasProximasTermino* posicionesMasProximasTerminoActuales =
			new PosicionesMasProximasTermino;

	list<long>* posicionesEnLibro = this->obtenerPosicionesEnLibro(id_libro);
	list<long>::const_iterator ci_posicionEnLibro;

	bool primer = true;
	for (ci_posicionEnLibro = posicionesEnLibro->begin();
		ci_posicionEnLibro != posicionesEnLibro->end();
			++ci_posicionEnLibro) {
			
		posicionesMasProximasTerminoActuales->posicionMasProximaTerminoAnterior =
			terminoAnterior->obtenerPosicionAnteriorMasProxima(id_libro, *ci_posicionEnLibro);
		posicionesMasProximasTerminoActuales->posicionMasProximaTerminoPosterior =
			terminoPosterior->obtenerPosicionPosteriorMasProxima(id_libro, *ci_posicionEnLibro);
		posicionesMasProximasTerminoActuales->posicionActualTermino = *ci_posicionEnLibro;

		if ((primer) || (*posicionesMasProximasTerminoActuales < *posicionesMasProximasTermino)) {
			
			*posicionesMasProximasTermino = *posicionesMasProximasTerminoActuales;
		}
		
		primer = false;
	}
	
	delete (posicionesEnLibro);
	delete (posicionesMasProximasTerminoActuales);

	return posicionesMasProximasTermino;

}

long Termino::obtenerPosicionAnteriorMasProxima(uint32_t id_libro,
		long posicion) {
	long posicionAnteriorMasProxima = -1;

	for (ci_posicionTerminoEnLibro = this->posicionesTerminoEnLibros->begin(); ci_posicionTerminoEnLibro
			!= this->posicionesTerminoEnLibros->end(); ++ci_posicionTerminoEnLibro) {
		if (((*ci_posicionTerminoEnLibro)->id_libro == id_libro) &&
			(((*ci_posicionTerminoEnLibro)->posicion <= posicion) &&
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
			(((*ci_posicionTerminoEnLibro)->posicion >= posicion) &&
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

