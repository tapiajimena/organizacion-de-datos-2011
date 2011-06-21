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
/*
#include "CalculadorDeNormas.h"

CalculadorDeNormas::CalculadorDeNormas(ControladorIndice* controladorIndice, ArchivoTerminos* archivoTerminos)
{
	Configuracion* conf = Configuracion::GetInstancia();
	this->pathCarpeta = conf->getPathCarpetaTrabajo();

	//TODO sacar hardcode y obtener numero de documentos de controladorIndice->controladorTriadas()->getIdLibros()->size()
	this->cantidadTotalDeDocumentos = 2; //Se carga al calcular pesos globales.

	//this->controladorDeTriadas = controladorDeTriadas;
	this->controladorIndice = controladorIndice;
	this->archivoTerminos = archivoTerminos;

	this->nombreArchivoTablaPesos = this->pathCarpeta + "TablaIndicePesos.dat";
	this->nombreArchivoCubetasPesos = this->pathCarpeta + "CubetasIndicePesos.dat";

	this->nombreArchivoTablaNormas = this->pathCarpeta + "TablaIndiceNormas.dat";
	this->nombreArchivoCubetasNormas = this->pathCarpeta + "CubetasIndiceNormas.dat";

	//Levantamos los indices
	this->indicePesosGlobales = new Hash(this->nombreArchivoTablaPesos, this->nombreArchivoCubetasPesos);
	this->indiceNormasDocumentos = new Hash(this->nombreArchivoTablaNormas, this->nombreArchivoCubetasNormas);

	std::cout<<"*!*!*!*!*!* CREAMOS INDICES HASH"<<std::endl;

}

void CalculadorDeNormas::reiniciarIndices()
{
	//Creamos y cerramos los archivos, por si antes fueron creados. Necesitamos empezar de cero, y el Hash...
	//...está hecho para persistir y recuperar la información que guarda.
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
	//Los índices quedan en disco por si se quieren ver de alguna manera...
	delete this->indicePesosGlobales;
	delete this->indiceNormasDocumentos;

	//No destruye el resto de las estructuras, porque no le pertenecen.
}

std::list<DatoTriada*>* CalculadorDeNormas::levantarTriadasDeTermino(uint32_t idTermino)
{
	//Esto es un acceso directo al archivo a traves de su offset-Id.

<<<<<<< .mine
	//TODO ...

	std::string palabra = this->archivoTerminos->obtenerTermino(idTermino);
>>>>>>> .r541

	//TODO buscar triadas a traves de ConsultaIndice->ControladorTriadas()->obtenerTriadas(palabra);

/*
	std::list<DatoTriada*>* listaTriadas;

	std::cout<<"Palabra: "<<palabra<<std::endl;
	listaTriadas = this->controladorIndice->recuperarTriadas(palabra);
	//Posibilidades:
		//* Falla controladorIndice y me da cualquier direccion
		//* Falla controladorTriadas.
		//* ????

	std::cout<<"++++++++++++Tamanio lista Triadas:"<<listaTriadas->size()<<std::endl;
	std::cout<<"IdLibro: "<<listaTriadas->front()->getIdLibro()<<std::endl;
	std::cout<<"IdTermino: "<<listaTriadas->front()->getIdTermino()<<std::endl;
	std::cout<<"Posicion: "<<listaTriadas->front()->getPosicion()<<std::endl;

	std::cout<<"??????????????????????????"<<std::endl;
	return listaTriadas;


	//Testing con mock.
	MockControladorIndice* mock = new MockControladorIndice();
	std::list<DatoTriada*>* lista = mock->recuperarTriadas(palabra);

	std::cout<<"++++++++++++Tamanio lista Triadas para "<<palabra<<": "<<lista->size()<<std::endl;
	std::cout<<"IdLibro: "<<lista->front()->getIdLibro()<<std::endl;
	std::cout<<"IdTermino: "<<lista->front()->getIdTermino()<<std::endl;
	std::cout<<"Posicion: "<<lista->front()->getPosicion()<<std::endl;

	//delete mock;
	return lista;


	//std::list<DatoTriada*>* listaTriadas = new std::list<DatoTriada*>;
	//return listaTriadas;
}

void CalculadorDeNormas::generarIndiceDePesosGlobalesDeTerminos()
{
	std::vector<std::pair<std::string, uint32_t> > listaTerminos = this->archivoTerminos->obtenerTerminos();

	std::vector<std::pair<std::string, uint32_t> >::iterator it_terminos;

	float pesoGlobalTermino;

	std::pair<std::string, uint32_t> parIdTerminoPesoGlobal;

	for(it_terminos = listaTerminos.begin(); it_terminos != listaTerminos.end(); it_terminos++)
	{

		//calculamos el peso global...
		pesoGlobalTermino = this->calcularPesoGlobalDeTermino((*it_terminos).second);//por id de termino.

		std::cout<<"Termino: '"<<(*it_terminos).first<<"' con ID "<<(*it_terminos).second<<" Tiene Peso Global: "<<pesoGlobalTermino<<std::endl;
		//La clave en el indice es el ID de termino pero pasado a string.
		parIdTerminoPesoGlobal.first = ServiceClass::obtenerString((*it_terminos).second);

		//Guardamos el peso global con dos decimales en un entero. Al recuperar, se debe volver a correr la coma.
		int pesoTerminoConDosDecimales = ServiceClass::floatToUint32t(pesoGlobalTermino);
		parIdTerminoPesoGlobal.second = pesoTerminoConDosDecimales;

		//y lo guardamos en el indice...
		this->indicePesosGlobales->insertarClave(parIdTerminoPesoGlobal);
	}

	this->cantidadTotalDeDocumentos = listaTerminos.size();

}

int CalculadorDeNormas::calcularDocumentosQueContienenTermino(uint32_t idTermino)
{
	int documentosQueContienenTermino = 0;

	std::cout<<"---------------calcularDocumentosQueContienenTermino"<<std::endl;

	std::list<DatoTriada*>* ocurrenciasDeTermino = this->levantarTriadasDeTermino(idTermino);

	std::cout<<"++++++++++++++Ocurrencias de Termino: "<<ocurrenciasDeTermino->size()<<std::endl;
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

	//Vaciamos vector y liberamos recursos.
	while (!ocurrenciasDeTermino->empty())
	{
		delete ocurrenciasDeTermino->back();
		ocurrenciasDeTermino->pop_back();
	}
	delete ocurrenciasDeTermino;


	return documentosQueContienenTermino;
}

float CalculadorDeNormas::calcularPesoGlobalDeTermino(uint32_t idTermino)
{
	float pesoGlobal = 0.0;

	int frecuenciaGlobalDeTermino = this->calcularDocumentosQueContienenTermino(idTermino);

	std::cout<<"Frecuencia Global de Termino: "<<frecuenciaGlobalDeTermino<<std::endl;

	if(frecuenciaGlobalDeTermino != 0)
	{
		std::cout<<"Nro Real parcial: "<<(float)(this->cantidadTotalDeDocumentos / frecuenciaGlobalDeTermino)<<std::endl;
		pesoGlobal = log10( (float)(this->cantidadTotalDeDocumentos / frecuenciaGlobalDeTermino));
	}

	std::cout<<"Peso Global de Termino calculado: "<<pesoGlobal<<std::endl;

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

	while (!ocurrenciasDeTermino->empty())
	{
		delete ocurrenciasDeTermino->back();
		ocurrenciasDeTermino->pop_back();
	}
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

			std::cout<<"+++++++++++++++++++++++++++++PESO GLOBAL LEIDO: "<<pesoGlobalDeTermino<<std::endl;
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

	return frecuenciaLocal*pesoGlobal; // /normaDocumento (no va la norma documento aca)
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


VectorDeDocumento* CalculadorDeNormas::cargarVectorDeTerminos(uint32_t idDocumento)
{

	//TODO sacar mock de testing.
	//std::list<DatoTriada*>* listaDatoTriadas = this->controladorIndice->getControladorTriadas()->getTriadas(idDocumento);

	//Testing de triadas.
	MockControladorIndice* mock = new MockControladorIndice();
	std::list<DatoTriada*>* listaDatoTriadas = mock->recuperarTriadasDeDocumento(idDocumento);
	delete mock;


	std::cout<<"Leo triadas de documento................."<<std::endl;

	std::cout<<"Me llegan para el documento: " <<idDocumento<<", "<<listaDatoTriadas->size()<<" triadas."<<std::endl;
	std::list<DatoTriada*>::iterator it;
	for(it = listaDatoTriadas->begin(); it != listaDatoTriadas->end(); it++)
	{
		std::cout<<"IdLibro: "<<(*it)->getIdLibro();
		std::cout<<"IdTermino: "<<(*it)->getIdTermino();
		std::cout<<"Posicion: "<<(*it)->getPosicion()<<std::endl;
	}
	std::cout<<"Fin Triadas Documento---"<<std::endl;

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

	std::cout<<"Contenido Vector Documento (id termino; frec. local): "<<std::endl;
	std::cout<<listaTerminosEnDocumento->begin()->first<<" ;  "<<listaTerminosEnDocumento->begin()->second<<std::endl;

	//Ahora a la frecuencia local se le pondera el peso global del termino.
	this->ponderarPesoLocal(listaTerminosEnDocumento);

	std::cout<<"Contenido Vector Documento (id termino; frec. local): "<<std::endl;
	std::cout<<listaTerminosEnDocumento->begin()->first<<" ;  "<<listaTerminosEnDocumento->begin()->second<<std::endl;


	//Liberamos recursos
	while( !listaDatoTriadas->empty() )
	{
		delete listaDatoTriadas->back();
		listaDatoTriadas->pop_back();
	}

	return listaTerminosEnDocumento;
}

VectorDeDocumento* CalculadorDeNormas::cargarVectorDeTerminos(std::list<Termino*>* listaTerminos)
{
	VectorDeDocumento* vectorConsulta = new VectorDeDocumento();

	std::list<Termino*>::iterator it_terminos;

	for(it_terminos = listaTerminos->begin(); it_terminos != listaTerminos->end(); it_terminos++)
	{
		uint32_t idTermino = (*it_terminos)->obtenerId();

		if( vectorConsulta->find(idTermino) != vectorConsulta->end())
		{
			(*vectorConsulta)[idTermino]++;
		}
		else
		{
			(*vectorConsulta)[idTermino] = 1;
		}

	}

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
		std::cout<<"ID termino: "<<(*it_vector).first<<std::endl;

		sumatoriaCuadradaParcial = sumatoriaCuadradaParcial + pow(it_vector->second, 2);
	}

	normaDocumento = sqrt(sumatoriaCuadradaParcial);

	return normaDocumento;
}
<<<<<<< .mine


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
	std::cout<<"generarIndiceDePesosGlobales......"<<std::endl;
	//Generamos un indice con los pesos globales, que se van a usar intensivamente para la generacion de las normas.
	this->generarIndiceDePesosGlobalesDeTerminos();
	std::cout<<"generarIndiceDePesosGlobales......... OK"<<std::endl;
	std::list<uint32_t>* listaIdDocumentos = this->controladorIndice->getControladorTriadas()->getLibrosAlmacenados();
	//controladorBiblioteca->recuperarLibrosDeBiblioteca();
	std::list<uint32_t>::iterator it_idDocumentos;

	for (it_idDocumentos = listaIdDocumentos->begin(); it_idDocumentos != listaIdDocumentos->end(); it_idDocumentos++)
	{
		uint32_t idDocumento = (*it_idDocumentos);

		VectorDeDocumento* vectorDocumento = this->cargarVectorDeTerminos(idDocumento);

		std::cout<<"####Tamanio VectorDocumento: "<<vectorDocumento->size()<<std::endl;

		//Esta norma recibe la coma corrida dos lugares a la derecha, para almacenar dos decimales en un entero.
		//Al leer se corre de nuevo la coma y se recuperan los dos decimales.
		float normaDocumentoReal = this->calcularNormaVectorDeTerminos( vectorDocumento );

		uint32_t normaDocumento = ServiceClass::floatToUint32t(normaDocumentoReal);

		std::cout<<"NormaDocumento: "<<normaDocumentoReal<<std::endl;

		//Insertamos el par ID Doc / Norma Doc en el índice de normas...
		std::string idDocumetoStr = ServiceClass::obtenerString(idDocumento);
		std::pair<std::string, uint32_t> claveNormaDocumentoHash;
		claveNormaDocumentoHash.first = idDocumetoStr;
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

		float pesoGlobal = this->obtenerPesoGlobalDeIndice(idTermino);

		float pesoLocalTermino = pesoGlobal * frecuenciaLocal;

		//it->second = ServiceClass::floatToUint32t(pesoLocalTermino);
		it->second = pesoLocalTermino;
		std::cout<<"Elemento de vector: "<<it->second<<std::endl;
	}

}

float CalculadorDeNormas::calcularSimilitudConsultaDocumento(uint32_t idDocumento, std::list<Termino*>* consulta)
{

	VectorDeDocumento* vectorConsulta = this->cargarVectorDeTerminos(consulta);

	VectorDeDocumento* vectorDocumento = this->cargarVectorDeTerminos(idDocumento);

	float productoInterno = this->calcularProductoInterno(vectorDocumento, vectorConsulta);

	std::cout<<"Producto Interno: "<<productoInterno<<std::endl;
	//La norma del documento la leemos del indice, para ahorrar accesos a disco.

	float normaDocumento = this->obtenerNormaDocumentoDeIndice(idDocumento);
	std::cout<<"Norma Documento: "<<normaDocumento<<std::endl;

	float normaConsulta = this->calcularNormaVectorDeTerminos(vectorConsulta);
	std::cout<<"Norma Consulta: "<<normaConsulta<<std::endl;

	float productoDeNormas = normaDocumento * normaConsulta;

	delete vectorConsulta;
	delete vectorDocumento;

	return productoInterno / productoDeNormas;
}
>>>>>>> .r541
*/
