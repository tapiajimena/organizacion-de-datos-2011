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
	this->archivoFragmentado = true;
}

ArchivoControlLibro::ArchivoControlLibro(string path) {
	this->pathArchivoControlLibro = path;
	this->archivoFragmentado = true;

	if (Existe(this->pathArchivoControlLibro.c_str(), this->archivoControlLibro)) {
		Abrir(this->pathArchivoControlLibro.c_str(), this->archivoControlLibro,
				false);
		Logger::log("ArchivoControlLibro", "ArchivoControlLibro",
				"Se abre el archivo de control.");
	} else {
		Logger::log("ArchivoControlLibro", "ArchivoControlLibro",
				"El archivo no existe.");
	}
}

DatoControlLibro* ArchivoControlLibro::buscarEnMap(uint32_t idLibro) {
	IrAlInicio(this->archivoControlLibro);
	it = this->libros->find(idLibro);
	if (it != this->libros->end()) {
		Logger::log("ArchivoControlLibro", "buscarEnMap",
				"Se encontro el libro buscado.");
		Logger::log("ArchivoControlLibro", "buscarEnMap",
				"Se devuelve el libro buscado.");
		return (*it).second;
	} else {
		Logger::log("ArchivoControlLibro", "buscarEnMap",
				"No se cuentra el libro en el map.");
		return NULL;
	}
}

void ArchivoControlLibro::cargarLibros() {
	this->parser = new ParserArchivoControl(CONTROL_TOKEN);
	this->libros = this->parser->getLibros(&archivoControlLibro);

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

	cout << "lo que recibe el donde escribo: " << endl;
	list<DatoControlLibro*>::iterator itt;
	for (itt = espaciosLibres->begin(); itt != espaciosLibres->end(); ++itt) {
		cout << (*itt)->getEspacioLibre() << endl;
	}

	list<DatoControlLibro*>* espaciosLibresFusionados;
	uint32_t mejorAjuste;

	if (espaciosLibres->size() == 0) {
		mejorAjuste = FIN_DE_ARCHIVO;
	} else {

		if (this->archivoFragmentado) {
			espaciosLibresFusionados = fusionarEspaciosLibres(espaciosLibres);

			cout << "espaciosLibresFusionados: " << endl;
			for (itt = espaciosLibresFusionados->begin(); itt
					!= espaciosLibresFusionados->end(); ++itt) {
				cout << (*itt)->getEspacioLibre() << endl;
			}

			this->archivoFragmentado = false;
			mejorAjuste = getMejorAjuste(espaciosLibresFusionados,
					sizeAlmacenar);

			cout << "mejorAjuste: " << mejorAjuste << endl;

			Logger::log(
					"ArchivoControlLibro",
					"dondeEscribo",
					"Se busca el lugar que mejor ajuste en espacio considerando espacios libres contiguos.");
		} else {
			mejorAjuste = getMejorAjuste(espaciosLibres, sizeAlmacenar);
			Logger::log("ArchivoControlLibro", "dondeEscribo",
					"Se busca el lugar que mejor ajuste en espacio.");
		}
	}

	return mejorAjuste;
}

list<DatoControlLibro*>* ArchivoControlLibro::getEspaciosLibres() {
	cargarLibros();

	list<DatoControlLibro*>* espaciosLibres = new list<DatoControlLibro*> ();

	DatoControlLibro* d_aux;
	//recorro el map en busqueda de espacios libres
	//y lleno la lista anterior con los mismos
	for (it = libros->begin(); it != libros->end(); ++it) {
		if (((*it).second)->getEspacioLibre() > 0) {
			d_aux = new DatoControlLibro((*it).second);
			espaciosLibres->push_back(d_aux);
		}
	}

	Logger::log("ArchivoControlLibro", "getEspaciosLibres",
			"Se buscan los espacios libres para grabar.");

	return espaciosLibres;
}

list<DatoControlLibro*>* ArchivoControlLibro::fusionarEspaciosLibres(list<
		DatoControlLibro*>* espaciosLibres) {
	list<DatoControlLibro*>* espaciosLibresFusionados = new list<
			DatoControlLibro*> ();

	DatoControlLibro* aux = espaciosLibres->front();
	espaciosLibres->pop_front();
	DatoControlLibro* cola = espaciosLibres->back();

	Logger::log("ArchivoControlLibro", "fusionarEspaciosLibres",
			"Fusionando los espacios libres.");
	list<DatoControlLibro*>::iterator it;
	for (it = espaciosLibres->begin(); it != espaciosLibres->end(); it++) {

		while ((aux->getId_Libro() + METADATA_SIZE_BOOK
				+ aux->getEspacioLibre()) == (*it)->getId_Libro()) {
			aux->setEspacioLibre(aux->getEspacioLibre()
					+ (*it)->getEspacioLibre() + METADATA_SIZE_BOOK);

			if ((*it)->getId_Libro() < cola->getId_Libro()){
				delete(*it);
				it++;
			}
			cout << aux->getEspacioLibre() << " id_Libro: "
					<< aux->getId_Libro() << endl;
		}
		espaciosLibresFusionados->push_back(aux);
		if (it != espaciosLibres->end())
			aux = *it;
	}
	if (espaciosLibresFusionados->size() > 0) {
		Logger::log("ArchivoControlLibro", "fusionarEspaciosLibres",
				"Se comienzan a actualizar los espacios libres.");
		actualizarEspaciosLibres(espaciosLibresFusionados);
	}

	Logger::log("ArchivoControlLibro", "fusionarEspaciosLibres",
			"Se terminan de fusionar los espacios libres.");

	return espaciosLibresFusionados;

}

struct less_than {
	bool operator()(DatoControlLibro* primero, DatoControlLibro* segundo) {
		return (primero->getEspacioLibre() < segundo->getEspacioLibre());
	}
};

uint32_t ArchivoControlLibro::getMejorAjuste(
		list<DatoControlLibro*>* espaciosLibres, uint32_t sizeAlmacenar) {

	espaciosLibres->sort(less_than());

	for (list<DatoControlLibro*>::const_iterator ci = espaciosLibres->begin(); ci
			!= espaciosLibres->end(); ++ci) {
		if ((*ci)->getEspacioLibre() >= sizeAlmacenar)
			return (*ci)->getId_Libro();
	}

	//en caso de que no se haya podido encontrar un lugar
	return FIN_DE_ARCHIVO;
}

void ArchivoControlLibro::actualizarEspaciosLibres(
		list<DatoControlLibro*>* espaciosLibres) {

	cout << "llega: " << endl;
	list<DatoControlLibro*>::iterator itt;
	for (itt = espaciosLibres->begin(); itt != espaciosLibres->end(); ++itt) {
		cout << (*itt)->getEspacioLibre() << endl;
		cout << (*itt)->getId_Libro() << endl;
	}

	cout << "tamaño: " << libros->size() << endl;
	//BORRARRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
	for (this->it = libros->begin(); this->it != libros->end(); ++it) {
		cout << ((*it).first) << endl;
	}

	this->it = this->libros->begin();
	map<uint32_t, DatoControlLibro*>::iterator it_aux;
	//borro los espacios libres anteriores desactualizados
	while (it != libros->end()) {
		if (((*it).second)->getEspacioLibre() > 0) {
			it_aux = it;
			++it;
			libros->erase(it_aux);
		} else {
			++it;
		}
	}
	cout << "tamaño: " << libros->size() << endl;

	//ingreso los nuevos espacios
	for (list<DatoControlLibro*>::const_iterator ci = espaciosLibres->begin(); ci
			!= espaciosLibres->end(); ++ci) {
		libros->insert(pair<uint32_t, DatoControlLibro*> ((*ci)->getId_Libro(),
				(*ci)));
	}

	cout << "A ver como quedo... " << endl;
	for (this->it = libros->begin(); this->it != libros->end(); ++it) {
		cout << ((*it).first) << endl;
	}
}

void ArchivoControlLibro::registrarIndexado(uint32_t idLibro, char tipoClave) {
	cargarLibros();
	DatoControlLibro* d = buscarEnMap(idLibro);

	if (d != NULL) {
		Logger::log("ArchivoControlLibro", "registrarIndexado",
				"Obtengo el libro a indexar.");

		list<char>::iterator it;
		bool encontrado = false;
		for (it = d->getIndexado()->begin(); it != (d->getIndexado()->end()); it++) {
			if (((*it) == '-') && (!encontrado)) {
				(*it) = tipoClave;
				encontrado = true;
			} else {
				if (!encontrado)
					Logger::log("ArchivoControlLibro", "registrarIndexado",
							"Ya esta indexado.");
			}
		}
		Logger::log("ArchivoControlLibro", "registrarIndexado",
				"Se registra una nueva indexacion.");

		for (it = d->getIndexado()->begin(); it != d->getIndexado()->end(); it++) {
			cout << "ahora quedo como: " << *it << endl;
		}
	} else {
		Logger::log("ArchivoControlLibro", "registrarIndexado",
				"No se encontro el libro.");
	}
}

void ArchivoControlLibro::actualizarArchivo() {
	Logger::log("ArchivoControlLibro", "actualizarArchivo",
			"Se comienza a actualizar el archivo de control.");

	Cerrar(this->archivoControlLibro);
	Crear(this->pathArchivoControlLibro.c_str(), this->archivoControlLibro,
			true);

	stringstream ss;
	for (it = this->libros->begin(); it != this->libros->end(); it++) {
		ss << (it->second)->serializar();
		ss << "\n";
		cout << ss.str() << endl;
	}
	//se le saca el ultimo \n
	string aux = ss.str();
	aux = aux.substr(0, aux.length() - 1);

	stringstream ss1;
	ss1 << aux;

	Escribir(this->archivoControlLibro, &ss1, 0);

	Logger::log("ArchivoControlLibro", "actualizarArchivo",
			"Se termina de actualizar el archivo de control.");

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

void ArchivoControlLibro::eliminarLibro(uint32_t idLibro, uint32_t size) {
	archivoFragmentado = true;
	cargarLibros();


	if(buscarEnMap(idLibro) != NULL){
		(buscarEnMap(idLibro))->setEspacioLibre(size);
		cout << "el espacio libre es: " << (buscarEnMap(idLibro))->getEspacioLibre() << endl;
		Logger::log("ArchivoControlLibro","eliminarLibro","Se elimina el libro.");
	}else{
		Logger::log("ArchivoControlLibro","eliminarLibro","No se encontro el libro.");
	}

}

ArchivoControlLibro::~ArchivoControlLibro() {
	// TODO Auto-generated destructor stub
	Logger::log("ArchivoControlLibro", "~ArchivoControlLibro",
			"Se cierra el archivo de control.");

	Cerrar(this->archivoControlLibro);
}
