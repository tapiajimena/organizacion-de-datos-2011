/*
 * Instruccion_ConsultarEditorial.cpp
 *
 *	Editorial	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ConsultarEditorial.h"


Instruccion_ConsultarEditorial::Instruccion_ConsultarEditorial(char id, string consulta):Instruccion(id)
{
	this->editorial = consulta;
}


void Instruccion_ConsultarEditorial::ejecutar()
{
	CaseFoldedString caseFold = CaseFoldedString();
	Configuracion* conf = Configuracion::GetInstancia();
	ConsultaIndice* consulta = new ConsultaIndice(conf->getPathCarpetaTrabajo());

	Logger::log("Instruccion_ConsultarEditorial", "ejecutar",
			"Se ejecuta la consulta.");

	cout<<"Se ejecuta la consulta de editorial "<< editorial<<": "<<endl;
	if(consulta->esConsultable()
			&& (consulta->consultarEditorial(caseFold.caseFoldWord(editorial))))
		cout<<MENSAJE_CONSULTA_EXITOSA<<endl;
	else
		cout<<MENSAJE_INDICE_NO_CONSULTABLE<<endl;



	Logger::log("Instruccion_ConsultarEditorial", "ejecutar",
			"Se devuelve la consulta.");

	delete(consulta);

}

Instruccion_ConsultarEditorial::~Instruccion_ConsultarEditorial() {

}
