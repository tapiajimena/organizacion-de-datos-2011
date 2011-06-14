/*
 * DatoControlTriada.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "DatoControlTriada.h"

DatoControlTriada::DatoControlTriada() {
	// TODO Auto-generated constructor stub

}

DatoControlTriada::DatoControlTriada(DatoControlTriada* d){
	this->eliminado = d->eliminado;
	this->idLibro = d->idLibro;
	this->idTriadaFinal = d->idTriadaFinal;
	this->idTriadaInicial = d->idTriadaInicial;
	Logger::log("datoControlTriada", "DatoControlTriada",
			"Se crea una copia del dato de control triada.");
}

string DatoControlTriada::serializar() {
	vector<string> datos;

	string datosControl[] = { ServiceClass::toString(this->idLibro),
			ServiceClass::toString(this->idTriadaInicial),
			ServiceClass::toString(this->idTriadaFinal),
			ServiceClass::toString(this->eliminado)};

	datos.clear();

	//Se inicializa un vector con los datos de control
	datos.insert(datos.begin(), datosControl, datosControl + 4);

	return ServiceClass::toStringData(&datos, CONTROL_TOKEN);
}

uint32_t DatoControlTriada::getIdLibro() const {
	return idLibro;
}

uint32_t DatoControlTriada::getIdTriadaFinal() const {
	return idTriadaFinal;
}

uint32_t DatoControlTriada::getIdTriadaInicial() const {
	return idTriadaInicial;
}

void DatoControlTriada::setEliminado(bool eliminado) {
	this->eliminado = eliminado;
}

void DatoControlTriada::setIdLibro(uint32_t idLibro) {
	this->idLibro = idLibro;
}

void DatoControlTriada::setIdTriadaFinal(uint32_t idTriadaFinal) {
	this->idTriadaFinal = idTriadaFinal;
}

void DatoControlTriada::setIdTriadaInicial(uint32_t idTriadaInicial) {
	this->idTriadaInicial = idTriadaInicial;
}

bool DatoControlTriada::estaBorrado() {
	return this->eliminado;
}

void DatoControlTriada::borrarLibro() {
	this->eliminado = true;
}

DatoControlTriada::~DatoControlTriada() {
	// TODO Auto-generated destructor stub
}
