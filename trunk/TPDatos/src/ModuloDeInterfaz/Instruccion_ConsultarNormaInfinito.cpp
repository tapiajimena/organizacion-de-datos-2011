/*
 * Instruccion_ConsultaNormaInfinito.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ConsultarNormaInfinito.h"


Instruccion_ConsultarNormaInfinito::Instruccion_ConsultarNormaInfinito(char id, string consulta)
																	:Instruccion(id)
{
	this->titulo = consulta;
}


void Instruccion_ConsultarNormaInfinito::ejecutar()
{
	Configuracion* conf = Configuracion::GetInstancia();

	this->controladorBiblioteca = new ControladorBiblioteca(
				conf->getPathCarpetaTrabajo() + ARCHIVO_BIBLIOTECA + EXTENSION_ARCHIVO_INDICE,
				conf->getPathCarpetaTrabajo() + ARCHIVO_CONTROL_BIBLIOTECA);

	this->controladorIndice = new ControladorIndice();

	this->archivoTerminos = new ArchivoTerminos(conf->getPathCarpetaTrabajo()
												+ ARCHIVO_TERMINOS
												+ EXTENSION_ARCHIVO_INDICE);


	std::list<uint32_t> listaDocumentos = this->controladorBiblioteca->recuperarLibrosDeBiblioteca();

	this->calculadorDeNormas = new CalculadorDeNormas(this->controladorIndice, this->archivoTerminos);

	this->calculadorDeNormas->generarReporteDeNormas(listaDocumentos, this->titulo);

	delete (this->calculadorDeNormas);
	delete (this->archivoTerminos);
	delete (this->controladorIndice);
	delete(this->controladorBiblioteca);

	cout<<"Se genero el archivo de consulta de Normas Infinito en "<< conf->getPathCarpetaTrabajo()<<endl;
}

Instruccion_ConsultarNormaInfinito::~Instruccion_ConsultarNormaInfinito() {

}
