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
	uint32_t idLibroAsignado = 0;

	Configuracion* conf = Configuracion::GetInstancia();

	this->controladorBiblioteca = new ControladorBiblioteca(
			conf->getPathCarpetaTrabajo() + ARCHIVO_BIBLIOTECA + EXTENSION_ARCHIVO_INDICE,
			conf->getPathCarpetaTrabajo() + ARCHIVO_CONTROL_BIBLIOTECA);

	this->controladorIndice = new ControladorIndice(conf->getPathCarpetaTrabajo());

	idUltimoLibro = this->controladorBiblioteca->getSizeBiblioteca();

	idLibroAsignado = this->controladorBiblioteca->ingresarLibro(this->libroNuevo);

	if (controladorBiblioteca->existeLibro)
	{
		DatoLibro* datoUltimoLibro = new DatoLibro(this->controladorBiblioteca->recuperarLibro(idLibroAsignado));

		Logger::log("Instruccion_TomarTexto", "ejecutar",
				"Se toma el archivo correspondiente.");

		Libro* libroUltimo = new Libro();
		ParserDeOcurrenciasDeTerminos* parser = new ParserDeOcurrenciasDeTerminos(conf->getPathArchivoStopWords());
		libroUltimo = parser->parsear(datoUltimoLibro);

		pair<Libro*,uint32_t> parLibroOffset;
		parLibroOffset.first	= libroUltimo;
		parLibroOffset.second	= idLibroAsignado;
		controladorIndice->nuevoIndiceOcurrenciaTerminos();
		controladorIndice->indexar(parLibroOffset,INDICE_OCURRENCIA_TERMINOS);

		cout<<"Por favor espere, el procedimiento puede demorar."<<endl;

		ControladorIndice* controlIndiceAux = new ControladorIndice(conf->getPathCarpetaTrabajo());
		ArchivoTerminos* archivoTerminos = new ArchivoTerminos(conf->getPathCarpetaTrabajo()
																+ ARCHIVO_TERMINOS
																+ EXTENSION_ARCHIVO_INDICE);

		controlIndiceAux->nuevoIndiceOcurrenciaTerminos();
		CalculadorDeNormas* calculadorDeNormas = new CalculadorDeNormas(controlIndiceAux,archivoTerminos);
		calculadorDeNormas->generarArchivoDeNormasDeDocumentos();

		delete controlIndiceAux;
		delete(archivoTerminos);
		delete(calculadorDeNormas);
	}

	delete(controladorIndice);
	delete(controladorBiblioteca);

}

Instruccion_TomarTexto::~Instruccion_TomarTexto() {

}
