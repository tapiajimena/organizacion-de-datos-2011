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
	this->datosControl = new map<uint32_t, DatoControlTriada*> ;
	this->it = datosControl->begin();
	this->pathArchivoControlTriadas = path;
	this->datoEliminado = false;

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

	this->offsets = new list<uint32_t> ;
	cargarDatosControl();
}

uint32_t ArchivoControlTriadas::buscarOffsetDondeEscribir(int cantidadTriadas,
		uint32_t sizeArchivo, uint32_t idLibro) {

	/* Se recorre el map en busqueda de espacios libres */
	for (it = datosControl->begin(); it != datosControl->end(); ++it)
	{
		/* Si ese espacio esta eliminado */
		if (((*it).second)->estaBorrado())
		{
			//recupera y setea el nuevo idLibro de un datoControl
			DatoControlTriada* datoControl = new DatoControlTriada(buscarEnMap(((*it).second)->getIdLibro()));
			datoControl->setIdLibro(idLibro);
			datoControl->setEliminado(false);

			//se elimina la clave del map pertenciente a ese datoControl
			this->datosControl->erase(((*it).second)->getIdLibro());

			//se inserta el nuevo registro en map(idLibro,dControlLibro)
			agregarDatoControl(datoControl);

			this->datoEliminado =true;
			cout << "entra en el espacio vacio " << endl;
			return datoControl->getIdTriadaInicial();
		}
	}
	return sizeArchivo;

}

void ArchivoControlTriadas::actualizarArchivo() {
	Logger::log("ArchivoControlTriadas", "actualizarArchivo",
			"Se comienza a actualizar el archivo de control de triadas.");

	//cargarDatosControl();

	Cerrar(this->archivoControlTriadas);
	fstream arc;
	Crear(this->pathArchivoControlTriadas.c_str(), arc, true);

	stringstream ss;
	for (it = this->datosControl->begin(); it != this->datosControl->end(); it++) {
		ss << (it->second)->serializar();
		ss << "\n";
	}
	//se le saca el ultimo \n
	string aux = ss.str();
	aux = aux.substr(0, aux.length() - 1);

	stringstream ss1;
	ss1 << aux;
	cout<<"LA daata a serializar es: "<<ss1.str()<<endl;

	Escribir(arc, &ss1, 0);

	Logger::log("ArchivoControlTriadas", "actualizarArchivo",
			"Se termina de actualizar el archivo de control.");
}

void ArchivoControlTriadas::agregarDatoControl(DatoControlTriada* nuevo) {
	this->datosControl->insert(
			pair<uint32_t, DatoControlTriada*> (nuevo->getIdLibro(), nuevo));
}

void ArchivoControlTriadas::eliminarLibro(uint32_t idLibro) {
	(buscarEnMap(idLibro))->borrarLibro();
}

list<uint32_t>* ArchivoControlTriadas::getTriadas(uint32_t id_Libro) {
	DatoControlTriada* d = buscarEnMap(id_Libro);

	if (d != NULL) {
		//se asume que el offset inicial y final son validos.
		uint32_t siguiente = d->getIdTriadaInicial();
		while (siguiente <= d->getIdTriadaFinal()) {
			this->offsets->push_back(siguiente);
			siguiente += sizeof(siguiente) * 3;
		}
	}

	return this->offsets;
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


void ArchivoControlTriadas::setDatoEliminado(bool eliminado)
{
	this->datoEliminado = eliminado;
}


bool ArchivoControlTriadas::getDatoEliminado()
{
	return this->datoEliminado;
}


ArchivoControlTriadas::~ArchivoControlTriadas() {
	//TODO
}
