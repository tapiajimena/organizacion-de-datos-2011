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

	std::string nombreArchivoTablaPesos = this->pathCarpeta + "/TablaIndicePesos.dat";
	std::string nombreArchivoCubetasPesos = this->pathCarpeta + "/CubetasIndicePesos.dat";

	std::string nombreArchivoTablaNormas = this->pathCarpeta + "/TablaIndiceNormas.dat";
	std::string nombreArchivoCubetasNormas = this->pathCarpeta + "/CubetasIndiceNormas.dat";

	//Creamos y cerramos los archivos, por si antes fueron creados. Necesitamos empezar de cero, y el Hash...
	//...está hecho para persistir y recuperar la información que guarda.
	fstream arcTemporal;
	ManejadorArchivo::Crear(nombreArchivoTablaPesos.c_str(), arcTemporal, true);
	ManejadorArchivo::Cerrar(arcTemporal);
	ManejadorArchivo::Crear(nombreArchivoCubetasPesos.c_str(), arcTemporal, true);
	ManejadorArchivo::Cerrar(arcTemporal);
	ManejadorArchivo::Crear(nombreArchivoTablaNormas.c_str(), arcTemporal, true);
	ManejadorArchivo::Cerrar(arcTemporal);
	ManejadorArchivo::Crear(nombreArchivoCubetasNormas.c_str(), arcTemporal, true);
	ManejadorArchivo::Cerrar(arcTemporal);


	this->indicePesosGlobales = new Hash(nombreArchivoTablaPesos, nombreArchivoCubetasPesos);

	this->indiceNormasDocumentos = new Hash(nombreArchivoTablaNormas, nombreArchivoCubetasNormas);

	//this->cantidadTotalDeDocumentos = ???; TODO
	this->controladorDeTriadas = controladorDeTriadas;
	this->controladorIndice = controladorIndice;

	//hash para pesos globales... (crear vacio, pisar archivos viejos).
}

CalculadorDeNormas::~CalculadorDeNormas()
{
	//Los índices quedan en disco por si se quieren ver de alguna manera...
	delete this->indicePesosGlobales;
	delete this->indiceNormasDocumentos;
}

std::vector<DatoTriada> CalculadorDeNormas::levantarTriadasDeTermino(uint32_t idTermino)
{
	std::vector<DatoTriada> ocurrenciasDeTermino;

	//TODO...

	return ocurrenciasDeTermino;
}

void CalculadorDeNormas::generarIndiceDePesosGlobalesDeTerminos()
{
	//iterar sobre los terminos... ver archivoTerminos.
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

	//Es más rápido pedir las ocurrencias del término que levantar todas las tríadas del libro.
	//(salvo que se carguen millones de libros y que haya más ocurrencias del término que palabras en el libro)
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

float CalculadorDeNormas::obtenerPesoGlobalDeIndice(uint32_t idTermino)
{
	float pesoGlobalDeTermino = 0.0;

	unsigned int id = (unsigned int)idTermino;
	std::string claveIndice = ServiceClass::obtenerString(id);

	std::vector<uint32_t> resultadoConsulta;
	resultadoConsulta = this->indicePesosGlobales->buscarPalabraEnHash(claveIndice);

	if( resultadoConsulta.size() == 0)
	{
		//0.0
	}
	else
	{
		if(resultadoConsulta.size() == 1)
		{
			uint32_t enteroLeido = resultadoConsulta.at(0);
			pesoGlobalDeTermino = ServiceClass::uint32tToFloat( enteroLeido );
		}
		else
		{
			std::cout<<"ERROR: multiples pesos globales para el termino"<<idTermino;
			//throw??
		}
	}

	return pesoGlobalDeTermino;
}

float CalculadorDeNormas::obtenerNormaDocumentoDeIndice(uint32_t idDocumento)
{
	float normaDocumento = 0.0;

	unsigned int id = (unsigned int)idDocumento;
	std::string claveIndice = ServiceClass::obtenerString(id);

	std::vector<uint32_t> resultadoConsulta;
	resultadoConsulta = this->indiceNormasDocumentos->buscarPalabraEnHash(claveIndice);

	if( resultadoConsulta.size() == 0)
	{
		//0.0
	}
	else
	{
		if(resultadoConsulta.size() == 1)
		{
			uint32_t enteroLeido = resultadoConsulta.at(0);
			normaDocumento = ServiceClass::uint32tToFloat( enteroLeido );
		}
		else
		{
			std::cout<<"ERROR: multiples normas para el documento"<<normaDocumento;
			//throw??
		}
	}

	return normaDocumento;
}

float CalculadorDeNormas::calcularPesoLocalDeTermino(uint32_t idDocumento, uint32_t idTermino)
{
	int frecuenciaLocal = this->calcularAparicionesDeTerminoEnDocumento(idDocumento, idTermino);

	float pesoGlobal = this->obtenerPesoGlobalDeIndice(idTermino);

	float normaDocumento = this->obtenerNormaDocumentoDeIndice(idDocumento);

	return frecuenciaLocal*pesoGlobal/normaDocumento;
}

float CalculadorDeNormas::calcularNormaDeDocumento(uint32_t idDocumento)
{
	//Ya tienen que estar cargados los pesos globales de términos, se consulta en vez de recalcular.

	//Este vector guarda todos los términos del documento, sin importar la cantidad de ocurrencias de los mismos.
	std::vector<uint32_t> listaIdTerminosDeDocumento; //TODO cargar listaIdTerminosDeDocumento...

	//Anotamos los términos ya procesados, para procesarlos una sola vez
	std::vector<uint32_t> terminosYaProcesados;

	std::vector<uint32_t>::iterator it_terminos;

	std::vector<uint32_t>::iterator it_terminosYaProcesados;

	float sumatoriaParcial = 0.0;

	for(it_terminos = listaIdTerminosDeDocumento.begin(); it_terminos != listaIdTerminosDeDocumento.end(); it_terminos++)
	{
		bool terminoYaProcesado = false;

		for( it_terminosYaProcesados = terminosYaProcesados.begin();
			 it_terminosYaProcesados != terminosYaProcesados.end() && !terminoYaProcesado;
			 it_terminosYaProcesados++)
		{
			if( *it_terminosYaProcesados == *it_terminos)
			{
				terminoYaProcesado = true;
			}
		}

		if (!terminoYaProcesado)
		{
			float pesoGlobalTermino = this->obtenerPesoGlobalDeIndice(*it_terminos);

			int frecuenciaLocalDeTermino = this->calcularAparicionesDeTerminoEnDocumento(idDocumento, *it_terminos);

			sumatoriaParcial = sumatoriaParcial +  frecuenciaLocalDeTermino * pow(pesoGlobalTermino, 2);
		}
	}

	return sqrt(sumatoriaParcial);
}

float CalculadorDeNormas::calcularNormaConsulta(std::string consulta)
{

}

float CalculadorDeNormas::calcularProductoInterno(uint32_t idDocumento, std::string consulta)
{

}

float CalculadorDeNormas::calcularSimilitudConsultaDocumento(uint32_t idDocumento, std::vector<std::string> consulta)
{
	//float productoInterno = this->calcularProductoInterno(idDocumento, consulta);
	//float productoDeNormas = this->obtenerNormaDocumento(idDocumento) * this->obtenerNormaConsulta(consulta);

	//return productoInterno / productoDeNormas;
}
