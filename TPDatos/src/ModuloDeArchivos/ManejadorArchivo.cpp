/*
 * ManejadorArchivo.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#include "ManejadorArchivo.h"

bool ManejadorArchivo::Crear(const char *pathArchivo, fstream &arc,
		bool binario) {
	if (binario)
		arc.open(pathArchivo, ios::in | ios::out | ios::trunc | ios::binary);//es "la linea"
	else
		arc.open(pathArchivo, ios::in | ios::out | ios::trunc);//es "la linea"
	if (arc.is_open())
		return true;
	return false;
}

bool ManejadorArchivo::Abrir(const char *pathArchivo, fstream &arc,
		bool binario) {
	if (binario)
		arc.open(pathArchivo, fstream::in | fstream::out | fstream::binary);
	else
		arc.open(pathArchivo, fstream::in | fstream::out);

	if (arc.is_open())
		return true;
	return false;
}

bool ManejadorArchivo::Existe(const char* pathArchivo, fstream & arc) {
	bool aux = Abrir(pathArchivo, arc, true);
	Cerrar(arc);

	return aux;
}

bool ManejadorArchivo::CrearSiNoExiste(const char* pathArchivo, fstream &arc) {
	if (!Existe(pathArchivo, arc)) {
		Crear(pathArchivo, arc, true);
		return true;
	} else {
		Abrir(pathArchivo, arc, true);
		return false;
	}
}


bool ManejadorArchivo::CrearDirectorios(string pathCarpeta)
{
	system(("makedir " + pathCarpeta).c_str());
	return true;
}


bool ManejadorArchivo::EscribirDato(fstream &arc, Dato* d) {
	stringstream aux;
	aux << d->getDato();
	Escribir(arc, &aux);
}

bool ManejadorArchivo::EscribirDato(fstream &arc, Dato* d, uint32_t offset) {
	arc.seekg(offset, ios_base::beg);
	stringstream aux;
	aux << d->getDato();
	Escribir(arc, &aux);
}

bool ManejadorArchivo::Escribir(fstream &arc, stringstream * ss) {
	if (arc.is_open() && arc.good()) {
		IrAlInicio(arc);
	}
	if (arc.good() && ss->good()) {
		arc << ss->str();
		arc.flush();
	} else
		return false;
}

bool ManejadorArchivo::Escribir(fstream &arc, stringstream * ss,
		uint32_t offset) {

	if (arc.good() && ss->good()) {
		arc.seekp(offset, ios_base::beg);
		arc << ss->str();
		arc.flush();
	} else
		return false;
}

bool ManejadorArchivo::Escribir(fstream* arc, iostream* ios, long offset,
		long size) {
	bool rdo = false;
	char* buffer = new char[size];

	arc->seekp(offset, ios_base::beg);
	ios->read(buffer, size);
	arc->write(buffer, size);
	if (arc->good() && ios->good())
		rdo = true;

	delete[] buffer;
	return rdo;
}

string ManejadorArchivo::LeerDato(fstream &arc) {
	string rdo;
	uint32_t size;
	char* contenido = (char*) malloc(0);

	arc.read(reinterpret_cast<char *> (&size), sizeof(size));
	contenido = (char*) realloc(contenido, size);
	arc.read(contenido, size);
	rdo = contenido;
	rdo = rdo.substr(0, size);

	return rdo;
}

string ManejadorArchivo::LeerCaracteres(fstream &arc, int tamanio) {
	if (arc.eof())
		return "";
	else {
		char* buffer = new char[tamanio + 1];
		stringstream sin;
		arc.get(buffer, tamanio + 1);
		sin << buffer;
		delete[] buffer;

		return sin.str();
	}
}

uint32_t ManejadorArchivo::GetSizeArchivo(string path) {
	fstream archivo;
	uint32_t size = 0;

	if (Existe(path.c_str(), archivo))
	{
		Abrir(path.c_str(), archivo, false);
		size = GetSizeArchivo(archivo);
		Cerrar(archivo);
	}
	return size;
}

uint32_t ManejadorArchivo::GetSizeArchivo(fstream & arc) {
	arc.seekp(0, ios_base::end);
	uint32_t size = arc.tellg();
	IrAlInicio(arc);

	return size;//pide cual es el tamanio del archivo
}

bool ManejadorArchivo::RecuperarEstructura(fstream &arc, stringstream &ss,
		uint32_t offset) {
	//string rdo = "";
	uint32_t size;
	char* buffer;

	arc.seekg(offset, ios_base::beg);//se posiciona el ptro en offset
	arc.read(reinterpret_cast<char *> (&size), sizeof(size));//se lee el size del dato
	buffer = new char[size];
	memset(buffer, 0, size);
	arc.read(buffer, size);
	//rdo.append(buffer, size);

	ss.write(buffer, size);

	delete[] buffer;

	if (arc.good() && ss.good())
		return true;
	else
		return false;

}

bool ManejadorArchivo::RecuperarEstructura(fstream &arc, stringstream &ss,
		uint32_t posEstructura, long tamanioEstructura) {
	char* buffer = new char[tamanioEstructura];

	arc.seekg(posEstructura, ios_base::beg);//se posicione en posEstructura
	memset(buffer, 0, tamanioEstructura);//se reserva la cantidad sizeEstructura
	arc.read(buffer, tamanioEstructura);//se lee

	ss.write(buffer, tamanioEstructura);
	delete[] buffer;

	if (arc.good() && ss.good())
		return true;//esta todon bien
	else
		return false;//o esta todon mal
}

void ManejadorArchivo::IrAlInicio(fstream &arc) {
	arc.seekp(0, ios_base::beg);
}

void ManejadorArchivo::IrAlFinal(fstream &arc) {
	arc.seekp(0, ios_base::end);
}

bool ManejadorArchivo::Cerrar(fstream &arc) {
	arc.close();
	return true;
}

