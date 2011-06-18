/*
 * ParserArchivoTriadas.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ParserArchivoTriadas.h"

ParserArchivoTriadas::ParserArchivoTriadas(string token) :
	ParserTriadas(token) {
	this->datoNuevo = new DatoTriada();
}

void ParserArchivoTriadas::cargarEstructura(string dato) {
}

void ParserArchivoTriadas::leerArchivo(fstream* archivo, uint32_t offset) {
	uint32_t idLibro, idTermino;
	long posicionRelativa;

	if (GetSizeArchivo(*archivo) > 0) {
		if (archivo->is_open()) {
			Logger::log("ParserTriadas", "leerArchivo",
					"Se comienza a leer el archivo de control");
			archivo->seekg(offset);

			archivo->read(reinterpret_cast<char *> (&idLibro), sizeof(idLibro));
			archivo->read(reinterpret_cast<char *> (&idTermino),
					sizeof(idTermino));
			archivo->read(reinterpret_cast<char *> (&posicionRelativa),
					sizeof(posicionRelativa));
			cout<<"EL OFFSET: "<<offset<<endl;
			cout<<"idLibro: "<<idLibro<<endl;
			cargarEstructura(idLibro, idTermino, posicionRelativa);
		} else {
			Logger::log("ParserTriadas", "leerArchivo",
					"El archivo no esta abierto.");
		}
	} else {
		Logger::log("ParserTriadas", "leerArchivo",
				"El archivo esta vacio o no existe.");
	}
}


DatoTriada* recuperarTriada(fstream* archivo, uint32_t offset)
{
	DatoTriada* triadaResultado = new DatoTriada();
	uint32_t idLibro, idTermino;
	long posicionRelativa;

	if (GetSizeArchivo(*archivo) > 0) {
		if (archivo->is_open()) {
			Logger::log("ParserTriadas", "recuperarTriada",
					"Se comienza a leer el archivo de control");

			archivo->seekg(offset);

			archivo->read(reinterpret_cast<char *> (&idLibro), sizeof(idLibro));
			archivo->read(reinterpret_cast<char *> (&idTermino),
					sizeof(idTermino));
			archivo->read(reinterpret_cast<char *> (&posicionRelativa),
					sizeof(posicionRelativa));
			//antes
			//cargarEstructura(archivo,offset);
			cout<<"Se recupero: "<<idLibro<<endl;
			triadaResultado->setIdLibro(idLibro);
			triadaResultado->setIdTermino(idTermino);
			triadaResultado->setPosicion(posicionRelativa);
		} else {
			Logger::log("ParserTriadas", "leerArchivo",
					"El archivo no esta abierto.");
		}
	} else {
		Logger::log("ParserTriadas", "leerArchivo",
				"El archivo esta vacio o no existe.");
	}

	return triadaResultado;
}

/*
//ANTES
DatoTriada* ParserArchivoTriadas::getTriada(fstream* archivo, uint32_t offset) {
	DatoTriada* d = NULL;

	IrAlInicio(*archivo);
	leerArchivo(archivo, offset);

	if (!this->triadas->empty())
		d = (DatoTriada*)this->triadas->front();

	return d;
}
*/



DatoTriada* ParserArchivoTriadas::getTriada(fstream* archivo, uint32_t offset)
{
	IrAlInicio(*archivo);
	return recuperarTriada(archivo, offset);
}


void ParserArchivoTriadas::cargarEstructura(uint32_t idLibro, uint32_t idTermino,
		long posicionRelativa) {
	this->triada->setIdLibro(idLibro);
	this->triada->setIdTermino(idTermino);
	this->triada->setPosicion(posicionRelativa);

	DatoTriada* d = new DatoTriada(this->triada);
	this->triadas->push_back(d);
}

ParserArchivoTriadas::~ParserArchivoTriadas() {
	// TODO Auto-generated destructor stub
}
