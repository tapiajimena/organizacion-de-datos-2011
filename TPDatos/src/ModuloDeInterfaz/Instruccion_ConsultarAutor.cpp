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
	CaseFoldedString caseFold = CaseFoldedString();
	Configuracion* conf = Configuracion::GetInstancia();
	ConsultaIndice* consulta = new ConsultaIndice(conf->getPathCarpetaTrabajo());


	Logger::log("Instruccion_ConsultarAutor", "ejecutar",
			"Se ejecuta la consulta.");

	cout<<"Se ejecuta la consulta de autor "<< this->autor<<": "<<endl;
	if(consulta->esConsultable())
	{
		if (consulta->consultarAutor(caseFold.caseFoldWord(autor)))
			cout<<MENSAJE_CONSULTA_EXITOSA<<endl;
		else
			cout<<MENSAJE_INDICE_NO_CONSULTABLE_BIBLIOTECA_VACIA<<endl;
	}
	else
		cout<<MENSAJE_INDICE_NO_CONSULTABLE_BIBLIOTECA_VACIA<<endl;


	Logger::log("Instruccion_ConsultarAutor", "ejecutar",
			"Se devuelve la consulta.");

	delete(consulta);

}

Instruccion_ConsultarAutor::~Instruccion_ConsultarAutor() {

}
