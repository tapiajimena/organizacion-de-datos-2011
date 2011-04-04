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

#include "RegistroVariable.h"
#include <stdio.h>
#include <stdlib.h>

RegistroVariable::RegistroVariable(const Datos& dato): Registro(dato) {
	this->dato = dato;
	this->eliminado = false;
}

RegistroVariable::~RegistroVariable() {
}

void RegistroVariable::setDato(const Datos& dato) {
	this->dato = dato;
}

Datos RegistroVariable::getDato() const {
	return this->dato;
}

void RegistroVariable::eliminar() {
	this->eliminado = true;
}

Datos RegistroVariable::serializarse() {
	/*
	string serializacion;
	stringstream streamTamanio;
	stringstream streamUID;

	uint32_t tamanio = dato.getTamanio();
	streamTamanio << tamanio;
	streamUID << nRegistro;

	unsigned int tamanioDatos = streamTamanio.str().size();
	unsigned int tamanioUID = streamUID.str().size();

	//UID
	while (tamanioUID < LONGITUD_CANT_BYTES)
	{
		serializacion += "0";
		tamanioUID++;
	}
	serializacion += streamUID.str();
/*
	cout << "1)))):" << endl;
	cout << serializacion << endl;
*/
/*
	//Tamaño
	while (tamanioDatos < LONGITUD_CANT_BYTES)
	{
		serializacion += "0";
		tamanioDatos++;
	}
	serializacion += streamTamanio.str();
/*
	cout << "2)))):" << endl;
	cout << serializacion << endl;
*/
	//DATO
	//serializacion += dato.toString();
/*
	cout << "3)))):" << endl;
	cout << serializacion << endl;
*/
	//return Datos(serializacion);
	return NULL;
}

void RegistroVariable::hidratarse(const Datos& cadena) {
	/*
	if (cadena.getTamanio() <= 1)
		return;

	this->numeroRegistro = atoi(cadena.getSubBytes(0,LONGITUD_CANT_BYTES).toString().c_str());
	int tamanioRegistro = atoi(cadena.getSubBytes(LONGITUD_CANT_BYTES, 2 * LONGITUD_CANT_BYTES).toString().c_str());
	this->setDato(cadena.getSubBytes(2 * LONGITUD_CANT_BYTES,tamanioRegistro));
	//this->tamanioDato = tamanioRegistro;
	 *
	 */
}

uint32_t RegistroVariable::getTamanioSerializado() {
	//return 2 * LONGITUD_CANT_BYTES + this->dato.getTamanio();
	return 0;
}
