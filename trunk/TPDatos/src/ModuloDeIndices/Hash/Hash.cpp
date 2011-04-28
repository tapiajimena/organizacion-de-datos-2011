/*
 * Hash.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *     Estructura que administra un Ã­ndice para acceder a registros libros.
 *
 */

#include "Hash.h"

//Hash::Hash() {}

Hash::Hash(std::string nombreArchivoTabla, std::string nombreArchivoCubetas){


	CrearSiNoExiste(nombreArchivoTabla.c_str(),archivoTabla);
	CrearSiNoExiste(nombreArchivoCubetas.c_str(),archivoCubetas);

	this->nombreArchivoTabla = nombreArchivoTabla;
	this->nombreArchivoCubetas = nombreArchivoCubetas;

	this->cantidadDeBloques = 0;
	this->cantidadDeCubetas = 0;

	if(ManejadorArchivo::GetSizeArchivo(this->archivoTabla) == 0)
	{
		//Creamos los dos primeros bloques de la tabla (vacías).
		DatoTablaHash datoTabla0 = DatoTablaHash();
		DatoTablaHash datoTabla1 = DatoTablaHash();

		//Agregamos los dos primeros bloques...
		datoTabla0.setOffsetCubeta( 0 );
		datoTabla0.setCantidadDeElementos( 0 );

		datoTabla1.setOffsetCubeta( TAMANIOCUBETA );
		datoTabla1.setCantidadDeElementos(0);

		this->escribirDatoTabla(&datoTabla0, this->calcularOffsetBloqueEnTabla(0));
		this->escribirDatoTabla(&datoTabla1, this->calcularOffsetBloqueEnTabla(1));
		this->cantidadDeBloques = 2;
		//Y sus correspondientes cubetas...
		DatoCubetaHash datoCubeta0 = DatoCubetaHash(); //inicializan en cero.
		DatoCubetaHash datoCubeta1 = DatoCubetaHash();

		this->escribirDatoCubeta( &datoCubeta0, datoTabla0.getOffsetCubeta() );
		this->escribirDatoCubeta( &datoCubeta1, datoTabla1.getOffsetCubeta() );
		this->cantidadDeCubetas = 2;
	}
	else
	{
		//Calculamos la cantidad de bloques
		this->cantidadDeBloques = (unsigned int)(GetSizeArchivo(archivoTabla) / TAMANIODATOTABLA);

		this->cantidadDeCubetas = (unsigned int) (GetSizeArchivo(archivoCubetas) / TAMANIOCUBETA);
	}
}


unsigned int Hash::getCantidadDeBloques()
{
	return this->cantidadDeBloques;
}

std::string Hash::getNombreArchivoTabla()
{
	return this->nombreArchivoTabla;
}

std::string Hash::getNombreArchivoCubetas()
{
	return this->nombreArchivoCubetas;
}

unsigned int Hash::funcionHash(std::string claveADispersar)
{
	unsigned int valorHash = 0;
	for (unsigned int x = 0; x < claveADispersar.size(); x++)
	{
		valorHash = valorHash + (unsigned int)claveADispersar.at(x);
	}

	return valorHash;
}

unsigned int Hash::obtenerNumeroDeBloque(unsigned int valorDispersado, unsigned int cantidadDeBloques)
{
	unsigned int valorRetorno = (unsigned int)valorDispersado%cantidadDeBloques;

	return valorRetorno;
}

unsigned int Hash::obtenerNumeroDeBloque(std::string claveADispersar)
{
	unsigned int valorHash = this->funcionHash(claveADispersar);

	return this->obtenerNumeroDeBloque(valorHash, this->cantidadDeBloques);
}

uint32_t Hash::calcularOffsetBloqueEnTabla(unsigned int numeroBloque)
{
	return (numeroBloque * TAMANIODATOTABLA); //Se busca en la tabla 1ero y luego en archivo de cubetas.
}

DatoTablaHash* Hash::levantarDatoTabla(uint32_t offsetDatoTabla)
{
	DatoTablaHash* datoTabla = NULL;
	std::stringstream ss;

	ManejadorArchivo::RecuperarEstructura(this->archivoTabla, ss, offsetDatoTabla, TAMANIODATOTABLA);

	datoTabla = new DatoTablaHash(&ss);

	return datoTabla;
}

DatoCubetaHash* Hash::levantarDatoCubeta(uint32_t offsetCubeta)
{
	DatoCubetaHash* datoCubeta = NULL;

	std::stringstream ss;

	ManejadorArchivo::RecuperarEstructura(this->archivoCubetas, ss, offsetCubeta, TAMANIOCUBETA);

	datoCubeta = new DatoCubetaHash(&ss);

	return datoCubeta;
}

void Hash::escribirDatoCubeta(DatoCubetaHash* datoCubeta, uint32_t offsetCubeta)
{
	stringstream ss;//(ios_base::in | ios_base::out);
	datoCubeta->serializarCubeta(&ss);

	int caracteres = ss.str().size();

	for (int x = 0; x < TAMANIOCUBETA - caracteres; x++)
	{
		ss<<BYTENULOENDISCO;
	}

	ManejadorArchivo::Escribir(archivoCubetas, &ss, offsetCubeta);

	//este método de abajo no reserva espacio adicional... no me sirve.
	//ManejadorArchivo::Escribir(&archivoCubetas, &ss, offsetCubeta, TAMANIOCUBETA);
}

void Hash::escribirDatoTabla(DatoTablaHash* datoTabla, uint32_t offsetDatoTabla)
{
	//stringstream ss(ios_base::in | ios_base::out);
	stringstream ss;
	datoTabla->serializarDatoTabla(&ss);
	ManejadorArchivo::Escribir(&archivoTabla, &ss, offsetDatoTabla, TAMANIODATOTABLA);
}

std::vector<uint32_t> Hash::acumularResultados(DatoCubetaHash* datoCubeta, std::string palabra)
{
	std::vector<uint32_t> resultados;

	bool siguienteCubeta = true; //indica si hay siguiente cubeta donde continuan los datos de la presente.
	uint32_t offsetSiguienteCubeta;

	while (siguienteCubeta)
	{
		if (datoCubeta->getOffsetCubetaContinuacion() == 0)
		{
			siguienteCubeta = false;
		}

		offsetSiguienteCubeta = datoCubeta->getOffsetCubetaContinuacion();

		for (unsigned int x = 0; x < datoCubeta->getElementos().size(); x++)
		{
			ElementoHash elemento = datoCubeta->getElementos().at(x);

			if( elemento.getPalabra() == palabra)
			{
				//TODO: si hace falta recorrer usar otra estructura más eficaz para buscar.

				//Verificamos si el offset de ese libro ya fue ingresado. Si así fue, no se vuelve a ingresar.
				bool yaFueIngresado = false;
				std::vector<uint32_t>::iterator it;

				for(it = resultados.begin(); it != resultados.end() && yaFueIngresado == false; it++)
				{
					if ( (*it) == elemento.getOffsetALibro())
						yaFueIngresado = true;
				}

				if (!yaFueIngresado)
				{
					resultados.push_back(elemento.getOffsetALibro());
				}

			}
		}

		if(siguienteCubeta)
		{
			delete datoCubeta;
			datoCubeta = this->levantarDatoCubeta(offsetSiguienteCubeta);
		}
	}
	return resultados;
}

uint32_t Hash::nuevaCubetaAlFinal(DatoCubetaHash* datoCubeta)
{
	uint32_t offsetNuevaCubeta = this->cantidadDeCubetas * TAMANIOCUBETA;
	this->escribirDatoCubeta( datoCubeta, offsetNuevaCubeta );
	this->cantidadDeCubetas++;

	return offsetNuevaCubeta;
}


void Hash::manejarDesbordeCubeta(ElementoHash* elemento, DatoCubetaHash* datoCubetaDesbordada, DatoTablaHash* datoTablaDesbordada)
{
	//TODO
}

void Hash::insertarClaveLibro(Libro* libro)
{
	//DEPRECATED
}

void Hash::insertarClave(std::pair<std::string, uint32_t> registroHash)
{
	//Elementos a insertar
	uint32_t offsetALibro = registroHash.second;
	std::string palabraClave = registroHash.first;

	ElementoHash elementoAInsertar(palabraClave, offsetALibro);

	//Primero obtenemos el bloque al que iría la palabra
	unsigned int numeroDeBLoqueAPriori = this->obtenerNumeroDeBloque(palabraClave);
	uint32_t offsetDatoTabla = this->calcularOffsetBloqueEnTabla(numeroDeBLoqueAPriori);

	DatoTablaHash* datoTablaAPriori = this->levantarDatoTabla(offsetDatoTabla);

	//Obtenemos el offset de la cubeta con la tabla
	uint32_t offsetCubeta = datoTablaAPriori->getOffsetCubeta();

	DatoCubetaHash* datoCubeta = this->levantarDatoCubeta( offsetCubeta );

	bool datoInsertado = datoCubeta->insertarElementoHash(elementoAInsertar); //Lo inserta si puede.

	if (datoInsertado)
	{
		//Reescribimos la cubeta en disco
		this->escribirDatoCubeta(datoCubeta, offsetCubeta);
	}
	else
	{
		//Delegamos el manejo del desborde a otro método
		this->manejarDesbordeCubeta(&elementoAInsertar, datoCubeta, datoTablaAPriori);
	}


	delete datoCubeta;
	delete datoTablaAPriori;
}

std::vector<uint32_t> Hash::buscarPalabraEnHash(std::string palabraClave)
{
	unsigned int numeroBloque = this->obtenerNumeroDeBloque(palabraClave);

	uint32_t offsetDatoTabla = this->calcularOffsetBloqueEnTabla(numeroBloque);

	DatoTablaHash* datoTabla = this->levantarDatoTabla(offsetDatoTabla);

	DatoCubetaHash* datoCubeta = this->levantarDatoCubeta(datoTabla->getOffsetCubeta());

	std::vector<uint32_t> resultadosBusqueda = this->acumularResultados(datoCubeta, palabraClave);

	delete datoTabla;
	delete datoCubeta;

	return resultadosBusqueda;
}

std::vector<uint32_t> Hash::buscarFraseEnHash(std::string fraseConPalabrasClave)
{
	std::string fraseConPalabrasClaveNormalizada = ServiceClass::normalizarString(fraseConPalabrasClave);

	std::vector<std::string>listaPalabrasClave = ServiceClass::obtenerListaPalabras(fraseConPalabrasClaveNormalizada, SEPARADORES_DE_PALABRAS);

	std::list<uint32_t> listaResultadosAcumulados;

	std::vector<uint32_t> resultadosParciales;
	std::vector<uint32_t> resultadosFinales;

	if (listaPalabrasClave.size() > 0)
	{
		//resultados de la primera palabra
		resultadosParciales = buscarPalabraEnHash( listaPalabrasClave.at(0) );

		//Lo pasamos a una lista para que sea más eficiente la eliminación de claves no comunes.
		for (unsigned int nroResultado = 0; nroResultado < listaResultadosAcumulados.size(); nroResultado++)
		{
			listaResultadosAcumulados.insert(listaResultadosAcumulados.begin(), resultadosParciales.at(nroResultado));
		}

		//Mientras queden palabras por procesar y no se hayan descartado todos los resultados...
		unsigned int nroPalabraClave = 1; //(la palabra nro cero se procesó arriba)
		while (nroPalabraClave < listaPalabrasClave.size() && listaResultadosAcumulados.size() > 0)
		{
			//Buscamos resultados de las palabras clave
			resultadosParciales = buscarPalabraEnHash( listaPalabrasClave.at(nroPalabraClave) );

			//Se eliminan los resultados que no sean comunes a TODAS las palabras clave.
			std::list<uint32_t>::iterator it_resultados = listaResultadosAcumulados.begin();

			while ( it_resultados != listaResultadosAcumulados.end())
			{
				uint32_t resultadoActual = *it_resultados;

				bool resultadoAcumuladoExisteTambienEnBusquedaActual = false;

				unsigned int x = 0;
				while (x < resultadosParciales.size() && !resultadoAcumuladoExisteTambienEnBusquedaActual)
				{
					if (resultadoActual == resultadosParciales.at(x))
						resultadoAcumuladoExisteTambienEnBusquedaActual = true;
				}

				//Si el resultado no estaba en la búsqueda actual, se elimina de resultados acumulados.
				if (!resultadoAcumuladoExisteTambienEnBusquedaActual)
				{
					std::list<uint32_t>::iterator it_elimiacion = it_resultados;
					it_resultados++;
					listaResultadosAcumulados.erase(it_elimiacion);
				}
				else
				{
					it_resultados++;
				}
			}
		}
		for (std::list<uint32_t>::iterator it_resultados = listaResultadosAcumulados.begin(); it_resultados != listaResultadosAcumulados.end(); it_resultados++)
		{
			resultadosFinales.push_back( *it_resultados);
		}

	}

	return resultadosFinales;
}

Hash::~Hash()
{
	Cerrar(archivoTabla);
	Cerrar(archivoCubetas);
}
