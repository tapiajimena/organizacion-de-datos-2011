/*
 * CalculadorDeNormas.cpp
 *
 *  Created on: 14/06/2011
 *      Author: santi
 */

#include "CalculadorDeNormas.h"

CalculadorDeNormas::CalculadorDeNormas(ControladorIndice* controladorIndice, ArchivoTerminos* archivoTerminos)
{
	Configuracion* conf = Configuracion::GetInstancia();
	this->pathCarpeta = conf->getPathCarpetaTrabajo();

	this->cantidadTotalDeDocumentos = 0; //Se carga al calcular pesos globales.

	//this->controladorDeTriadas = controladorDeTriadas;
	this->controladorIndice = controladorIndice;
	this->archivoTerminos = archivoTerminos;

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

}

CalculadorDeNormas::~CalculadorDeNormas()
{
	//Los índices quedan en disco por si se quieren ver de alguna manera...
	delete this->indicePesosGlobales;
	delete this->indiceNormasDocumentos;

	//No destruye el resto de las estructuras, porque no le pertenecen.
}

std::list<DatoTriada*>* CalculadorDeNormas::levantarTriadasDeTermino(uint32_t idTermino)
{
	//Esto es un acceso directo al archivo a traves de su offset-Id.
	std::string palabra = this->archivoTerminos->obtenerTermino(idTermino);

	return this->controladorIndice->recuperarTriadas(palabra);
}

void CalculadorDeNormas::generarIndiceDePesosGlobalesDeTerminos()
{
	std::vector<std::pair<std::string, uint32_t> > listaTerminos = this->archivoTerminos->obtenerTerminos();

	std::vector<std::pair<std::string, uint32_t> >::iterator it_terminos;

	float pesoGlobalTermino;

	for(it_terminos = listaTerminos.begin(); it_terminos != listaTerminos.end(); it_terminos++)
	{
		//calculamos el peso global...
		pesoGlobalTermino = this->calcularPesoGlobalDeTermino((*it_terminos).second);//por id de termino.

		//y lo guardamos en el indice...
		this->indicePesosGlobales->insertarClave(*it_terminos);
	}

	this->cantidadTotalDeDocumentos = listaTerminos.size();

}

int CalculadorDeNormas::calcularDocumentosQueContienenTermino(uint32_t idTermino)
{
	int documentosQueContienenTermino = 0;

	std::list<DatoTriada*>* ocurrenciasDeTermino = this->levantarTriadasDeTermino(idTermino);

	//En este vector se guardan los libros en que aparece el término. La idea es no contar
	//dos ocurrencias si son del mismo documento, ya que interesa la cantidad de DOCUMENTOS
	//que contienen alguna vez al término.
	std::vector<uint32_t> documentosYaVisitados;

	std::list<DatoTriada*>::iterator it_triadas;

	std::vector<uint32_t>::iterator it_documentos;

	bool documentoYaVisitado;

	for(it_triadas = ocurrenciasDeTermino->begin();
		it_triadas != ocurrenciasDeTermino->end();
		it_triadas++)
	{
		documentoYaVisitado = false;

		//Si el documento de la ocurrencia no fue ya visitado, se cuenta la ocurrencia y
		//se agrega el documento como visitado, si no, se ignora la ocurrencia.
		for(it_documentos = documentosYaVisitados.begin();
			it_documentos != documentosYaVisitados.end() && !documentoYaVisitado;
			it_documentos++)
		{
			if((*it_triadas)->getIdLibro() == *it_documentos)
			{
				documentoYaVisitado = true;
			}
		}

		if(!documentoYaVisitado)
		{
			documentosQueContienenTermino++;
			documentosYaVisitados.push_back((*it_triadas)->getIdLibro());
		}
	}

	//TODO ver si antes de eliminar vector hay que eliminar manualmente todos los elementos DatoTriada
	delete ocurrenciasDeTermino;

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
	std::list<DatoTriada*>* ocurrenciasDeTermino = this->levantarTriadasDeTermino(idTermino);

	std::list<DatoTriada*>::iterator it_ocurrencias;

	for(it_ocurrencias = ocurrenciasDeTermino->begin();
		it_ocurrencias != ocurrenciasDeTermino->end();
		it_ocurrencias++)
	{
		if((*it_ocurrencias)->getIdLibro() == idDocumento)
		{
			ocurrenciasDeTerminoEnDocumento++;
		}
	}

	//TODO ver si antes de eliminar vector hay que eliminar manualmente todos los elementos DatoTriada
	delete ocurrenciasDeTermino;

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

//Depretated... se usa calcular la norma sobre el VectorDeDocumento, no sobre idTermino.
/*
float CalculadorDeNormas::calcularNormaDeDocumento(uint32_t idDocumento)
{

	//Ya tienen que estar cargados los pesos globales de términos, se consulta en vez de recalcular.

	//Este vector guarda todos los términos del documento, sin importar la cantidad de ocurrencias de los mismos.
	//Falta cargar listaIdTerminosDeDocumento... (consultar Arbol)
	std::vector<uint32_t> listaIdTerminosDeDocumento;

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
*/

VectorDeDocumento* CalculadorDeNormas::cargarVectorDeTerminos(uint32_t idDocumento)
{
	std::list<DatoTriada*>* listaDatoTriadas = this->controladorIndice->getControladorTriadas()->getTriadas(idDocumento);

	std::list<DatoTriada*>::iterator it_datosTriada;

	VectorDeDocumento* listaTerminosEnDocumento = new VectorDeDocumento();

	for( it_datosTriada = listaDatoTriadas->begin(); it_datosTriada != listaDatoTriadas->end(); it_datosTriada++)
	{
		if( listaTerminosEnDocumento->find((*it_datosTriada)->getIdTermino()) != listaTerminosEnDocumento->end())
		{
			(*listaTerminosEnDocumento)[(*it_datosTriada)->getIdTermino()]++;
		}
		else
		{
			(*listaTerminosEnDocumento)[(*it_datosTriada)->getIdTermino()] = 1;
		}
	}

	return listaTerminosEnDocumento;
}

VectorDeDocumento* CalculadorDeNormas::cargarVectorDeTerminos(std::list<uint32_t> ocurrenciasDeTerminos)
{
	VectorDeDocumento* vectorConsulta = new VectorDeDocumento();

	std::list<uint32_t>::iterator it_terminos;

	for(it_terminos = ocurrenciasDeTerminos.begin(); it_terminos != ocurrenciasDeTerminos.end(); it_terminos++)
	{
		if( vectorConsulta->find(*it_terminos) != vectorConsulta->end())
		{
			(*vectorConsulta)[*it_terminos]++;
		}
		else
		{
			(*vectorConsulta)[*it_terminos] = 1;
		}
	}

	return vectorConsulta;
}

float CalculadorDeNormas::calcularNormaVectorDeTerminos(VectorDeDocumento* vectorDeTerminos)
{
	VectorDeDocumento::iterator it_vector;

	float normaDocumento = 0.0; //normaDocumento = sqrt(sumatoriaCuadradaParcial)
	float sumatoriaCuadradaParcial = 0.0; //sumatoriaCuadradaParcial = (pesoDeTerminoEnDocumento)^2
	float pesoDeTerminoEnDocumento = 0.0; // pesoDeTerminoEnDocumento = [aparicionesTermino] * pesoGlobalTermino

	for(it_vector = vectorDeTerminos->begin(); it_vector != vectorDeTerminos->end(); it_vector++)
	{
		//peso de termino en documento = cantidad de apariciones * peso global del termino.
		pesoDeTerminoEnDocumento = (*it_vector).second * this->obtenerPesoGlobalDeIndice((*it_vector).first);

		sumatoriaCuadradaParcial = sumatoriaCuadradaParcial + pow(pesoDeTerminoEnDocumento, 2);
	}

	normaDocumento = sqrt(sumatoriaCuadradaParcial);

	return normaDocumento;
}

float CalculadorDeNormas::calcularProductoInterno(VectorDeDocumento* vectorDocumento1, VectorDeDocumento* vectorDocumento2)
{
	//iteraremos sobre el mas corto de los dos vectores (la consulta tipicamente)
	VectorDeDocumento* vectorDocumento;
	VectorDeDocumento* vectorConsulta;

	if( vectorDocumento1->size() > vectorDocumento2->size())
	{
		vectorDocumento = vectorDocumento1;
		vectorConsulta = vectorDocumento2;
	}
	else
	{
		vectorDocumento = vectorDocumento2;
		vectorConsulta = vectorDocumento1;
	}

	//Se multiplican los multiplos de los terminos que aparecen tanto en la consulta como en le documento.
	//El resto de los teminos dan cero en el P.I. Canonico.
	float productoInterno = 0.0;

	VectorDeDocumento::iterator it_consulta;
	for(it_consulta = vectorConsulta->begin(); it_consulta != vectorConsulta->end(); it_consulta++)
	{
		if( vectorDocumento->find(it_consulta->first) != vectorDocumento->end())
		{
			productoInterno = productoInterno + it_consulta->second * (vectorDocumento->find(it_consulta->first)->second);
		}
	}

	return productoInterno;
}

void CalculadorDeNormas::generarArchivoDeNormasDeDocumentos()
{
//para cada documento, calcular norma e ingresar al hash.
	//std::string idDocumetoStr = ServiceClass::obtenerString(idDocumento);
	//std::pair<std::string, uint32_t> claveNormaDocumentoHash;
	//this->indiceNormasDocumentos->insertarClave(claveNormaDocumentoHash);
}

float CalculadorDeNormas::calcularSimilitudConsultaDocumento(uint32_t idDocumento, std::list<uint32_t> consulta)
{
	VectorDeDocumento* vectorConsulta = this->cargarVectorDeTerminos(consulta);

	VectorDeDocumento* vectorDocumento = this->cargarVectorDeTerminos(idDocumento);

	float productoInterno = this->calcularProductoInterno(vectorDocumento, vectorConsulta);

	//La norma del documento la leemos del indice, para ahorrar accesos a disco.
	float productoDeNormas = this->obtenerNormaDocumentoDeIndice(idDocumento) * this->calcularNormaVectorDeTerminos(vectorConsulta);

	delete vectorConsulta;
	delete vectorDocumento;

	return productoInterno / productoDeNormas;
}
