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

ArchivoTriadas::ArchivoTriadas(string path) {
	// TODO Auto-generated constructor stub

	this->pathArchivoTriadas = path;
	this->triadas = new list<DatoTriada*> ();

	char* cstrPath = new char[path.size() + 1];
	strcpy(cstrPath, path.c_str());

	if (Existe(cstrPath, this->archivoTriadas)) {
		Abrir(cstrPath, this->archivoTriadas, true);
		Logger::log("ArchivoTriadas", "ArchivoTriadas",
				"Se abre el archivo de control.");
	} else {
		Logger::log("ArchivoTriadas", "ArchivoTriadas", "El archivo no existe.");
		CrearSiNoExiste(cstrPath, this->archivoTriadas);
		Logger::log("ArchivoControlTriadas", "ArchivoControlTriadas",
				"Se crea un archivo nuevo.");
	}
	delete[] cstrPath;

	this->parser = new ParserArchivoTriadas(CONTROL_TOKEN);
}

DatoTriada* ArchivoTriadas::obtenerTriada(uint32_t offset)
{
	return this->parser->getTriada(&this->archivoTriadas,offset);
}

void ArchivoTriadas::escribirAlFinal(DatoTriada* triada)
{
	Logger::log("ArchivoControlTriadas", "escribirAlFinal",
			"Se escribe una triada en el archivo.");

	stringstream auxStream;
	uint32_t idLibro 	= triada->getIdLibro();
	uint32_t idTermino 	= triada->getIdTermino();
	uint32_t posicionTermino= triada->getPosicion();//los long son malos para persistir

	auxStream.write(reinterpret_cast<char *> (&idLibro), sizeof(idLibro));
	auxStream.write(reinterpret_cast<char *> (&idTermino), sizeof(idLibro));
	auxStream.write(reinterpret_cast<char *> (&posicionTermino), sizeof(posicionTermino));

	Escribir(archivoTriadas, &auxStream, this->devolverTamanio());
}

uint32_t ArchivoTriadas::devolverTamanio() {
	return GetSizeArchivo(this->archivoTriadas);
}

list<DatoTriada*>* ArchivoTriadas::getTriadas() {
	//return this->parser->getTriadas(&archivoTriadas);
}

list<DatoTriada*>* ArchivoTriadas::getTriadas(uint32_t id) {
	//return this->parser->getTriadas(&archivoTriadas, id);
}

ArchivoTriadas::~ArchivoTriadas() {
	// TODO Auto-generated destructor stub
}
