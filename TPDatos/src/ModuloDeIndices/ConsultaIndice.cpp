/*
 * ConsultaIndice.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 * //TODO dar diseño y usar el mismo case que en ConsultaIndice
 * hacer una interfaz IndexableConsultable
 *      
 */

#include "ConsultaIndice.h"

ConsultaIndice::ConsultaIndice()
{
	Configuracion* conf = Configuracion::GetInstancia();
	pathCarpeta = conf->getPathCarpetaTrabajo();
	controlIndice = new ControladorIndice(pathCarpeta);
	controlBiblioteca = new ControladorBiblioteca(
			pathCarpeta + ARCHIVO_BIBLIOTECA + EXTENSION_ARCHIVO_INDICE,
			pathCarpeta + ARCHIVO_CONTROL_BIBLIOTECA);
}

ConsultaIndice::ConsultaIndice(string pathCarpeta)
{
	pathCarpeta = pathCarpeta;
	CrearDirectorios(pathCarpeta);
	controlIndice = new ControladorIndice(pathCarpeta);
	controlBiblioteca = new ControladorBiblioteca(
			pathCarpeta + ARCHIVO_BIBLIOTECA + EXTENSION_ARCHIVO_INDICE,
			pathCarpeta + ARCHIVO_CONTROL_BIBLIOTECA);
}


void ConsultaIndice::crearTipoConsulta(char tipoConsulta, string consulta)
{
	switch(tipoConsulta)
	{
		case CONSULTA_INDICE_AUTOR:
			controlIndice->nuevoIndiceAutor();
			controlIndice->consultarPorAutorOEditorial(consulta);
		break;
		case CONSULTA_INDICE_EDITORIAL:
			controlIndice->nuevoIndiceEditorial();
		break;
		case CONSULTA_INDICE_PALABRAS:
			controlIndice->nuevoIndicePalabras();
		break;
		case CONSULTA_INDICE_TITULO:
			controlIndice->nuevoIndiceTitulo();
		break;
	}
}

void ConsultaIndice::consultarAutor(string consulta)
{
	Logger::log("ConsultaIndice", "consultarAutor","Se accede al indice.");
	controlIndice->nuevoIndiceAutor();
	controlIndice->consultarPorAutorOEditorial(consulta);
}

void ConsultaIndice::consultarEditorial(string consulta)
{
	Logger::log("ConsultaIndice", "consultarEditorial","Se accede al indice.");
	controlIndice->nuevoIndiceEditorial();
	controlIndice->consultarPorAutorOEditorial(consulta);
}


void ConsultaIndice::consultarTitulo(string consulta)
{
	controlIndice->nuevoIndiceTitulo();
	controlIndice->consultarPorTitulo(consulta);
}


void ConsultaIndice::consultarPalabras(string consulta)
{
	controlIndice->nuevoIndiceOcurrenciaTerminos();
	controlIndice->consultarPorOcurrenciaTerminos(consulta);
}

void ConsultaIndice::consultarTerminosProximos(string consulta)
{


	cout<<"Datos a consultar Consulta: "<<consulta<<endl;

	Configuracion* conf = Configuracion::GetInstancia();
	ControladorIndice* control = new ControladorIndice();
	ArchivoTerminos* arc = new ArchivoTerminos(
			conf->getPathCarpetaTrabajo()
					+ ARCHIVO_TERMINOS
					+ EXTENSION_ARCHIVO_INDICE);
	ProcesadorDeRelevancia* proc = new ProcesadorDeRelevancia(control, arc);

	Logger::log("ConsultaIndice", "consultarTerminosProximos","Se realiza la consulta");
	proc->mostrarLibrosRelevantes(consulta);
}


void ConsultaIndice::consultar(char tipoIndice, string consulta)
{
	Libro*					libro;
	DatoLibro*				dLibro;
	list<uint32_t> 			idLibros;
	pair<Libro*,uint32_t>	parLibroOffset;


	crearTipoConsulta(tipoIndice, consulta);

}

void ConsultaIndice::generarReporte(char tipoIndice, string nombreArchivo)
{
	/*
	crearTipoConsulta(tipoIndice);
	this->controlIndice->generarReporte(tipoIndice, nombreArchivo);
	*/

}



ConsultaIndice::~ConsultaIndice()
{
	delete(controlBiblioteca);
	delete(controlIndice);
}






















