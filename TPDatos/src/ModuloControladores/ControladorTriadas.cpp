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

void ControladorTriadas::insertarDatosControlTriadas(
		DatoControlTriada* datoControlTriada) {
	this->arcControl->agregarDatoControl(datoControlTriada);
}

uint32_t ControladorTriadas::getSiguienteIdTriada() {
	this->offsetAEscribir += (sizeof(offsetAEscribir) * 3);
	return this->offsetAEscribir;
}

uint32_t ControladorTriadas::dondeEscribo(int cantidadTriadas) {
	uint32_t sizeArchivo = getSizeArchivoTriadas();
	if (sizeArchivo != 0) {
		this->offsetAEscribir = this->arcControl->buscarOffsetDondeEscribir(
				cantidadTriadas, sizeArchivo);
	} else
		return 0;

	return this->offsetAEscribir;
}

void ControladorTriadas::insertarTriadaAlFinal(DatoTriada* datoTriada) {
	this->arcTriadas->escribirAlFinal(datoTriada);

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
	triadas->clear();
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

list<uint32_t>* ControladorTriadas::getLibrosAlmacenados() {
	return this->arcControl->getIdLibrosAlmacenados();
}

bool ControladorTriadas::eliminarLibro(uint32_t offset) {
	/* Actualiza el estado del archivo de control */
	if(getSizeArchivoTriadas() > 0)
	{
		arcControl->eliminarLibro(offset);
		arcControl->actualizarArchivo();

		Logger::log("ControladorTriadas", "eliminarLibro",
				"Se actualiza el archivo de control.");
	}
	else
		Logger::log("ControladorTriadas", "eliminarLibro",
						"El archivo control esta vacio");

}

void ControladorTriadas::eliminarRegistro(uint32_t idLibro) {
	this->arcControl->eliminarDatoControl(idLibro);
}

void ControladorTriadas::setDatoControlEliminado(bool e) {
	return this->arcControl->setDatoEliminado(e);
}

bool ControladorTriadas::getDatoControlEliminado() {
	return this->arcControl->getDatoEliminado();
}

void ControladorTriadas::actualizarArchivoDeControl() {
	arcControl->actualizarArchivo();
}

uint32_t ControladorTriadas::getSizeArchivoTriadas() {
	return this->arcTriadas->devolverTamanio();
}

ControladorTriadas::~ControladorTriadas() {
	Logger::log("ControladorTriadas", "~ControladorTriadas",
			"Se cierra el archivo de control.");

	delete (arcControl);
	delete (arcTriadas);
}
