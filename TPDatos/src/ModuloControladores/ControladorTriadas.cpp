/*
 * ControladorTriadas.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ControladorTriadas.h"

ControladorTriadas::ControladorTriadas() {

}

ControladorTriadas::ControladorTriadas(string pathArchivoTriadas,
		string pathControlTriadas) {

	this->arcTriadas = new ArchivoTriadas(pathArchivoTriadas);
	this->arcControl = new ArchivoControlTriadas(pathControlTriadas);
	this->triadas = new list<DatoTriada*> ;
	this->offsetAEscribir = 0;

	Logger::log("ControladorTriadas", "ControladorTriadas",
			"Se cargan los libros.");
}

void ControladorTriadas::insertarTriada(DatoTriada* triada, uint32_t offset) {
	this->arcTriadas->insertarNuevaTriada(triada, offset);
}

uint32_t ControladorTriadas::getSiguienteIdTriada() {
	uint32_t siguiente = this->offsetAEscribir + (sizeof(this->offsetAEscribir)*3);
	this->offsetAEscribir += siguiente;
	return siguiente;
}

uint32_t ControladorTriadas::dondeEscribo(int cantidadTriadas) {
	if(getSizeArchivoTriadas() != 0) {
		this->offsetAEscribir = this->arcControl->buscarOffsetDondeEscribir(cantidadTriadas);
	}

	return this->offsetAEscribir;
}

void ControladorTriadas::insertarTriadaAlFinal(DatoTriada* datoTriada) {
	this->arcTriadas->escribirAlFinal(datoTriada);

	//TODO se inserto una nueva triada en el
	//arcTriadas => deberia actualizarse arcControl
	this->arcControl->actualizarArchivo();

	Logger::log("ControladorTriadas", "insertarTriadaAlFinal",
			"Se inserto triada al final.");
}

DatoTriada* ControladorTriadas::getTriada(uint32_t offsetTriada) {
	return this->arcTriadas->obtenerTriada(offsetTriada);
}

list<DatoTriada*>* ControladorTriadas::getTriadas(list<uint32_t> idTriadas) {
	DatoTriada* ptrTriada, triada;
	list<uint32_t>::iterator it;
	for (it = idTriadas.begin(); it != idTriadas.end(); it++) {
		ptrTriada = this->getTriada(*it);

		if (ptrTriada != NULL)
			triadas->push_back(ptrTriada);
	}
	return triadas;
}

list<DatoTriada*>* ControladorTriadas::getTriadas(uint32_t id_Libro) {
	return this->getTriadas(*(this->arcControl->getTriadas(id_Libro)));
}

bool ControladorTriadas::eliminarLibro(uint32_t offset) {
	/* Actualiza el estado del archivo de control */
	arcControl->eliminarLibro(offset);

	arcControl->actualizarArchivo();

	Logger::log("ControladorTriadas", "eliminarLibro",
			"Se actualiza el archivo de control.");
}

void ControladorTriadas::actualizarArchivoDeControl() {
	arcControl->actualizarArchivo();
}

uint32_t ControladorTriadas::getSizeArchivoTriadas() {
	return this->arcTriadas->devolverTamanio();
}

ControladorTriadas::~ControladorTriadas() {
	delete (arcTriadas);
	delete (arcControl);
}
