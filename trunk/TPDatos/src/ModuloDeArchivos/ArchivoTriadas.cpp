/*
 * ArchivoTriadas.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 */

#include "ArchivoTriadas.h"

ArchivoTriadas::ArchivoTriadas() {
	// TODO Auto-generated constructor stub

}

list<DatoTriada*>* ArchivoTriadas::getTriadas(){
	return this->parser->getTriadas(&archivoTriadas);
}

list<DatoTriada*>* ArchivoTriadas::getTriadas(uint32_t id){
	return this->parser->getTriadas(&archivoTriadas,id);
}


ArchivoTriadas::~ArchivoTriadas() {
	// TODO Auto-generated destructor stub
}
