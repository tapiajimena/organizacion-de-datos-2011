/*
 * CalculadorDeNormas.cpp
 *
 *  Created on: 14/06/2011
 *      Author: santi
 */

#include "CalculadorDeNormas.h"

CalculadorDeNormas::CalculadorDeNormas(ControladorIndice* controladorIndice, ControladorTriadas* controladorDeTriadas)
{
	Configuracion* conf = Configuracion::GetInstancia();
	this->pathCarpeta = conf->getPathCarpetaTrabajo();
	this->controladorDeTriadas = controladorDeTriadas;
	this->controladorIndice = controladorIndice;
}

CalculadorDeNormas::~CalculadorDeNormas()
{
	//no destruye las estructuras que usa.
}

std::vector<DatoTriada> CalculadorDeNormas::levantarTriadasDeTermino(uint32_t idTermino)
{
	std::vector<DatoTriada> ocurrenciasDeTermino;

	//TODO...

	return ocurrenciasDeTermino;
}

int CalculadorDeNormas::calcularDocumentosQueContienenTermino(uint32_t idTermino)
{
	int documentosQueContienenTermino = 0;

	std::vector<DatoTriada> ocurrenciasDeTermino = this->levantarTriadasDeTermino(idTermino);

	//En este vector se guardan los libros en que aparece el término. La idea es no contar
	//dos ocurrencias si son del mismo documento, ya que interesa la cantidad de DOCUMENTOS
	//que contienen alguna vez al término.
	std::vector<uint32_t> documentosYaVisitados;

	std::vector<DatoTriada>::iterator it_triadas;

	std::vector<uint32_t>::iterator it_documentos;

	bool documentoYaVisitado;

	for(it_triadas = ocurrenciasDeTermino.begin();
		it_triadas != ocurrenciasDeTermino.end();
		it_triadas++)
	{
		documentoYaVisitado = false;

		//Si el documento de la ocurrencia no fue ya visitado, se cuenta la ocurrencia y
		//se agrega el documento como visitado, si no, se ignora la ocurrencia.
		for(it_documentos = documentosYaVisitados.begin();
			it_documentos != documentosYaVisitados.end() && !documentoYaVisitado;
			it_documentos++)
		{
			if(it_triadas->getIdLibro() == *it_documentos)
			{
				documentoYaVisitado = true;
			}
		}

		if(!documentoYaVisitado)
		{
			documentosQueContienenTermino++;
			documentosYaVisitados.push_back(it_triadas->getIdLibro());
		}
	}

	return documentosQueContienenTermino;
}

float CalculadorDeNormas::calcularPesoGlobalDeTermino(uint32_t idTermino)
{
	float pesoGlobal = 0.0;

	int frecuenciaGlobalDeTermino = this->calcularDocumentosQueContienenTermino(idTermino);

	if(frecuenciaGlobalDeTermino != 0)
	{
		pesoGlobal = log10( (float)(this->cantidadTotalDeDocumentos / frecuenciaGlobalDeTermino));
	}

	return pesoGlobal;
}

int CalculadorDeNormas::calcularAparicionesDeTerminoEnDocumento(uint32_t idDocumento, uint32_t idTermino)
{
	int ocurrenciasDeTerminoEnDocumento = 0;

	std::vector<DatoTriada> ocurrenciasDeTermino = this->levantarTriadasDeTermino(idTermino);

	std::vector<DatoTriada>::iterator it_ocurrencias;

	for(it_ocurrencias = ocurrenciasDeTermino.begin();
		it_ocurrencias != ocurrenciasDeTermino.end();
		it_ocurrencias++)
	{
		if(it_ocurrencias->getIdLibro() == idDocumento)
		{
			ocurrenciasDeTerminoEnDocumento++;
		}
	}

	return ocurrenciasDeTerminoEnDocumento;
}

float CalculadorDeNormas::calcularPesoLocalDeTermino(uint32_t idDocumento, uint32_t idTermino)
{
	int frecuenciaLocal = this->calcularAparicionesDeTerminoEnDocumento(idDocumento, idTermino);

	float pesoGlobal; //TODO ...estructura???

	float normaDocumento; //TODO ...???

	return frecuenciaLocal*pesoGlobal/normaDocumento;
}

float CalculadorDeNormas::calcularNormaDeDocumento(uint32_t idDocumento)
{

}

float CalculadorDeNormas::calcularProductoInterno(uint32_t idDocumento, std::string consulta)
{

}

float CalculadorDeNormas::obtenerNormaDocumento(uint32_t idDocumento)
{

}

float CalculadorDeNormas::obtenerNormaConsulta(std::string consulta)
{

}

float CalculadorDeNormas::calcularSimilitudConsultaDocumento(uint32_t idDocumento, std::vector<std::string> consulta)
{
	//float productoInterno = this->calcularProductoInterno(idDocumento, consulta);
	//float productoDeNormas = this->obtenerNormaDocumento(idDocumento) * this->obtenerNormaConsulta(consulta);

	//return productoInterno / productoDeNormas;
}
