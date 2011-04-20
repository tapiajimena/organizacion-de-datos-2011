/*
 * ArchivoControlLibro.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 */

#include "ArchivoControlLibro.h"

ArchivoControlLibro::ArchivoControlLibro() {
	archivoFragmentado = false;
}

ArchivoControlLibro::ArchivoControlLibro(string path) {
	ArchivoControlLibro();
	this->pathArchivoControlLibro = path;

	if (Existe(this->pathArchivoControlLibro.c_str(), this->archivoControlLibro)) {
		Abrir(this->pathArchivoControlLibro.c_str(), this->archivoControlLibro,
				true);
		Logger::log("ArchivoControlLibro", "ArchivoControlLibro",
				"Se abre el archivo de control.");
	} else {
		Logger::log("ArchivoControlLibro", "ArchivoControlLibro",
				"El archivo no existe.");
	}
}

DatoControlLibro* ArchivoControlLibro::buscarEnMap(uint32_t idLibro) {
	it = this->libros->find(idLibro);
	if (it != this->libros->end()) {
		Logger::log("ArchivoControlLibro", "buscarEnMap",
				"Se encontro el libro buscado.");

		DatoControlLibro* d = new DatoControlLibro((*it).second);
		Logger::log("ArchivoControlLibro", "buscarEnMap",
				"Se devuelve el libro buscado.");
		return d;
	} else {
		Logger::log("ArchivoControlLibro", "buscarEnMap",
				"No se cuentra el libro en el map.");
		return NULL;
	}
}

void ArchivoControlLibro::cargarLibros() {
	this->parser = new ParserArchivoControl(CONTROL_TOKEN);
	this->libros = this->parser->getLibros(&archivoControlLibro);

	if (this->libros->empty())
		cout << "empty" << endl;

	Logger::log("ArchivoControlLibro", "cargarLibros",
			"Se obtienen los datos de control de los libros.");
}

list<char>* ArchivoControlLibro::chequearIndexado(uint32_t idLibro) {
	cargarLibros();
	DatoControlLibro* datoBuscado = buscarEnMap(idLibro);

	if (datoBuscado != NULL) {
		Logger::log("ArchivoControlLibro", "chequearIndexado",
				"El libro buscado esta indexado.");
		return datoBuscado->getIndexado();
	} else {
		Logger::log("ArchivoControlLibro", "chequearIndexado",
				"No se encuentra el libro buscado.");
		return NULL;
	}
}

string ArchivoControlLibro::getPathArchivoControlLibro() const {
	return pathArchivoControlLibro;
}

void ArchivoControlLibro::setPathArchivoControlLibro(
		string pathArchivoControlLibro) {
	this->pathArchivoControlLibro = pathArchivoControlLibro;
}

uint32_t ArchivoControlLibro::dondeEscribo(uint32_t sizeAlmacenar) {

	list<DatoControlLibro*>* espaciosLibres = getEspaciosLibres();
	list<DatoControlLibro*>* espaciosLibresFusionados;
	uint32_t mejorAjuste;

	if (espaciosLibres->size() == 0)
		return FIN_DE_ARCHIVO;

	if (archivoFragmentado) {
		espaciosLibresFusionados = fusionarEspaciosLibres(espaciosLibres);
		archivoFragmentado = false;
		mejorAjuste = getMejorAjuste(espaciosLibresFusionados, sizeAlmacenar);
	} else {
		mejorAjuste = getMejorAjuste(espaciosLibres, sizeAlmacenar);
	}
	if (mejorAjuste > 0)
		return mejorAjuste;
	else
		return FIN_DE_ARCHIVO;

}

list<DatoControlLibro*>* ArchivoControlLibro::getEspaciosLibres() {
	cargarLibros();

	list<DatoControlLibro*>* espaciosLibres = new list<DatoControlLibro*> ();

	//recorro el map en busqueda de espacios libres
	//y lleno la lista anterior con los mismos
	for (it = libros->begin(); it != libros->end(); ++it) {
		if (((*it).second)->getEspacioLibre() > 0)
			espaciosLibres->push_back(((*it).second));
	}

	return espaciosLibres;
}

list<DatoControlLibro*>* ArchivoControlLibro::fusionarEspaciosLibres(
		list<DatoControlLibro*>* espaciosLibres) {
	list<DatoControlLibro*>* espaciosLibresFusionados = new list<
			DatoControlLibro*> ();

	DatoControlLibro* aux = espaciosLibres->front();
	espaciosLibres->pop_front();

	for (list<DatoControlLibro*>::const_iterator ci = espaciosLibres->begin(); ci
			!= espaciosLibres->end(); ++ci) {
		while (aux->getId_Libro() + aux->getEspacioLibre()
				== (*ci)->getId_Libro()) {
			aux->setEspacioLibre(
					aux->getEspacioLibre() + (*ci)->getEspacioLibre()
							+ METADATA_SIZE_BOOK);
		}
		espaciosLibresFusionados->push_back(aux);
		aux = *ci;
	}
	return espaciosLibresFusionados;
}

uint32_t ArchivoControlLibro::getMejorAjuste(
		list<DatoControlLibro*>* espaciosLibres, uint32_t sizeAlmacenar) {

	espaciosLibres->sort();

	for (list<DatoControlLibro*>::const_iterator ci = espaciosLibres->begin(); ci
			!= espaciosLibres->end(); ++ci) {
		if ((*ci)->getEspacioLibre() >= sizeAlmacenar)
			return (*ci)->getId_Libro();
	}

	//en caso de que no se haya podido encontrar un lugar
	return FIN_DE_ARCHIVO;
}

void ArchivoControlLibro::actualizarEspaciosLibres(list<DatoControlLibro*>* espaciosLibres){;

}

void ArchivoControlLibro::registrarIndexado(uint32_t idLibro, char tipoClave) {
	cargarLibros();
	DatoControlLibro* d = buscarEnMap(idLibro);

	Logger::log("ArchivoControlLibro", "registrarIndexado",
			"Obtengo el libro a indexar.");

	list<char>::iterator it;
	for (it = d->getIndexado()->begin(); it != (d->getIndexado()->end()); it++) {
		if (((*it) == '-')) {
			(*it) = tipoClave;
			it = d->getIndexado()->end();
		} else {
			Logger::log("ArchivoControlLibro", "registrarIndexado",
					"Ya esta indexado.");
		}
	}
	Logger::log("ArchivoControlLibro", "registrarIndexado",
			"Se registra un nuevo indexacion.");

	for (it = d->getIndexado()->begin(); it != d->getIndexado()->end(); it++) {
		cout << "ahora quedo como: " << *it << endl;
	}

	//TODO Persistir cambios en el disco.
}

void ArchivoControlLibro::registrarLibro(uint32_t idLibro) {
	string str;
	stringstream ssAux;
	char aux[11]; // 11 bytes: 10 for the digits, 1 for the null character

	snprintf(aux, sizeof aux, "%lu", (uint32_t) idLibro);

	//	if (idLibro > 0)//si no es el primer archivo se le inserta un enter adelante
	//	str = "\n";

	//se arma el string:
	//offset|sizeLibre|TagAutor|TagEditorial|TagTitulo|TagPalabras (se inicializan en 0 los tags)
	str = str + aux + INICIALIZACION_ARCHIVO_LIBRO_CONTROL;

	ssAux.write(str.c_str(), str.length());
	IrAlFinal(archivoControlLibro);
	Escribir(archivoControlLibro, &ssAux);
}

void ArchivoControlLibro::eliminarLibro(uint32_t idLibro) {
	archivoFragmentado = true;
	//TODO implementar
}

ArchivoControlLibro::~ArchivoControlLibro() {
	// TODO Auto-generated destructor stub
	Logger::log("ArchivoControlLibro", "~ArchivoControlLibro",
			"Se cierra el archivo de control.");
	Cerrar(this->archivoControlLibro);
	this->libros->clear();
	delete (this->libros);
	delete (this->parser);
}
