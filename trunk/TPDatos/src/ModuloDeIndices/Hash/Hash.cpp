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
		//Creamos los dos primeros bloques de la tabla (vacï¿½as).
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

	//este mï¿½todo de abajo no reserva espacio adicional... no me sirve.
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
				//TODO: si hace falta recorrer usar otra estructura mï¿½s eficaz para buscar.

				//Verificamos si el offset de ese libro ya fue ingresado. Si asï¿½ fue, no se vuelve a ingresar.
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

void Hash::duplicarTablaHash()
{
	unsigned int nuevaCantidadDeBloques = this->cantidadDeBloques * 2;

	for (unsigned int nroBloque = this->cantidadDeBloques + 1; nroBloque <= nuevaCantidadDeBloques; nroBloque++)
	{
		uint32_t offsetNuevoBloqueTabla = this->calcularOffsetBloqueEnTabla( nroBloque );
		DatoTablaHash nuevoDatoTabla;

		//Bloque al que se direccionarÃ­an los elementos del actual con la funciÃ³n de hash nueva (segÃºn cantidad de bloques vieja).
		unsigned int nroBloqueAnteriorEquivalente = nroBloque % this->cantidadDeBloques;
		uint32_t offsetBloqueEquivalenteAnterior = this->calcularOffsetBloqueEnTabla( nroBloqueAnteriorEquivalente );
		DatoTablaHash* datoTablaEquivalenteAnterior = this->levantarDatoTabla( offsetBloqueEquivalenteAnterior );

		nuevoDatoTabla.setOffsetCubeta( datoTablaEquivalenteAnterior->getOffsetCubeta() );
		nuevoDatoTabla.setCantidadDeElementos( datoTablaEquivalenteAnterior->getCantidadDeElementos());

		//No se usa ahora, pero vale la pena recordar esta relaciÃ³n: [X mod 2N] mod N = X mod N

		//Nota: no se actualiza (ni se debe hacerlo) la cantidad de bloques hasta terminar de duplicar toda la tabla.
		this->escribirDatoTabla(&nuevoDatoTabla, offsetNuevoBloqueTabla);
	}

	this->cantidadDeBloques = nuevaCantidadDeBloques;
}

void Hash::manejarDesbordeCubeta(ElementoHash* elemento, DatoCubetaHash* datoCubeta, DatoTablaHash* datoTabla, uint32_t offsetDatoTabla)
{
	//Si llegamos hasta acï¿½ sabemos que el dato no cabe en la cubeta que nos llega por parï¿½metro

	std::vector<DatoCubetaHash*> cubetasSucesivas; //Vector que guarda puntero a cubeta junto con su offset.

	cubetasSucesivas.push_back(datoCubeta);

	//Si en este proceso se usa demasiada memoria, se puede trabajar con offsets en el vector de arriba, en vez de con las cubetas, y usando levantarDatoCubeta cada vez.
	//Sin embargo es raro que una cubeta se extienda, y cada cubeta tiene 1KB de tamaño, por lo que se da por bueno subirlas sucesivamente a memoria.

	bool elementoInsertado = false;

	//Se intenta insertar el elemento sucesivamente en las extensiones de la cubeta actual, si las hubiere.
	//NOTA: La cubeta con offset 0 siempre es inicializada y no continï¿½ua otras anteriores
	while ( cubetasSucesivas.back()->getOffsetCubetaContinuacion() != 0 && !elementoInsertado)
	{

		cubetasSucesivas.push_back( this->levantarDatoCubeta( cubetasSucesivas.back()->getOffsetCubetaContinuacion()) );
		//offsetsDeExtensionesDeCubeta.push_back( datoCubeta->getOffsetCubetaContinuacion() );

		elementoInsertado = cubetasSucesivas.back()->insertarElementoHash(*elemento); //Lo inserta si puede.
	}

	//Si no se ingresï¿½ el dato en alguna cubeta extendida anteriormente, se hace lo siguiente:
	//
	// * Se duplica el tamaï¿½o de la tabla y se redispersan todos los elementos contenidos en la cubeta (o bloque de cubetas
	// agrupadas por la entrada de la tabla) desbordada.
	//
	// * En caso de que aï¿½n haciendo lo anterior siga habiendo desborde, se repite el proceso hasta 3 veces.
	//
	// * Si luego de duplicar la tabla 3 veces la cubeta sigue desbordada, se asume que el desborde se debe a que muchas palabras
	// tienen exactamente el mismo valor de hash, y por lo tanto la ï¿½nica manera de agregar la nueva entrada es extendiendo una cubeta.
	// Para esto se indica en la cubeta el offset de la nueva cubeta que la extiende.

	//Redispersión del bloque de cubetas.
	if (!elementoInsertado)
	{
	uint32_t offsetCubetaInicial = datoTabla->getOffsetCubeta();
	//elementoInsertado = this->redispersarBloqueDeCubetasSucesivas( &cubetasSucesivas, offsetCubetaInicial); //TODO!!
	}

	//Duplicamos la tabla hasta 3 veces
	for (int intentos = 0; intentos < 3 && !elementoInsertado; intentos++)
	{
		// ?y si antes de duplicar tabla intento redispersar cubeta?


		//this->duplicarTablaHash();
		//this->redispersarBloqueDeTabla( datoTabla, offsetDatoTabla );

		//insertar elemento con tabla extendida.
	}

	//Si aún no se pudo insertar, extendemos la cubeta (tras duplicar tabla y redispersar antes el bloque, ojo)
	//TODO

	//registramos el incremento en la entrada tambiï¿½n de la tabla.... esto NO va acá....
	datoTabla->setCantidadDeElementos(datoTabla->getCantidadDeElementos() + 1);
	this->escribirDatoTabla( datoTabla, offsetDatoTabla);


	//liberación de recursos.
	cubetasSucesivas.clear(); //llama a los destructures de sus objetos.
	delete datoTabla;
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

	//TODO separar en dos metodos, el que implementa recibe un elemento a insertar. (?)
	ElementoHash elementoAInsertar(palabraClave, offsetALibro);

	//Primero obtenemos el bloque al que irï¿½a la palabra
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
		datoTablaAPriori->setCantidadDeElementos(datoTablaAPriori->getCantidadDeElementos()+1);
		this->escribirDatoTabla(datoTablaAPriori, offsetDatoTabla);

		//liberación local de recursos.
		delete datoCubeta;
		delete datoTablaAPriori;
	}
	else
	{
		//Delegamos el manejo del desborde a otro mï¿½todo
		this->manejarDesbordeCubeta(&elementoAInsertar, datoCubeta, datoTablaAPriori, offsetDatoTabla);

		//este método libera los recursos de datoCubeta y datoTabla.
	}

	//recursos liberados.
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

		//Lo pasamos a una lista para que sea mï¿½s eficiente la eliminaciï¿½n de claves no comunes.
		for (unsigned int nroResultado = 0; nroResultado < listaResultadosAcumulados.size(); nroResultado++)
		{
			listaResultadosAcumulados.insert(listaResultadosAcumulados.begin(), resultadosParciales.at(nroResultado));
		}

		//Mientras queden palabras por procesar y no se hayan descartado todos los resultados...
		unsigned int nroPalabraClave = 1; //(la palabra nro cero se procesï¿½ arriba)
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

				//Si el resultado no estaba en la bï¿½squeda actual, se elimina de resultados acumulados.
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
