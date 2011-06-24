/*
 * Instruccion_ConsultarTerminosProximos.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ConsultarArchivoTerminos.h"


Instruccion_ConsultarArchivoTerminos::Instruccion_ConsultarArchivoTerminos(char id, string consulta):Instruccion(id)
{
	this->titulo = consulta;
}


void Instruccion_ConsultarArchivoTerminos::ejecutar()
{
	Configuracion* conf = Configuracion::GetInstancia();
	string origen = conf->getPathCarpetaTrabajo() + ARCHIVO_TERMINOS + EXTENSION_ARCHIVO_INDICE;
	string destino= conf->getPathCarpetaReportes() + ARCHIVO_TERMINOS + EXTENSION_ARCHIVO_REPORTE;

	ManejadorArchivo::CopiarArchivo(origen, destino);
	cout<<"Se genero el archivo de terminos"<<endl;
}

Instruccion_ConsultarArchivoTerminos::~Instruccion_ConsultarArchivoTerminos() {

}