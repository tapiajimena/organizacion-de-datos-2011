/*
 * Instruccion_ConsultarTerminosProximos.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ConsultarOcurrenciaPosicional.h"


Instruccion_ConsultarOcurrenciaPosicional::Instruccion_ConsultarOcurrenciaPosicional(char id, string consulta):Instruccion(id)
{
	this->titulo = consulta;
}


void Instruccion_ConsultarOcurrenciaPosicional::ejecutar()
{
	Configuracion* conf = Configuracion::GetInstancia();
	ControladorIndice* control = new ControladorIndice();

	//cout <<this->titulo<<endl;
	cout << "Procesando ocurrencias de terminos, esto puede demorar unos pocos minutos, aguarde por favor..."<<endl;
	control->mostrarTriadas( this->titulo );
	delete(control);

}

Instruccion_ConsultarOcurrenciaPosicional::~Instruccion_ConsultarOcurrenciaPosicional() {

}
