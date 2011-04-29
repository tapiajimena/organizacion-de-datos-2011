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
	cout << "idArchivo: " << idArchivo << endl;
}

void Instruccion_QuitarArchivo::ejecutar() {
	Configuracion* conf = Configuracion::GetInstancia();
	this->controladorBiblioteca = new ControladorBiblioteca(
			conf->getPathCarpetaTrabajo() + "/" + ARCHIVO_BIBLIOTECA,
			conf->getPathCarpetaTrabajo() + "/" + ARCHIVO_CONTROL_BIBLIOTECA);

	bool exito = this->controladorBiblioteca->eliminarLibro(this->idArchivo);

	if (exito) {
		Logger::log("Instruccion_QuitarArchivo", "ejecutar",
				"Se elimina el archivo.");
	} else {
		Logger::log("Instruccion_QuitarArchivo", "ejecutar",
				"No se pudo eliminar el archivo.");
	}

}

Instruccion_QuitarArchivo::~Instruccion_QuitarArchivo() {
	// TODO Auto-generated destructor stub
}
