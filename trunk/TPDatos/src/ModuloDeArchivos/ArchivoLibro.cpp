/*
 * ArchivoLibro.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 */

#include "ArchivoLibro.h"

using namespace ManejadorArchivo;

ArchivoLibro::ArchivoLibro() {
}

ArchivoLibro::ArchivoLibro(string pathArchivo) {
	this->path = pathArchivo;
	this->abrir();
}

void ArchivoLibro::abrir() {
	//se abre el archivo de forma binaria, si no existe lo crea
	//si existe lo borra...
	if (Existe(path.c_str(), archivoVariable)) {
		Abrir(path.c_str(), archivoVariable, true);

		Logger::log("ArchivoLibro", "abrir",
				"Se abre el archivo de registros variables.");
	} else {
		Crear(path.c_str(), archivoVariable, true);

		Logger::log("ArchivoLibro", "abrir",
				"Se creo el archivo de registros variables.");

	}
}

void ArchivoLibro::agregarLibro(char* pathLibro, uint32_t nuevoOffset) {
	string rdo;
	DatoLibro* dato = new DatoLibro();
	uint32_t sizeAux;
	fstream arcLibro;

	Abrir(pathLibro, arcLibro, true);

	Logger::log("ArchivoLibro", "agregarLibro",
			"Se abre el archivo con el libro a agregar.");

	//se lee en contenidoLibro el libro completo
	char* contenidoLibro = leer(arcLibro, sizeAux);

	//se procesa
	rdo = contenidoLibro;
	rdo = rdo.substr(0, sizeAux);
	dato->setDato(rdo);

	Logger::log("ArchivoLibro", "agregarLibro",
			"Se lee el archivo y se procesa.");

	Cerrar(arcLibro);//se cierra el arcLibro

	Logger::log("ArchivoLibro", "agregarLibro",
			"Se crea el nuevo dato libro.");

	escribir(*dato, nuevoOffset);

	Logger::log("ArchivoLibro", "agregarLibro",
			"Se escribe el dato en el archivo de registros variables.");
}

DatoLibro ArchivoLibro::recuperarLibro(uint32_t idLibro) {
	stringstream ss;
	DatoLibro rdo;

	if (!this->finArchivo())
		RecuperarEstructura(archivoVariable, ss, idLibro);
	rdo.setDato(ss.str());

	Logger::log("ArchivoLibro", "recuperarLibro",
			"Se recupera el libro buscado.");

	return rdo;
}

string ArchivoLibro::recuperarBiblioteca() {
	if (!this->finArchivo())
		return LeerDato(archivoVariable);
}

char* ArchivoLibro::leer(fstream & arcLibro, uint32_t & size) {
	char* contenidoLibro = (char*) (malloc(0));

	size = GetSizeArchivo(arcLibro);
	arcLibro.seekp(0, ios_base::beg);

	//se lee
	contenidoLibro = (char*) (realloc(contenidoLibro, size));
	arcLibro.read(contenidoLibro, size);

	Logger::log("ArchivoLibro", "leer","");

	return contenidoLibro;
}

void ArchivoLibro::escribir(DatoLibro & d, uint32_t offset) {
	string buffer = d.toString();
	uint32_t size = buffer.size();

	this->archivoVariable.seekp(offset, ios_base::beg);

	archivoVariable.write(reinterpret_cast<char *> (&size), sizeof(size));
	archivoVariable.write(buffer.c_str(), size);
	this->archivoVariable.flush();

	Logger::log("ArchivoLibro", "escribir","");
}

string ArchivoLibro::getPath() const {
	return path;
}

void ArchivoLibro::setPath(string path) {
	this->path = path;
}

void ArchivoLibro::escribirAlFinal(DatoLibro &d) {
	stringstream auxStream;
	string aux = d.toString();
	uint32_t size = d.getSize();

	auxStream.write(reinterpret_cast<char *> (&size), sizeof(size));
	auxStream.write(aux.c_str(), size);
	Escribir(archivoVariable, &auxStream);
}

void ArchivoLibro::irAlInicio() {
	IrAlInicio(archivoVariable);
}

uint32_t ArchivoLibro::getSizeArchivo() {
	return GetSizeArchivo(archivoVariable);
}

uint32_t ArchivoLibro::getPosicionActual() {
	return archivoVariable.tellg();
}

bool ArchivoLibro::finArchivo() {
	return this->archivoVariable.eof();
}

ArchivoLibro::~ArchivoLibro() {
	Cerrar(archivoVariable);
}

