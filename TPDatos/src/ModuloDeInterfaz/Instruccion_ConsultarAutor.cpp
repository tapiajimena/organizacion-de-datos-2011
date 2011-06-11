/*
 * Instruccion_ConsultarAutor.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ConsultarAutor.h"


Instruccion_ConsultarAutor::Instruccion_ConsultarAutor(char id, string consulta):Instruccion(id)
{
	this->autor = consulta;
}


void Instruccion_ConsultarAutor::ejecutar()
{
	Configuracion* conf = Configuracion::GetInstancia();
	ConsultaIndice* consulta = new ConsultaIndice(conf->getPathCarpetaTrabajo());

	Logger::log("Instruccion_ConsultarAutor", "ejecutar",
			"Se ejecuta la consulta.");

	cout<<"Se devuelven los datos consultados de Autor: "<<endl;
	consulta->consultarAutor(autor);


	Logger::log("Instruccion_ConsultarAutor", "ejecutar",
			"Se devuelve la consulta.");

	delete(consulta);

}

Instruccion_ConsultarAutor::~Instruccion_ConsultarAutor() {
	// TODO Auto-generated destructor stub
}
