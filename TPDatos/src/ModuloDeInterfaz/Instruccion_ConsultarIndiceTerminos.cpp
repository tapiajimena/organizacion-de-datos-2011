/*
 * Instruccion_ConsultarTerminosProximos.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ConsultarIndiceTerminos.h"


Instruccion_ConsultarIndiceTerminos::Instruccion_ConsultarIndiceTerminos(char id, string consulta):Instruccion(id)
{
	this->titulo = consulta;
}


void Instruccion_ConsultarIndiceTerminos::ejecutar()
{
	Configuracion* conf = Configuracion::GetInstancia();
	ControladorIndice* control = new ControladorIndice();

	control->nuevoIndiceOcurrenciaTerminos();
	control->generarReporte(CONSULTA_INDICE_TERMINOS,"IndiceTerminos");

	cout<<"Se genera el reporte de Listas invertidas"<<endl;

	delete(control);
}

Instruccion_ConsultarIndiceTerminos::~Instruccion_ConsultarIndiceTerminos() {

}
