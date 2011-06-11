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

	char* cstrPath = new char [path.size()+1];
	strcpy(cstrPath,path.c_str());

	if (Existe(cstrPath, this->archivoTriadas)) {
		Abrir(cstrPath, this->archivoTriadas,true);
		Logger::log("ArchivoTriadas", "ArchivoTriadas",
				"Se abre el archivo de control.");
	} else {
		Logger::log("ArchivoTriadas", "ArchivoTriadas",
				"El archivo no existe.");
		CrearSiNoExiste(cstrPath,
				this->archivoTriadas);
		Logger::log("ArchivoControlLibro", "ArchivoControlLibro",
				"Se crea un archivo nuevo.");
	}
	delete[] cstrPath;

	this->parser = new ParserArchivoTriadas(CONTROL_TOKEN);
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
