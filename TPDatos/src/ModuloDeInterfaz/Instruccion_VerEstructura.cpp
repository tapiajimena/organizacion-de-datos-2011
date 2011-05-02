/*
 * Instruccion_VerEstructura.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_VerEstructura.h"

Instruccion_VerEstructura::Instruccion_VerEstructura(char id,
		char tipoEstructura, string nombreArchivo) :
	Instruccion(id) {
	this->tipoEstructura = tipoEstructura;
	this->nombreArchivo = nombreArchivo;
}

void Instruccion_VerEstructura::crearArchivos() {
	if ((this->tipoEstructura == INDICE_AUTOR || this->tipoEstructura
			== INDICE_EDITORIAL)) {
		string archivoEstructura = this->nombreArchivo + ARCHIVO_INDICE_SUFIX;
	} else {
		string archivoEstructura = this->nombreArchivo + ARCHIVO_TABLA_SUFIX;
	}
	Crear(archivoEstructura, this->archivoEstructuras, true);

	string archivoEspaciosLibres = this->nombreArchivo
			+ ARCHIVO_ESPACIOSLIBRES_SUFIX;
	Crear(archivoEspaciosLibres, this->archivoEspaciosLibres, true);

	string archivoBloques = this->nombreArchivo + ARCHIVO_BLOQUES_SUFIX;
	Crear(archivoBloques, this->archivoBloques, true);
}

void Instruccion_VerEstructura::ejecutar() {
	Configuracion* conf = Configuracion::GetInstancia();

	Indexador* indexador = new Indexador();

	//genero el indice correspondiente
	indexador->indexar(ServiceClass::toUppercase(this->tipoEstructura));

	//armo los archivos.
	crearArchivos();

	//cargar archivos


	Logger::log("Instruccion_VerEstructura", "ejecutar",
			"Se muestra la estructura.");
}

Instruccion_VerEstructura::~Instruccion_VerEstructura() {
	// TODO Auto-generated destructor stub
}
