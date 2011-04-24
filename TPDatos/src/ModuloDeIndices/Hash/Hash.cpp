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

	//
	this->cantidadDeBloques = (int)GetSizeArchivo(archivoTabla) / TAMANIODATOTABLA;
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
	return numeroBloque * TAMANIODATOTABLA; //Se busca en la tabla 1ero y luego en archivo de cubetas.
}

DatoCubetaHash Hash::levantarBloqueNro(unsigned int numeroBloque)
{
	//Recordar que dos bloques distintos de la tabla hash pueden direccionar una misma cubeta de datos.
	std::stringstream cadenaLeida(ios_base::out|ios_base::in);

	//RecuperarEstructura(archivoCubetas, cadenaLeida, offsetBloque, TAMANIOCUBETA );

	DatoCubetaHash datoCubeta(&cadenaLeida);

	return datoCubeta;
}

DatoTablaHash* Hash::levantarDatoTabla(uint32_t offsetDatoTabla)
{
	DatoTablaHash* datoTabla = NULL;
	std::stringstream ss;

	ManejadorArchivo::RecuperarEstructura(this->archivoTabla, ss, offsetDatoTabla, sizeof(TAMANIODATOTABLA));

	datoTabla = new DatoTablaHash(&ss);

	return datoTabla;
}

DatoCubetaHash* Hash::levantarDatoCubeta(uint32_t offsetCubeta)
{
	DatoCubetaHash* datoCubeta = NULL;

	std::stringstream ss;

	ManejadorArchivo::RecuperarEstructura(this->archivoCubetas, ss, offsetCubeta, sizeof(TAMANIOCUBETA));

	datoCubeta = new DatoCubetaHash(&ss);

	return datoCubeta;
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
				resultados.push_back(elemento.getOffsetALibro());
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

void Hash::insertarClaveLibro(Libro* libro)
{

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
