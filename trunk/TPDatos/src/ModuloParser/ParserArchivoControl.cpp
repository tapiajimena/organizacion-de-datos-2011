/*
 * ParserArchivoControl.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ParserArchivoControl.h"

ParserArchivoControl::ParserArchivoControl(string token) :
	ParserAuxiliar(token) {
	this->libros = new map<uint32_t, DatoControlLibro*> ();
	this->it = this->libros->begin();
	this->contadorLinea = 0;
	this->datoNuevo = new DatoControlLibro();
}

map<uint32_t, DatoControlLibro*>* ParserArchivoControl::getLibros(
		fstream* archivo) {
	IrAlInicio(*archivo);
	leerArchivo(archivo);
	return this->libros;
}

void ParserArchivoControl::leerArchivo(fstream* archivo) {
	char buffer[CONTROL_LENGTH];

	if (archivo->is_open()) {
		Logger::log("parserArchivoControl", "leerArchivo",
				"Se comienza a leer el archivo de control");
		this->it = this->libros->begin();
		do {
			archivo->getline(buffer, CONTROL_LENGTH);
			cout << buffer << endl;
			cargarEstructura(buffer);
			this->contadorLinea++;
			this->it++;
		} while (!archivo->eof());
	} else {
		Logger::log("parserArchivoControl", "leerArchivo",
				"No se pudo abrir el archivo de control");
	}
}

void ParserArchivoControl::cargarEstructura(string dato) {
	vector<string> datos = ServiceClass::obtenerListaPalabras(dato,
			CONTROL_TOKEN);

	/* Dado que el orden de los datos es id|espacioLibre|indice */

	//id_Libro, espacioLibre, indexado, offset
	this->datoNuevo->setEspacioLibre(
			ServiceClass::convertirAUint32(datos.at(1)));
	this->datoNuevo->setId_Libro(ServiceClass::convertirAUint32(datos.at(0)));
	setTipoIndice(datos);
	this->datoNuevo->setOffset(this->contadorLinea);

	cout << "DATO NUEVO" << endl;
	cout << this->datoNuevo->getEspacioLibre() << endl;
	cout << this->datoNuevo->getId_Libro() << endl;
	cout << this->datoNuevo->getOffset() << endl;

	setTipoIndice(datos);

	Logger::log("parserArchivoControl", "cargarEstructura",
			"Se obtiene el dato de control.");

	DatoControlLibro* d = new DatoControlLibro(this->datoNuevo);

	cout << d->getIndexado()->front() << endl;
	cout << d->getIndexado()->back() << endl;

	this->libros->insert(pair<uint32_t, DatoControlLibro*> (
			ServiceClass::convertirAUint32(datos.at(0)), d));

	Logger::log("parserArchivoControl", "cargarEstructura",
			"Se le agrega al map un nuevo dato.");
}

void ParserArchivoControl::setTipoIndice(vector<string> datos) {
	list<char>::iterator it_lista = this->datoNuevo->getIndexado()->begin();
	vector<string>::iterator it_datos;

	this->datoNuevo->getIndexado()->clear();

	int i = 0;
	for (it_datos = datos.begin() + 2; it_datos != datos.end(); it_datos++) {
		if (i < 4) {
			string aux = (*it_datos);
			char c_aux = aux[0];
			this->datoNuevo->getIndexado()->push_back(c_aux);
		}
		i++;
	}

	Logger::log("parserArchivoControl", "getTipoIndice",
			"Se obtiene el tipo de Indice.");
}

list<char>* ParserArchivoControl::getTipoIndice(vector<string> datos) const {
	return this->datoNuevo->getIndexado();
}

ParserArchivoControl::~ParserArchivoControl() {
	delete (this->datoNuevo);

	for (it = this->libros->begin(); it != this->libros->end(); it++)
		delete ((*it).second);
	delete (this->libros);
}
