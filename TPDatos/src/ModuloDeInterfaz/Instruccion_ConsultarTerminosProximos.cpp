/*
 * Instruccion_ConsultarTerminosProximos.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ConsultarTerminosProximos.h"


Instruccion_ConsultarTerminosProximos::Instruccion_ConsultarTerminosProximos(char id, string consulta):Instruccion(id)
{
	this->titulo = consulta;
}


void Instruccion_ConsultarTerminosProximos::ejecutar()
{
	Configuracion* conf = Configuracion::GetInstancia();
	ConsultaIndice* consulta = new ConsultaIndice(conf->getPathCarpetaTrabajo());

	Logger::log("Instruccion_ConsultarTerminosProximos", "ejecutar",
			"Se ejecuta la consulta.");

	cout<<"Se devuelven los datos consultados de titulo "<<endl;
	consulta->consultarPalabras(titulo);

	Logger::log("Instruccion_ConsultarTerminosProximos", "ejecutar",
			"Se devuelve la consulta.");

	delete(consulta);

}

Instruccion_ConsultarTerminosProximos::~Instruccion_ConsultarTerminosProximos() {

}
