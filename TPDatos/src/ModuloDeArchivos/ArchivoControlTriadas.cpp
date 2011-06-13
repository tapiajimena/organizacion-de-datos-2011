/*
 * ArchivoControlTriadas.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ArchivoControlTriadas.h"

ArchivoControlTriadas::ArchivoControlTriadas() {

}

ArchivoControlTriadas::ArchivoControlTriadas(string pathArchivoControlTriadas) {
	this->pathArchivoControlTriadas = pathArchivoControlTriadas;

	char* cstrPath = new char[path.size() + 1];
	strcpy(cstrPath, path.c_str());

	if (Existe(cstrPath, this->archivoControlTriadas)) {
		Abrir(cstrPath, this->archivoControlTriadas, false);
		Logger::log("ArchivoControlTriadas", "ArchivoControlTriadas",
				"Se abre el archivo de control.");
	} else {
		Logger::log("ArchivoControlTriadas", "ArchivoControlTriadas",
				"El archivo no existe.");
		CrearSiNoExiste(cstrPath, this->archivoControlTriadas);
		Logger::log("ArchivoControlTriadas", "ArchivoControlTriadas",
				"Se crea un archivo nuevo.");
	}
	delete[] cstrPath;
}

void ArchivoControlTriadas::actualizarArchivo() {
	// TODO: actualizar archivo control triadas
}

void ArchivoControlTriadas::eliminarLibro(uint32_t idLibro) {
	//TODO
}

fstream ArchivoControlTriadas::getArchivoControlTriadas() const {
	return archivoControlTriadas;
}

ParserArchivoControlTriadas * ArchivoControlTriadas::getParser() const {
	return parser;
}

string ArchivoControlTriadas::getPathArchivoControlTriadas() const {
	return pathArchivoControlTriadas;
}

void ArchivoControlTriadas::setArchivoControlTriadas(
		fstream archivoControlTriadas) {
	this->archivoControlTriadas = archivoControlTriadas;
}

void ArchivoControlTriadas::setParser(ParserArchivoControlTriadas *parser) {
	this->parser = parser;
}

void ArchivoControlTriadas::setPathArchivoControlTriadas(
		string pathArchivoControlTriadas) {
	this->pathArchivoControlTriadas = pathArchivoControlTriadas;
}

ArchivoControlTriadas::~ArchivoControlTriadas() {
	//TODO
}
