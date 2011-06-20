/*
 * Instruccion_VerEstructura.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_VerEstructura.h"

Instruccion_VerEstructura::Instruccion_VerEstructura(char id,
		char tipoEstructura, string nombreArchivo) :
	Instruccion(id) {
	this->tipoEstructura = tipoEstructura;
	this->nombreArchivo = nombreArchivo;
}


void Instruccion_VerEstructura::crearReporteArchivoControl(string nombreArchivo)
{
	Configuracion* conf = Configuracion::GetInstancia();

	CrearDirectorios(conf->getPathCarpetaReportes());
	CopiarArchivo(conf->getPathCarpetaTrabajo() + ARCHIVO_CONTROL_BIBLIOTECA,
						conf->getPathCarpetaReportes());
	RenombrarArchivo( conf->getPathCarpetaReportes() + ARCHIVO_CONTROL_BIBLIOTECA,
									conf->getPathCarpetaReportes() + nombreArchivo +
									ARCHIVO_ESPACIOSLIBRES_SUFIX + EXTENSION_ARCHIVO_REPORTE);
}

void Instruccion_VerEstructura::crearArchivos() {
	string archivoEstructura;

	crearReporteArchivoControl(this->nombreArchivo);

	if ((this->tipoEstructura == INDICE_AUTOR || this->tipoEstructura
			== INDICE_EDITORIAL)) {
		archivoEstructura = this->nombreArchivo + ARCHIVO_INDICE_SUFIX;
	} else {
		archivoEstructura = this->nombreArchivo + ARCHIVO_TABLA_SUFIX;
	}
	Crear(archivoEstructura.c_str(), this->archivoEstructuras, true);

	string archivoBloques = this->nombreArchivo + ARCHIVO_BLOQUES_SUFIX;
	Crear(archivoBloques.c_str(), this->archivoBloques, true);
}

void Instruccion_VerEstructura::ejecutar()
{
	Indexador* indexador = new Indexador();

	stringstream mayuscula;
	string aux;
	mayuscula << this->tipoEstructura;
	mayuscula >> aux;
	char char_Aux = ServiceClass::toUppercase(aux)[0];

	indexador->generarReporte(char_Aux, this->nombreArchivo);

	//se arman los archivos.
	crearArchivos();


	cout<<"Se generan reportes en la carpeta de resultados."<<endl;
	Logger::log("Instruccion_VerEstructura", "ejecutar",
			"Se muestra la estructura.");

	delete(indexador);
}

Instruccion_VerEstructura::~Instruccion_VerEstructura() {

}
