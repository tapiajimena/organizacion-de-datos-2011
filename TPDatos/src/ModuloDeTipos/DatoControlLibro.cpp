/*
 * DatoControlLibro.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 */

#include "DatoControlLibro.h"

DatoControlLibro::DatoControlLibro() {
	this->indexado = new list<char> ();
}

DatoControlLibro::DatoControlLibro(DatoControlLibro* d) {
	this->espacioLibre = d->espacioLibre;
	this->id_Libro = d->id_Libro;
	setIndexado(d->indexado);
	this->offset = d->offset;
	Logger::log("datoControlLibro", "DatoControlLibro",
			"Se crea una copia del dato de control libro.");
}

DatoControlLibro::DatoControlLibro(uint32_t id_Libro, uint32_t espacioLibre,
		list<char>* indexado, uint32_t offset) {
	this->espacioLibre = espacioLibre;
	this->id_Libro = id_Libro;
	setIndexado(indexado);
	this->offset = offset;
	Logger::log("datoControlLibro", "DatoControlLibro",
			"Se crea un nuevo dato de control libro.");
}

string DatoControlLibro::serializar() {
	vector<string> datos;
	vector<string>::iterator datos_it = datos.begin();
	list<char>::iterator it;

	string aux;

	for (it = this->indexado->begin(); it != this->indexado->end(); it++) {
		aux += (*it);
		datos.push_back(aux);
		aux.clear();
	}

	string datosControl[] = { ServiceClass::toString(this->id_Libro),
			ServiceClass::toString(this->espacioLibre),
			ServiceClass::toStringData(&datos, CONTROL_TOKEN).substr(0,
					ServiceClass::toStringData(&datos, CONTROL_TOKEN).size()
							- 1), ServiceClass::toString(this->offset) };

	datos.clear();

	//Se inicializa un vector con los datos de control
	datos.insert(datos.begin(), datosControl, datosControl + 4);

	return ServiceClass::toStringData(&datos, CONTROL_TOKEN);
}

bool operator<(const DatoControlLibro &primero, const DatoControlLibro &segundo) {

	cout << "primero" << primero.getEspacioLibre() << endl;
	cout << "segundo" << segundo.getEspacioLibre() << endl;

	return (primero.getEspacioLibre() < segundo.getEspacioLibre());
}

uint32_t DatoControlLibro::getEspacioLibre() const {
	return espacioLibre;
}

uint32_t DatoControlLibro::getId_Libro() const {
	return id_Libro;
}

list<char> * DatoControlLibro::getIndexado() const {
	return indexado;
}

uint32_t DatoControlLibro::getOffset() const {
	return offset;
}

void DatoControlLibro::setEspacioLibre(uint32_t espacioLibre) {
	this->espacioLibre = espacioLibre;
}

void DatoControlLibro::setId_Libro(uint32_t id_Libro) {
	this->id_Libro = id_Libro;
}

void DatoControlLibro::setIndexado(list<char> *indexado) {
	this->indexado = new list<char> ();
	list<char>::iterator it = indexado->begin();

	for (it; it != indexado->end(); it++) {
		char aux = *it;
		this->indexado->push_back(aux);
	}
}

void DatoControlLibro::setOffset(uint32_t offset) {
	this->offset = offset;
}

DatoControlLibro::~DatoControlLibro() {
	list<char>::iterator it;
	if (!this->indexado->empty()) {
		this->indexado->clear();
		delete (this->indexado);
	}
	Logger::log("datoControlLibro", "~DatoControlLibro", "Se libera memoria.");
}
