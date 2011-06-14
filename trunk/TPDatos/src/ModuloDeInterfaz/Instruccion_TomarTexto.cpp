/*
 * Instruccion_TomarTexto.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_TomarTexto.h"

Instruccion_TomarTexto::Instruccion_TomarTexto(char id, string pathLibro) :
	Instruccion(id) {
	this->libroNuevo = pathLibro;

}

void Instruccion_TomarTexto::ejecutar() {
	long int idUltimoLibro = 0;
	Configuracion* conf = Configuracion::GetInstancia();

	this->controladorBiblioteca = new ControladorBiblioteca(
			conf->getPathCarpetaTrabajo() + ARCHIVO_BIBLIOTECA + EXTENSION_ARCHIVO_INDICE,
			conf->getPathCarpetaTrabajo() + ARCHIVO_CONTROL_BIBLIOTECA);

	this->controladorIndice = new ControladorIndice(conf->getPathCarpetaTrabajo());

	idUltimoLibro = this->controladorBiblioteca->getSizeBiblioteca();

	this->controladorBiblioteca->ingresarLibro(this->libroNuevo);

	DatoLibro* datoUltimoLibro = new DatoLibro(this->controladorBiblioteca->recuperarLibro(idUltimoLibro));

	Logger::log("Instruccion_TomarTexto", "ejecutar",
			"Se toma el archivo correspondiente.");

	Libro* libroUltimo = new Libro();
	ParserDePalabras* parser = new ParserDePalabras(conf->getPathArchivoStopWords());
	libroUltimo = parser->parsear(datoUltimoLibro);

	pair<Libro*,uint32_t> parLibroOffset;
	parLibroOffset.first	= libroUltimo;
	parLibroOffset.second	= idUltimoLibro;
	controladorIndice->nuevoIndiceOcurrenciaTerminos();
	controladorIndice->indexar(parLibroOffset,INDICE_OCURRENCIA_TERMINOS);

}

Instruccion_TomarTexto::~Instruccion_TomarTexto() {
	delete(controladorIndice);
	delete(controladorBiblioteca);
}
