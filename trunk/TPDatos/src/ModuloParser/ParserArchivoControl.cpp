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
}

map<uint32_t, DatoControlLibro*>* ParserArchivoControl::getLibros(
		fstream* archivo) {
	leerArchivo(archivo);
	return this->libros;
}

void ParserArchivoControl::leerArchivo(fstream* archivo) {
	char buffer[CONTROL_LENGTH];

	if (archivo->is_open()) {
		Logger::log("parserArchivoControl", "leerArchivo",
				"Se comienza a leer el archivo de control");
		do {
			archivo->getline(buffer, CONTROL_LENGTH);
			cargarEstructura(buffer);
			this->contadorLinea++;
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
	DatoControlLibro* datoNuevo = new DatoControlLibro(
			ServiceClass::convertirAUint32(datos.at(0)),
			ServiceClass::convertirAUint32(datos.at(1)), getTipoIndice(datos),
			this->contadorLinea);

	Logger::log("parserArchivoControl", "cargarEstructura",
			"Se obtiene el dato de control.");

	cout<<"id_Libro: "<<ServiceClass::convertirAUint32(datos.at(0))<<datoNuevo->getId_Libro()<<endl;
	cout<<"espaciolibre: "<<ServiceClass::convertirAUint32(datos.at(1))<<datoNuevo->getEspacioLibre()<<endl;
	cout<<"linea: "<<this->contadorLinea<<datoNuevo->getOffset()<<endl;

	this->libros->insert(it, pair<uint32_t, DatoControlLibro*> (
			ServiceClass::convertirAUint32(datos.at(0)), datoNuevo));
	it++;

	Logger::log("parserArchivoControl", "cargarEstructura",
			"Se le agrega al map un nuevo dato.");
}

list<char>* ParserArchivoControl::getTipoIndice(vector<string> datos) const {
	list<char>* indices = new list<char> ();
	list<char>::iterator it_lista = indices->begin();
	vector<string>::iterator it_datos;

	for (it_datos = datos.begin() + 2; it_datos != datos.end(); it_datos++) {
		string aux = (*it_datos);
		char c_aux = aux[0];
		indices->push_back(c_aux);
	}

	Logger::log("parserArchivoControl", "getTipoIndice",
				"Se obtiene el tipo de Indice.");
	return indices;
}

ParserArchivoControl::~ParserArchivoControl() {
	//TODO
}
