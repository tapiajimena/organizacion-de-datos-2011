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

	if(controlBiblioteca->getSizeBiblioteca()>0)
		consultable =true;
	else
		consultable = false;
}

ConsultaIndice::ConsultaIndice(string pathCarpeta)
{
	pathCarpeta = pathCarpeta;
	CrearDirectorios(pathCarpeta);
	controlIndice = new ControladorIndice(pathCarpeta);
	controlBiblioteca = new ControladorBiblioteca(
			pathCarpeta + ARCHIVO_BIBLIOTECA + EXTENSION_ARCHIVO_INDICE,
			pathCarpeta + ARCHIVO_CONTROL_BIBLIOTECA);

	if(controlBiblioteca->getSizeBiblioteca() > 0)
		consultable =true;
	else
		consultable = false;
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


bool ConsultaIndice::validarEsConsultable(char tipoIndice)
{
	list<uint32_t> libros = controlBiblioteca->recuperarLibrosDeBiblioteca();
	this->consultable = false;

	list<uint32_t>::iterator it;
	for(it=libros.begin(); it != libros.end(); ++it)
	{
		list<char>* indexados  = controlBiblioteca->chequearIndexadoSinCarga(*it);

		if (indexados->empty())
			this->consultable = false;
		else
		{
			list<char>::iterator itIndexado;
			for(itIndexado = indexados->begin();itIndexado != indexados->end(); itIndexado++)
			{
				if ((*itIndexado) == tipoIndice)
					this->consultable = true;
			}
		}
	}
	return consultable;
}


bool ConsultaIndice::consultarAutor(string consulta)
{
	Logger::log("ConsultaIndice", "consultarAutor","Se accede al indice.");

	if (validarEsConsultable(INDICE_AUTOR))
	{
		controlIndice->nuevoIndiceAutor();
		controlIndice->consultarPorAutorOEditorial(consulta);
		return true;
	}
	else
		return false;
}

bool ConsultaIndice::consultarEditorial(string consulta)
{
	Logger::log("ConsultaIndice", "consultarEditorial","Se accede al indice.");
	if(validarEsConsultable(INDICE_EDITORIAL))
	{
		controlIndice->nuevoIndiceEditorial();
		controlIndice->consultarPorAutorOEditorial(consulta);
	}
}


bool ConsultaIndice::consultarTitulo(string consulta)
{
	Logger::log("ConsultaIndice", "consultarTitulo","Se accede al indice.");
	if(validarEsConsultable(INDICE_TITULO))
	{
		controlIndice->nuevoIndiceTitulo();
		controlIndice->consultarPorTitulo(consulta);
		return true;
	}
	else
		return false;
}


bool ConsultaIndice::consultarPalabras(string consulta)
{
	/*
	Logger::log("ConsultaIndice", "consultarPalabras","Se accede al indice.");
	if(validarEsConsultable(INDICE_PALABRAS))
	{
		controlIndice->nuevoIndiceOcurrenciaTerminos();
		controlIndice->consultarPorOcurrenciaTerminos(consulta);
		return true;
	}
	else
		return false;
		*/
}

void ConsultaIndice::consultarTerminosProximos(string consulta)
{
	Logger::log("ConsultaIndice", "consultarTerminosProximos","Se accede al indice.");

	cout<<"Datos a consultar: "<<consulta<<endl;

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


bool ConsultaIndice::esConsultable() const
{
    return consultable;
}


void ConsultaIndice::setConsultable(bool consultable)
{
    this->consultable = consultable;
}

ConsultaIndice::~ConsultaIndice()
{
	delete(controlBiblioteca);
	delete(controlIndice);
}






















