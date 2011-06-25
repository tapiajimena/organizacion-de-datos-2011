/*
 *
 * CalculadorDeNormas.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 */

#include "CalculadorDeNormas.h"

CalculadorDeNormas::CalculadorDeNormas(ControladorIndice* controladorIndice, ArchivoTerminos* archivoTerminos)
{
	Configuracion* conf = Configuracion::GetInstancia();
	this->pathCarpeta = conf->getPathCarpetaTrabajo();

	this->controladorIndice = controladorIndice;
	this->archivoTerminos = archivoTerminos;

	this->cantidadTotalDeDocumentos = this->controladorIndice->getControladorTriadas()->getLibrosAlmacenados()->size();

	this->nombreArchivoTablaPesos = this->pathCarpeta + "TablaIndicePesos.dat";
	this->nombreArchivoCubetasPesos = this->pathCarpeta + "CubetasIndicePesos.dat";

	this->nombreArchivoTablaNormas = this->pathCarpeta + "TablaIndiceNormas.dat";
	this->nombreArchivoCubetasNormas = this->pathCarpeta + "CubetasIndiceNormas.dat";

	//Levantamos los indices
	this->indicePesosGlobales = new Hash(this->nombreArchivoTablaPesos, this->nombreArchivoCubetasPesos);
	this->indiceNormasDocumentos = new Hash(this->nombreArchivoTablaNormas, this->nombreArchivoCubetasNormas);

	this->listaTerminos = this->archivoTerminos->obtenerTerminos();

}

void CalculadorDeNormas::reiniciarIndices()
{
	//Creamos y cerramos los archivos, por si antes fueron creados. Necesitamos empezar de cero, y el Hash...
	//...est� hecho para persistir y recuperar la informaci�n que guarda.
	delete this->indiceNormasDocumentos;
	delete this->indicePesosGlobales;

	fstream arcTemporal;
	ManejadorArchivo::Crear(this->nombreArchivoTablaPesos.c_str(), arcTemporal, true);
	ManejadorArchivo::Cerrar(arcTemporal);
	ManejadorArchivo::Crear(this->nombreArchivoCubetasPesos.c_str(), arcTemporal, true);
	ManejadorArchivo::Cerrar(arcTemporal);
	ManejadorArchivo::Crear(this->nombreArchivoTablaNormas.c_str(), arcTemporal, true);
	ManejadorArchivo::Cerrar(arcTemporal);
	ManejadorArchivo::Crear(this->nombreArchivoCubetasNormas.c_str(), arcTemporal, true);
	ManejadorArchivo::Cerrar(arcTemporal);

	this->indicePesosGlobales = new Hash(nombreArchivoTablaPesos, nombreArchivoCubetasPesos);

	this->indiceNormasDocumentos = new Hash(nombreArchivoTablaNormas, nombreArchivoCubetasNormas);
}

CalculadorDeNormas::~CalculadorDeNormas()
{
	//Los �ndices quedan en disco por si se quieren ver de alguna manera...
	delete this->indicePesosGlobales;
	delete this->indiceNormasDocumentos;

	//No destruye el resto de las estructuras, porque no le pertenecen.
}

std::list<DatoTriada*>* CalculadorDeNormas::levantarTriadasDeTermino(uint32_t idTermino)
{

	//std::cout<<"levantando idTermino"<<std::endl;
	//Esto es un acceso directo al archivo a traves de su offset-Id.
	std::string palabra = this->archivoTerminos->obtenerTermino(idTermino);

	//std::cout<<"Palabra de Termino: "<<palabra<<std::endl;

	//std::cout<<"Llamo a... this->controladorIndice->recuperarTriadas(palabra)..."<<std::endl;
	//Carga posta de triadas:
	std::list<DatoTriada*>* listaTriadas = this->controladorIndice->recuperarTriadas(palabra);

	//std::cout<<"Recupero listaTriadas..."<<std::endl;

	return listaTriadas;
}

void CalculadorDeNormas::generarIndiceDePesosGlobalesDeTerminos()
{
	std::vector<std::pair<std::string, uint32_t> >::iterator it_terminos;

	float pesoGlobalTermino;

	std::pair<std::string, uint32_t> parIdTerminoPesoGlobal;

	for(it_terminos = this->listaTerminos.begin(); it_terminos != this->listaTerminos.end(); it_terminos++)
	{

		//calculamos el peso global...
		pesoGlobalTermino = this->calcularPesoGlobalDeTermino((*it_terminos).second);//por id de termino.

		//std::cout<<"Termino: '"<<(*it_terminos).first<<"' con ID "<<(*it_terminos).second<<" Tiene Peso Global: "<<pesoGlobalTermino<<std::endl;
		//La clave en el indice es el ID de termino pero pasado a string.
		parIdTerminoPesoGlobal.first = ServiceClass::obtenerString((*it_terminos).second);

		//Guardamos el peso global con dos decimales en un entero. Al recuperar, se debe volver a correr la coma.
		int pesoTerminoConDosDecimales = ServiceClass::floatToUint32t(pesoGlobalTermino);
		parIdTerminoPesoGlobal.second = pesoTerminoConDosDecimales;

		//y lo guardamos en el indice...
		this->indicePesosGlobales->insertarClave(parIdTerminoPesoGlobal);
	}

	this->cantidadTotalDeDocumentos = this->listaTerminos.size();

}

int CalculadorDeNormas::calcularDocumentosQueContienenTermino(uint32_t idTermino)
{
	int documentosQueContienenTermino = 0;

	//std::cout<<" entrando a levantarTriadasDeTermino..."<<std::endl;
	std::list<DatoTriada*>* ocurrenciasDeTermino = this->levantarTriadasDeTermino(idTermino);
	//std::cout<<"Salio de levantarTriadasDeTermino"<<std::endl;

	//En este vector se guardan los libros en que aparece el t�rmino. La idea es no contar
	//dos ocurrencias si son del mismo documento, ya que interesa la cantidad de DOCUMENTOS
	//que contienen alguna vez al t�rmino.
	std::vector<uint32_t> documentosYaVisitados;

	std::list<DatoTriada*>::iterator it_triadas;

	std::vector<uint32_t>::iterator it_documentos;

	bool documentoYaVisitado = false;

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

	return documentosQueContienenTermino;
}

float CalculadorDeNormas::calcularPesoGlobalDeTermino(uint32_t idTermino)
{
	float pesoGlobal = 0.0;

	//std::cout<<"entrando a calcularDocumentosQueContienenTermino"<<std::endl;
	float frecuenciaGlobalDeTermino = this->calcularDocumentosQueContienenTermino(idTermino);

	//std::cout<<"Frec. global de termino: "<< frecuenciaGlobalDeTermino<<std::endl;
	//std::cout<<"cantidad docs: "<< this->cantidadTotalDeDocumentos<<std::endl;

	if(frecuenciaGlobalDeTermino != 0)
	{
		pesoGlobal = log10( (float)(this->cantidadTotalDeDocumentos) / frecuenciaGlobalDeTermino);
	}

	std::cout<<"Peso Global: "<< pesoGlobal<<std::endl;

	return pesoGlobal;
}

int CalculadorDeNormas::calcularAparicionesDeTerminoEnDocumento(uint32_t idDocumento, uint32_t idTermino)
{
	int ocurrenciasDeTerminoEnDocumento = 0;

	//Es m�s r�pido pedir las ocurrencias del t�rmino que levantar todas las tr�adas del libro.
	//(salvo que se carguen millones de libros y que haya m�s ocurrencias del t�rmino que palabras en el libro)

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

	/*while (!ocurrenciasDeTermino->empty())
	{
		delete ocurrenciasDeTermino->back();
		ocurrenciasDeTermino->pop_back();
	}
	delete ocurrenciasDeTermino;
*/
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

	if(resultadoConsulta.size() == 1)
		{
			uint32_t enteroLeido = resultadoConsulta.at(0);
			normaDocumento = ServiceClass::uint32tToFloat( enteroLeido );
		}
		else
		{
			std::cout<<"Atencion: multiples normas para el documento"<<normaDocumento;
			//throw??
		}

	return normaDocumento;
}

float CalculadorDeNormas::calcularPesoLocalDeTermino(uint32_t idDocumento, uint32_t idTermino)
{
	int frecuenciaLocal = this->calcularAparicionesDeTerminoEnDocumento(idDocumento, idTermino);

	float pesoGlobal = this->obtenerPesoGlobalDeIndice(idTermino);

	return frecuenciaLocal*pesoGlobal;
}

VectorDeDocumento* CalculadorDeNormas::cargarVectorDeTerminos(uint32_t idDocumento)
{

	std::list<DatoTriada*>* listaDatoTriadas = this->controladorIndice->getControladorTriadas()->getTriadas(idDocumento);

	std::list<DatoTriada*>::iterator it;
	std::list<DatoTriada*>::iterator it_datosTriada;

	VectorDeDocumento* listaTerminosEnDocumento = new VectorDeDocumento();

	//Cargamos frecuencias locales en el vector.
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

	//Ahora a la frecuencia local se le pondera el peso global del termino.
	this->ponderarPesoLocal(listaTerminosEnDocumento);

	//listaDatoTriadas: de liberar este recurso se ocupa la clase ControladorTriadas.

	return listaTerminosEnDocumento;
}

bool CalculadorDeNormas::buscarTerminoEnBiblioteca(string termino, uint32_t &idTermino)
{
	bool encontrado = false;

	std::vector<std::pair<string, uint32_t> >::iterator it_terminos;

	for( it_terminos = this->listaTerminos.begin();
		 it_terminos != this->listaTerminos.end() && !encontrado;
		 it_terminos++)
	{
		if ( termino == (*it_terminos).first)
		{
			encontrado = true;
			idTermino = (*it_terminos).second;
		}
	}
	return encontrado;
}

VectorDeDocumento* CalculadorDeNormas::cargarVectorDeTerminos(std::list<Termino*>* listaTerminos)
{
	VectorDeDocumento* vectorConsulta = new VectorDeDocumento(); //se retorna esto.

	std::list<Termino*>::iterator it_terminos;

	std::vector<uint32_t> listaIdTerminos;
	uint32_t idTermino;

	for(it_terminos = listaTerminos->begin(); it_terminos != listaTerminos->end(); it_terminos++)
	{
		string cadenaTermino = (*it_terminos)->obtenerNombre();

		idTermino = 0; //Si el termino no existe en la biblioteca se omite este valor.

		if (this->buscarTerminoEnBiblioteca(cadenaTermino, idTermino))
		{
			//uint32_t idTermino = this->obtenerIdTermino(); idTermino ya cargado...

			string idTerminoString = ServiceClass::obtenerString( idTermino );

			listaIdTerminos = this->indicePesosGlobales->buscarPalabraEnHash(idTerminoString);

			if (listaIdTerminos.size() == 1 )
			{
				//std::cout<<"Id termino encontrado. ID = "<<idTermino<<std::endl;

				if( vectorConsulta->find(idTermino) != vectorConsulta->end())
				{
					(*vectorConsulta)[idTermino]++;
				}
				else
				{
					(*vectorConsulta)[idTermino] = 1;
				}

				//std::cout<<"Se ingreso termino ID en vector..."<<idTermino<<std::endl;
				//std::cout<<"Apariciones del termino: "<<(*vectorConsulta)[idTermino]<<std::endl;
			}

		}
		else
		{
			//No aporta nada al vector de terminos...
			//...no esta en ningun documento y se anula en el producto interno.
		}

	}

	//std::cout<<"Tamanio Vector Consulta: "<<vectorConsulta->size()<<std::endl;

	this->ponderarPesoLocal(vectorConsulta);

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
		sumatoriaCuadradaParcial = sumatoriaCuadradaParcial + pow(it_vector->second, 2);
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

void CalculadorDeNormas::generarArchivoDeNormasDeDocumentos()//ControladorBiblioteca* controladorBiblioteca)
{
	//vaciamos el contenido desactualizado de los indices.
	this->reiniciarIndices();
	//Generamos un indice con los pesos globales, que se van a usar intensivamente para la generacion de las normas.
	this->generarIndiceDePesosGlobalesDeTerminos();

	std::list<uint32_t>* listaIdDocumentos = this->controladorIndice->getControladorTriadas()->getLibrosAlmacenados();

	std::cout<<"Cantidad libros en lista: "<<listaIdDocumentos->size()<<std::endl;

	std::list<uint32_t>::iterator it_idDocumentos;

	std::string idDocumentoString;

	for (it_idDocumentos = listaIdDocumentos->begin(); it_idDocumentos != listaIdDocumentos->end(); it_idDocumentos++)
	{
		uint32_t idDocumento = (*it_idDocumentos);

		idDocumentoString = ServiceClass::obtenerString(idDocumento);

		VectorDeDocumento* vectorDocumento = this->cargarVectorDeTerminos(idDocumento);

		//Esta norma recibe la coma corrida dos lugares a la derecha, para almacenar dos decimales en un entero.
		//Al leer se corre de nuevo la coma y se recuperan los dos decimales.
		float normaDocumentoReal = this->calcularNormaVectorDeTerminos( vectorDocumento );

		uint32_t normaDocumento = ServiceClass::floatToUint32t(normaDocumentoReal);

		//Insertamos el par ID Doc / Norma Doc en el �ndice de normas...
		std::string idDocumetoStr = ServiceClass::obtenerString(idDocumento);
		std::pair<std::string, uint32_t> claveNormaDocumentoHash;
		claveNormaDocumentoHash.first = idDocumetoStr;
		std::cout<<"idDoc que se guarda en hash de normas de documentos: "<< idDocumento<<std::endl;
		claveNormaDocumentoHash.second = normaDocumento;
		this->indiceNormasDocumentos->insertarClave(claveNormaDocumentoHash);

		delete vectorDocumento;

	}
}

void CalculadorDeNormas::ponderarPesoLocal(VectorDeDocumento* vectorDocumento)
{
	//Se aplica para cada posicion la formula de peso local de termino:
	// Plocal = (frecuencia local) * (peso global);

	VectorDeDocumento::iterator it;
	for(it = vectorDocumento->begin(); it != vectorDocumento->end(); it++)
	{
		uint32_t idTermino = it->first;

		int frecuenciaLocal = it->second;

		//std::cout<<"Frecuencia local de termino..."<<frecuenciaLocal<<std::endl;

		float pesoGlobal = this->obtenerPesoGlobalDeIndice(idTermino);

		float pesoLocalTermino = pesoGlobal * frecuenciaLocal;

		it->second = pesoLocalTermino;
	}

}

float CalculadorDeNormas::calcularSimilitudConsultaConDocumento(uint32_t idDocumento, std::list<Termino*>* consulta)
{
	float  similitudCalculada = 0;

	std::cout<<"Consulta por similitud - Id libro: "<<idDocumento<<" |	";

	VectorDeDocumento* vectorConsulta = this->cargarVectorDeTerminos(consulta);

	VectorDeDocumento* vectorDocumento = this->cargarVectorDeTerminos(idDocumento);

	float productoInterno = this->calcularProductoInterno(vectorDocumento, vectorConsulta);

	//std::cout<<"Producto Interno = "<<productoInterno<<std::endl;

	//La norma del documento la leemos del indice, para ahorrar accesos a disco.
	float normaDocumento = this->obtenerNormaDocumentoDeIndice(idDocumento);

	//std::cout<<"Norma Documento = "<<normaDocumento<<std::endl;

	float normaConsulta = this->calcularNormaVectorDeTerminos(vectorConsulta);

	//std::cout<<"Norma Consulta = "<<normaConsulta<<std::endl;

	float productoDeNormas = normaDocumento * normaConsulta;

	//std::cout<<"ProductoDeNormas = "<<productoDeNormas<<std::endl;

	delete vectorConsulta;
	delete vectorDocumento;

	if (productoDeNormas > 0)
		similitudCalculada = productoInterno / productoDeNormas;

	std::cout<<"Similitud calculada: "<<similitudCalculada<<std::endl;

	return similitudCalculada;
}

void CalculadorDeNormas::generarReporteDeNormas(std::list<uint32_t> listaDocumentos)
{
	Configuracion* conf = Configuracion::GetInstancia();

	string pathArchivoReporte = conf->getPathCarpetaReportes()+"Reporte_NormaInfinito.txt";

	fstream archivoReporte;

	uint32_t normaDocumento = 0;

	ManejadorArchivo::Crear(pathArchivoReporte.c_str(), archivoReporte, false);

	archivoReporte << "REPORTE DE NORMAS DE DOCUMENTOS INDEXADOS" << std::endl;
	archivoReporte << "******* ** ****** ** ********** *********" <<std::endl << std::endl;

	while (!listaDocumentos.empty())
	{
		normaDocumento = this->obtenerNormaDocumentoDeIndice(listaDocumentos.front());

		archivoReporte << "Documento ID = " << listaDocumentos.front() << " | Norma Infinito = " << normaDocumento << std::endl;

		listaDocumentos.pop_front();
	}

	archivoReporte << std::endl <<  "FIN REPORTE" << std::endl;
	archivoReporte << 				"*** *******" <<std::endl << std::endl;

	ManejadorArchivo::Cerrar(archivoReporte);
}
