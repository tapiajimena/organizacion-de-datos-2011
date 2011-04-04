/*
 * RegistroFij.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "RegistroFijo.h"

RegistroFijo::RegistroFijo(const Datos &dato):Registro(dato) {

	this->dato = dato;
}

Datos RegistroFijo::serializarse() {

	string datos;
/*
	char vivo = this->estaVivo();

	datos += this->dato.toString();
*/
	return NULL;
}

void RegistroFijo::hidratarse(const Datos& componente) {

	/*
	if (componente.getTamanio() <= 1) {
		return;
	}

	char vivo = componente.toString()[0];
	this->vivo = vivo;

	this->setDato(componente.getSubBytes(1,componente.getTamanio() - 1));
	*/
}

uint32_t RegistroFijo::getTamanioSerializado() {
	//return 1 + this->dato.getTamanio();
	return 1;
}


RegistroFijo::~RegistroFijo() {
	// TODO Auto-generated destructor stub
}
