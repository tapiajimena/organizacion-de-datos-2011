/*
 * ArchivoControlLibro.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 */

#include "ArchivoControlLibro.h"

ArchivoControlLibro::ArchivoControlLibro() {
}

ArchivoControlLibro::ArchivoControlLibro(string path) {
	this->pathArchivoControlLibro = path;

	if (Existe(this->pathArchivoControlLibro.c_str(), this->archivoControlLibro)) {
		Abrir(this->pathArchivoControlLibro.c_str(), this->archivoControlLibro,
				true);
		Logger::log("ArchivoControlLibro", "ArchivoControlLibro",
				"Se abre el archivo de control.");
	} else {
		Logger::log("ArchivoControlLibro", "ArchivoControlLibro",
				"El archivo no existe.");
	}
}

void ArchivoControlLibro::cargarLibros() {
	this->parser = new ParserArchivoControl(CONTROL_TOKEN);
	this->libros = this->parser->getLibros(&archivoControlLibro);
	Cerrar(this->archivoControlLibro);
}

bool ArchivoControlLibro::chequearIndexado(uint32_t idLIbro) {
	cargarLibros();

	return false;
}

string ArchivoControlLibro::getPathArchivoControlLibro() const {
	return pathArchivoControlLibro;
}

void ArchivoControlLibro::setPathArchivoControlLibro(
		string pathArchivoControlLibro) {
	this->pathArchivoControlLibro = pathArchivoControlLibro;
}

uint32_t ArchivoControlLibro::dondeEscribo(uint32_t sizeAlmacenar) {
	cargarLibros();
	return 0;
}

void ArchivoControlLibro::registrarIndexado(uint32_t idLibro, char tipoClave) {
	cargarLibros();

	this->libros->find(idLibro);
	if (it != this->libros->end()) {
	}
}

void ArchivoControlLibro::registrarLibro(uint32_t idLibro) {
	string str;
	stringstream ssAux;
	char aux[11]; // 11 bytes: 10 for the digits, 1 for the null character

	snprintf(aux, sizeof aux, "%lu", (uint32_t) idLibro);

	if (idLibro > 0)//si no es el primer archivo se le inserta un enter adelante
		str = "\n";

	//se arma el string:
	//offset|sizeLibre|TagAutor|TagEditorial|TagTitulo|TagPalabras (se inicializan en 0 los tags)
	str = str + aux + INICIALIZACION_ARCHIVO_LIBRO_CONTROL;

	ssAux.write(str.c_str(), str.length());
	Escribir(archivoControlLibro, &ssAux);
}

ArchivoControlLibro::~ArchivoControlLibro() {
	// TODO Auto-generated destructor stub
	//liberar el parser.
}
