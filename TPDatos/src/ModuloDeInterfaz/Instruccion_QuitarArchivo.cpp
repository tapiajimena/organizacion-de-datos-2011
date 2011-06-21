/*
 * Instruccion_QuitarArchivo.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_QuitarArchivo.h"

Instruccion_QuitarArchivo::Instruccion_QuitarArchivo(char id,
		uint32_t idArchivo) :
	Instruccion(id) {
	this->idArchivo = idArchivo;
	cout << "Id Archivo: " << idArchivo << endl;
}

void Instruccion_QuitarArchivo::ejecutar()
{
	Indexador* indexador = new Indexador();
	Configuracion* conf = Configuracion::GetInstancia();
	this->controladorBiblioteca = new ControladorBiblioteca(
			conf->getPathCarpetaTrabajo()+ "/"+ ARCHIVO_BIBLIOTECA + EXTENSION_ARCHIVO_INDICE,
			conf->getPathCarpetaTrabajo()+"/"+ARCHIVO_CONTROL_BIBLIOTECA);
	this->controladorIndice = new ControladorIndice(conf->getPathCarpetaTrabajo());

	if ((controladorBiblioteca->getSizeBiblioteca() > 0)
		&& (!controladorBiblioteca->estaEliminado(this->idArchivo)))
	{
		(controladorIndice->getControladorTriadas())->eliminarLibro(idArchivo);

		//se lo elimina de los indices y biblioteca
		indexador->eliminarIndexado(idArchivo);

		cout<<MENSAJE_QUITAR_ARCHIVO<<endl;
		Logger::log("Instruccion_QuitarArchivo", "ejecutar","Se elimina el archivo.");
	}
	else
		cout<<MENSAJE_LIBRO_NO_EXISTE<<endl;

	delete(indexador);
	delete(controladorIndice);
	delete(controladorBiblioteca);
}

Instruccion_QuitarArchivo::~Instruccion_QuitarArchivo()
{

}
