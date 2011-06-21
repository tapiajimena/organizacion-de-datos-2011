/*
 * ParserArchivoTriadas.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ParserArchivoTriadas.h"

ParserArchivoTriadas::ParserArchivoTriadas(string token) {
	this->separador = token;
	this->triada= new DatoTriada();
	this->triadas =  new list<DatoTriada*>;
}

void ParserArchivoTriadas::leerArchivo(fstream* archivo, uint32_t offset) {
	uint32_t idLibro, idTermino;
	long posicionRelativa;

	uint32_t tamanioArchivo = GetSizeArchivo(*archivo);

	if ((tamanioArchivo > 0) && (offset < tamanioArchivo)){
		if (archivo->is_open()) {
			Logger::log("ParserTriadas", "leerArchivo",
					"Se comienza a leer el archivo de control");
			archivo->seekg(offset);

			archivo->read(reinterpret_cast<char *> (&idLibro), sizeof(idLibro));
			archivo->read(reinterpret_cast<char *> (&idTermino),
					sizeof(idTermino));
			archivo->read(reinterpret_cast<char *> (&posicionRelativa),
					sizeof(posicionRelativa));
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

void ParserArchivoTriadas::cargarEstructura(uint32_t idLibro, uint32_t idTermino,
		long posicionRelativa) {
	DatoTriada* d = new DatoTriada();

	d->setIdLibro(idLibro);
	d->setIdTermino(idTermino);
	d->setPosicion(posicionRelativa);

	this->triadas->push_back(d);
}


DatoTriada* ParserArchivoTriadas::getTriada(fstream* archivo, uint32_t offset) {
	DatoTriada* d = NULL;

	IrAlInicio(*archivo);
	leerArchivo(archivo, offset);

	if (!this->triadas->empty())
		d = (DatoTriada*)this->triadas->front();

	this->triadas->clear();

	return d;
}

ParserArchivoTriadas::~ParserArchivoTriadas() {
	Logger::log("ParserArchivoTriadas", "~ParserArchivoTriadas",
			"Se elimina el ParserArchivoTriadas.");

	/*
	delete(this->triada);

	//elimina cada dato dentro de triadas
	list<DatoTriada*>::iterator itTriadas;
	for(itTriadas= this->triadas->begin(); itTriadas != triadas->end();itTriadas++)
		delete(*itTriadas);
	delete(triadas);
*/

}
