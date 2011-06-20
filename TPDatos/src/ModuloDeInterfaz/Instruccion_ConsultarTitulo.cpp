/*
 * Instruccion_ConsultarTitulo.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ConsultarTitulo.h"


Instruccion_ConsultarTitulo::Instruccion_ConsultarTitulo(char id, string consulta):Instruccion(id)
{
	this->titulo = consulta;
}


void Instruccion_ConsultarTitulo::ejecutar()
{
	Configuracion* conf = Configuracion::GetInstancia();
	ConsultaIndice* consulta = new ConsultaIndice(conf->getPathCarpetaTrabajo());

	Logger::log("Instruccion_ConsultarTitulo", "ejecutar",
			"Se ejecuta la consulta.");

	cout<<"Se devuelven los datos consultados de titulo "<<endl;
	consulta->consultarTitulo(titulo);

	Logger::log("Instruccion_ConsultarTitulo", "ejecutar",
			"Se devuelve la consulta.");

	delete(consulta);

}

Instruccion_ConsultarTitulo::~Instruccion_ConsultarTitulo() {

}
