/*
 * Instruccion_ConsultaNormaInfinito.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ConsultarNormaInfinito.h"


Instruccion_ConsultaNormaInfinito::Instruccion_ConsultaNormaInfinito(char id, string consulta):Instruccion(id)
{
	this->titulo = consulta;
}


void Instruccion_ConsultaNormaInfinito::ejecutar()
{
	Configuracion* conf = Configuracion::GetInstancia();
	ControladorIndice* control = new ControladorIndice();

	control->nuevoIndiceOcurrenciaTerminos();
	control->generarReporte(CONSULTA_INDICE_TERMINOS,"IndiceTerminos");

	cout<<"Se genero el archivo de consulta de Normas Infinitas"<<endl;
}

Instruccion_ConsultaNormaInfinito::~Instruccion_ConsultaNormaInfinito() {

}
