/*
 * CalculadorDeNormas.cpp
 *
 *  Created on: 14/06/2011
 *      Author: santi
 */

#include "CalculadorDeNormas.h"

CalculadorDeNormas::CalculadorDeNormas() {
	Configuracion* conf = Configuracion::GetInstancia();
	this->pathCarpeta = conf->getPathCarpetaTrabajo();

	//TODO obtener...
	//...archivo de triadas
	//...puntero al arbol de terminos para acceder a las triadas.
}

CalculadorDeNormas::~CalculadorDeNormas() {
}

int CalculadorDeNormas::calcularDocumentosQueContienenTermino(uint32_t idTermino)
{

}

int CalculadorDeNormas::calcularAparicionesDeTerminoEnDocumento(uint32_t idDocumento, uint32_t idTermino)
{

}

int CalculadorDeNormas::calcularNormaDeDocumeto(uint32_t idDocumento)
{

}

float CalculadorDeNormas::calcularSimilitudConsultaDocumento(uint32_t idDocumento, std::vector<std::string> consulta)
{

}
