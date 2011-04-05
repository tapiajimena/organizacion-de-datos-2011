/*
 * RegistroVariable.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#define LONGITUD_CANT_DATOS 32

#include "RegistroVariable.h"

RegistroVariable::RegistroVariable(const Datos& dato) :Registro(dato) {
	this->dato = dato;
	this->eliminado = false;
}

RegistroVariable::~RegistroVariable() {
}

void RegistroVariable::eliminar() {
	this->eliminado = true;
}

Datos RegistroVariable::serializarse() {

	string serializacion;
	stringstream streamTamanio;

	uint32_t tamanio = dato.getSize();
	streamTamanio << tamanio;

	unsigned int tamanioDatos = streamTamanio.str().size();

	//Tamaño
	while (tamanioDatos < LONGITUD_CANT_DATOS) {
		serializacion += "0";
		tamanioDatos++;
	}
	serializacion += streamTamanio.str();

	 cout << "2)))):" << endl;
	 cout << serializacion << endl;

	//DATO
	serializacion += dato.toString();
	cout << "3)))):" << endl;
	cout << serializacion << endl;

	return Datos(serializacion);
	return NULL;
}

void RegistroVariable::hidratarse(const Datos& cadena) {

	/*
	if (cadena.getSize() <= 1)
		return;

	/*
	 this->numeroRegistro = atoi(cadena.getSubBytes(0,LONGITUD_CANT_DATOS).toString().c_str());
	 int tamanioRegistro = atoi(cadena.getSubBytes(LONGITUD_CANT_DATOS, 2 * LONGITUD_CANT_DATOS).toString().c_str());
	 this->setDato(cadena.getSubBytes(2 * LONGITUD_CANT_DATOS,tamanioRegistro));
	 */
	//this->tamanioDato = tamanioRegistro;


}

void RegistroVariable::setDato(const Datos& dato) {
	this->dato = dato;
}

Datos RegistroVariable::getDato() {
	return this->dato;
}


uint32_t RegistroVariable::getTamanioSerializado() {
	return 2 * LONGITUD_CANT_DATOS + this->dato.getSize();

}
