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

ArchivoControlTriadas::ArchivoControlTriadas(string path) {
	this->pathArchivoControlTriadas = path;

	char* cstrPath = new char[pathArchivoControlTriadas.size() + 1];
	strcpy(cstrPath, pathArchivoControlTriadas.c_str());

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
	Logger::log("ArchivoControlTriadas", "actualizarArchivo",
			"Se comienza a actualizar el archivo de control de triadas.");

	Cerrar(this->archivoControlTriadas);
	fstream arc;
	Crear(this->pathArchivoControlTriadas.c_str(), arc, true);

	//TODO cargar los datos de control en atributo datosControl
	/*
	if (this->datosControl->empty())
	{
		stringstream ss;
		for (it = this->datosControl->begin(); it != this->datosControl->end(); it++)
		{
			ss << (it->second)->serializar();
			ss << "\n";
		}
		//se le saca el ultimo \n
		string aux = ss.str();
		aux = aux.substr(0, aux.length() - 1);

		stringstream ss1;
		ss1 << aux;

		Escribir(arc, &ss1, 0);
	}
	*/

	Logger::log("ArchivoControlTriadas", "actualizarArchivo",
			"Se termina de actualizar el archivo de control.");
}

void ArchivoControlTriadas::eliminarLibro(uint32_t idLibro) {
	//TODO
}


void ArchivoControlTriadas::cargarDatosControl() {

	this->parser = new ParserArchivoControlTriadas(CONTROL_TOKEN);

	this->datosControl = this->parser->getDatosControl(&archivoControlTriadas);

	Logger::log("ArchivoControlLibro", "cargarLibros",
			"Se obtienen los datos de control de las triadas.");
}

DatoControlTriada* ArchivoControlTriadas::buscarEnMap(uint32_t idLibro) {
	IrAlInicio(this->archivoControlTriadas);
	it = this->datosControl->find(idLibro);
	if (it != this->datosControl->end()) {
		Logger::log("ArchivoControlTriada", "buscarEnMap",
				"Se encontro el libro buscado.");
		Logger::log("ArchivoControlTriada", "buscarEnMap",
				"Se devuelve el libro buscado.");
		return (*it).second;
	} else {
		Logger::log("ArchivoControlTriada", "buscarEnMap",
				"No se cuentra el libro en el map.");
		return NULL;
	}
}

ParserArchivoControlTriadas * ArchivoControlTriadas::getParser() const {
	return parser;
}

string ArchivoControlTriadas::getPathArchivoControlTriadas() const {
	return pathArchivoControlTriadas;
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
