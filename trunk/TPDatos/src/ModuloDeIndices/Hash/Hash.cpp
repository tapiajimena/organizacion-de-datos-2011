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

std::vector< unsigned int > Hash::obtenerBloquesConMismaCubeta(unsigned int nroDeBloque, unsigned int offsetCubeta)
{
	std::vector< unsigned int > entradasDeTabla;

	/* Se procede de la siguiente manera:
	 *
	 * Dado el tamaño actual de la tabla, la cuenta para determinar el nro de bloque al que se entra es:
	 *
	 * nroBloque = X mod N
	 *
	 * ...donde X es el número dispersado del dato por la función de Hash y N la cantidad de bloques de la tabla.
	 *
	 * Ahora tenemos que a medida que la tabla fue creciendo, bloques que cuando la tabla tenía menos "resolución" de números de bloque agruparon datos, que luego de expandirse
	 * la tabla corresponderían a distintas entradas. Las nuevas entradas direccionan a la cubeta de la anterior... ¿ok? Lo que relaciona a estas dos entradas de tabla, que antes
	 * eran la misma y luego de duplicar la tabla se separaron, por hacer X mod 2N en vez de X mod N, tienen en común justamente eso, el resto que dan según el tamaño de la tabla.
	 *
	 * Si tenemos X = 31 y la tabla tiene tamaño N = 16 (crece en potencias de dos)
	 *
	 * Nro de bloque actual, al que iría el dato con valor X = 31 es
	 *
	 * 31 mod 16 = 15
	 *
	 * Sin embargo antes, con N = 8 otro dato con mismo X podría haber ido
	 *
	 * 31 mod 8 = 7, pero también tenemos que 15 mod 8 = 7, y así sucesivamente...
	 * 31 mod 4 = 3... 3 = 7 mod 4
	 * 31 mod 2 = 1... 1 = 3 mod 2
	 *
	 * Vinculamos todas estas entradas de tabla, que son candidatas a estar compartiendo una cubeta a través de cálculo recursivo de módulo para los N que fue teniendo la tabla.
	 * (si de entrada tenemos un número bajo, ese número se repite hasta que la tabla sea menor que el número obtenido... por ejemplo, de ser X mod N = 0 o 1, ese valor sería igual
	 * para todos los tamaños de la tabla.
	 *
	 * Podemos usar esta propiedad del álgebra modular:
	 *
	 * a = b mod c <=> c = a mod b (el igual en sentido de congruencia del álgebra modular).
	 */

	/*
	std::vector<unsigned int> numerosDeBloqueParientes;

	unsigned int nroDeBloqueEquivalenteTemporal = nroDeBloque; //ver función obtener número de bloque.

	//Como la tabla nos viene con el tamaño actualizado, sólo hay que buscar equivalencias hacia atrás.
	//TamanioTablaEnesimo representa cantidad de bloques.
	for( unsigned int tamanioTablaEnesimo = this->cantidadDeBloques; tamanioTablaEnesimo > 1; tamanioTablaEnesimo = (unsigned int)(tamanioTablaEnesimo / 2) )
	{
		nroDeBloqueEquivalenteTemporal = (unsigned int) nroDeBloqueEquivalenteTemporal % tamanioTablaEnesimo; //en la 1er iteración da igual a nroDeBloque.

		if( std::find(numerosDeBloqueParientes.begin(), numerosDeBloqueParientes.end(), nroDeBloqueEquivalenteTemporal) !=  numerosDeBloqueParientes.end()
			&&
			nroDeBloqueEquivalenteTemporal != nroDeBloque)
		{
			//si el equivalente no había sido ingresado, lo ingresamos, salvo que sea igual al nroDeBloque parámetro
			numerosDeBloqueParientes.push_back(nroDeBloqueEquivalenteTemporal);
		}
	}

	//return numerosDeBloqueParientes;
	*/

	std::vector<unsigned int> numerosDeBloqueCompartiendoCubeta;
	//Ahora levantamos todos los bloques parientes que apunten a la misma cubeta.
	//for( std::vector<unsigned int>::iterator it_nrosBloque = numerosDeBloqueParientes.begin(); it_nrosBloque != numerosDeBloqueParientes.end(); it_nrosBloque++)
	for( unsigned int numeroBloqueTemporal = 0; numeroBloqueTemporal < this->getCantidadDeBloques(); numeroBloqueTemporal++)
	{
		uint32_t offsetDatoTabla = this->calcularOffsetBloqueEnTabla( numeroBloqueTemporal);//*it_nrosBloque );
		DatoTablaHash* datoTabla = this->levantarDatoTabla(offsetDatoTabla); //recordar que datoTabla equivale a bloque. La tabla contiene bloques que direccionan cubetas.

		if(datoTabla->getOffsetCubeta() == offsetCubeta && numeroBloqueTemporal != nroDeBloque)
		{
			//TODO hacer esto...
			//std::pair<DatoTablaHash*, unsigned int> datoTablaYNroBloque( datoTabla, *it_nrosBloque);
			//entradasDeTabla.push_back( datoTablaYNroBloque );
			numerosDeBloqueCompartiendoCubeta.push_back( numeroBloqueTemporal);//*it_nrosBloque );
		}

		delete datoTabla;
	}
	return numerosDeBloqueCompartiendoCubeta;
	//return entradasDeTabla;
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
	unsigned int nuevaCantidadDeBloques = (unsigned int) this->cantidadDeBloques * 2;

	for (unsigned int nroBloque = this->cantidadDeBloques; nroBloque <= nuevaCantidadDeBloques - 1; nroBloque++)
	{
		uint32_t offsetNuevoBloqueTabla = this->calcularOffsetBloqueEnTabla( nroBloque );
		DatoTablaHash nuevoDatoTabla; //(estructura estática)

		//Bloque al que se direccionarÃ­an los elementos del actual con la funciÃ³n de hash nueva (segÃºn cantidad de bloques vieja).
		unsigned int nroBloqueAnteriorEquivalente = nroBloque % this->cantidadDeBloques;
		uint32_t offsetBloqueEquivalenteAnterior = this->calcularOffsetBloqueEnTabla( nroBloqueAnteriorEquivalente );
		DatoTablaHash* datoTablaEquivalenteAnterior = this->levantarDatoTabla( offsetBloqueEquivalenteAnterior );

		nuevoDatoTabla.setOffsetCubeta( datoTablaEquivalenteAnterior->getOffsetCubeta() );
		nuevoDatoTabla.setCantidadDeElementos( datoTablaEquivalenteAnterior->getCantidadDeElementos());

		//No se usa ahora, pero vale la pena recordar esta relaciÃ³n: [X mod 2N] mod N = X mod N

		//Nota: no se actualiza (ni se debe hacerlo) la cantidad de bloques hasta terminar de duplicar toda la tabla.
		this->escribirDatoTabla(&nuevoDatoTabla, offsetNuevoBloqueTabla);

		delete datoTablaEquivalenteAnterior;
	}

	this->cantidadDeBloques = nuevaCantidadDeBloques;
}

void Hash::redispersarSucesionCubetas(std::vector<DatoCubetaHash*> cubetasSucesivas, unsigned int numeroDeBloque, DatoTablaHash* datoTabla)
{
	std::vector< unsigned int > bloquesConMismaCubeta = this->obtenerBloquesConMismaCubeta( numeroDeBloque, datoTabla->getOffsetCubeta());
	std::cout<<"Bloques que comparten cubeta..."<<bloquesConMismaCubeta.size()<<std::endl;

	//Inicializamos cubetas vacías para los bloques que compartían la cubeta desbordada.
	for( std::vector<unsigned int>::iterator it_bloques = bloquesConMismaCubeta.begin(); it_bloques != bloquesConMismaCubeta.end(); it_bloques++)
	{
		DatoCubetaHash* datoCubeta = new DatoCubetaHash();
		uint32_t offsetCubeta = this->nuevaCubetaAlFinal(datoCubeta);

		DatoTablaHash* datoTablaInicializado = this->levantarDatoTabla( this->calcularOffsetBloqueEnTabla(*it_bloques) );
		datoTablaInicializado->setCantidadDeElementos(0);
		datoTablaInicializado->setOffsetCubeta( offsetCubeta );

		this->escribirDatoTabla(datoTablaInicializado, this->calcularOffsetBloqueEnTabla( *it_bloques ));
		delete datoTablaInicializado;
		delete datoCubeta;
	}

	//Ahora redispersamos los datos de la cubeta compartida anteriormente (la sucesión de cubetas está en memoria).
	uint32_t offsetCubetaActual = datoTabla->getOffsetCubeta();

	for( std::vector<DatoCubetaHash*>::iterator it_cubetasSucesivas = cubetasSucesivas.begin(); it_cubetasSucesivas != cubetasSucesivas.end(); it_cubetasSucesivas++)
	{
		std::vector<ElementoHash> elementos = (*it_cubetasSucesivas)->getElementos(); //nos da una copia.

		for( std::vector<ElementoHash>::iterator it_elementos = elementos.begin(); it_elementos != elementos.end(); it_elementos++)
		{
			unsigned int nuevoNumeroDeBloque = this->obtenerNumeroDeBloque( it_elementos->getPalabra());

			//Si al elemento le corresponde otro número de bloque, se lo redispersa en la tabla.
			if( nuevoNumeroDeBloque != numeroDeBloque)
			{
				//Redispersamos el elemento en la tabla (cae y se escribe en otro bloque y su dirección se corresponde con el tamaño de tabla actual):
				this->insertarElemento( *it_elementos );

				//Y lo eliminamos de la cubeta a la que no le corresponde más.
				(*it_cubetasSucesivas)->eliminarElementoHash( *it_elementos );
				datoTabla->setCantidadDeElementos( datoTabla->getCantidadDeElementos() - 1);
			}
		}

		//Reescribimos la cubeta que eventualmente perdió elementos al redistribuirlos.
		this->escribirDatoCubeta( *it_cubetasSucesivas, offsetCubetaActual);
		offsetCubetaActual = (*it_cubetasSucesivas)->getOffsetCubetaContinuacion();
	}

	this->escribirDatoTabla(datoTabla, this->calcularOffsetBloqueEnTabla( numeroDeBloque ));
}

/*Refactorizando metodo... (voy a dividir en metodos mas chiquitos)
void Hash::manejarDesbordeCubeta(ElementoHash* elemento, DatoCubetaHash* datoCubeta, DatoTablaHash* datoTabla, unsigned int numeroDeBloque)
{

	bool elementoInsertado = false;

	std::vector<DatoCubetaHash*> cubetasSucesivas;

	cubetasSucesivas.push_back(datoCubeta); //Al 1er elemento no se le debe hacer delete en este método.



}
*/


void Hash::manejarDesbordeCubeta(ElementoHash* elemento, DatoCubetaHash* datoCubeta, DatoTablaHash* datoTabla, unsigned int numeroDeBloque)
{
	//Si llegamos hasta acï¿½ sabemos que el dato no cabe en la cubeta que nos llega por parï¿½metro

	std::vector<DatoCubetaHash*> cubetasSucesivas; //Vector que guarda puntero a cubeta junto con su offset.

	bool elementoInsertado = false;

	cubetasSucesivas.push_back(datoCubeta);

	//Se intenta insertar el elemento sucesivamente en las extensiones de la cubeta actual, si las hubiere (si no, se carga la sucesión de cubetas).
	//NOTA: La cubeta con offset 0 siempre es inicializada y no continï¿½ua otras anteriores
	//PRIMERO...
	uint32_t offsetCubetaActual = datoTabla->getOffsetCubeta();

	while ( cubetasSucesivas.back()->getOffsetCubetaContinuacion() != 0 && !elementoInsertado)
	{
		offsetCubetaActual = cubetasSucesivas.back()->getOffsetCubetaContinuacion();
		cubetasSucesivas.push_back( this->levantarDatoCubeta( offsetCubetaActual ) );

		elementoInsertado = cubetasSucesivas.back()->insertarElementoHash(*elemento); //Lo inserta si puede.
	}

	if(elementoInsertado)
	{
		datoTabla->setCantidadDeElementos( datoTabla->getCantidadDeElementos() + 1);
		this->escribirDatoTabla( datoTabla, this->calcularOffsetBloqueEnTabla(numeroDeBloque));
		this->escribirDatoCubeta( cubetasSucesivas.back(), offsetCubetaActual);

		//liberación de recursos...
		//delete datoTabla;
		while ( cubetasSucesivas.size() > 1)
		{
			DatoCubetaHash* cubeta = cubetasSucesivas.back();
			delete cubeta;
			cubetasSucesivas.pop_back();
		}
		//cubetasSucesivas.clear();
	}

	if (!elementoInsertado)
	{
		//---------------------------------------------------------------------------------------------------------------------------------------
		//Si no hubo éxito... -------------------------------------------------------------------------------------------------------------------
		//SEGUNDO...

		//...intentamos esto: todos los bloques que compartían la cubeta inicial inicializan una cubeta vacía y se redispersan los elementos de la cubeta compartida.
		if (cubetasSucesivas.size() > 1)
		{
			this->redispersarSucesionCubetas( cubetasSucesivas, numeroDeBloque, datoTabla);

			//intentamos meter el dato en alguna cubeta de la sucesión, a ver si se hizo lugar...
			offsetCubetaActual = datoTabla->getOffsetCubeta();
			for( std::vector<DatoCubetaHash*>::iterator it_cubetasSucesivas = cubetasSucesivas.begin();
				 it_cubetasSucesivas != cubetasSucesivas.end() && !elementoInsertado;
				 it_cubetasSucesivas++)
			{
				elementoInsertado = (*it_cubetasSucesivas)->insertarElementoHash(*elemento);

				if(elementoInsertado)
				{
					this->escribirDatoCubeta((*it_cubetasSucesivas), offsetCubetaActual);
					datoTabla->setCantidadDeElementos( datoTabla->getCantidadDeElementos() + 1);
					this->escribirDatoTabla( datoTabla, this->calcularOffsetBloqueEnTabla(numeroDeBloque));

					//liberamos recursos.
					//delete datoTabla; (en metodo invocador)

					while ( cubetasSucesivas.size() > 1 )
					{
						DatoCubetaHash* cubeta = cubetasSucesivas.back();
						delete cubeta;
						cubetasSucesivas.pop_back();
					}
					//cubetasSucesivas.clear();

				}
				else
				{
					offsetCubetaActual = (*it_cubetasSucesivas)->getOffsetCubetaContinuacion();
				}
			}

		}

		//---------------------------------------------------------------------------------------------------------------------------------------
		//Si todavía no hubo éxito... -------------------------------------------------------------------------------------------------------------------
		//TERCERO...

		//...duplicamos la tabla hasta 5 veces.
		//Si luego de duplicar 5 veces la tabla no se pudo insertar, asumimos que la función de hash es mala y que hay muchas palabras con un valor,
		//y por lo tanto debemos extender la cubeta correspondiente.
		std::vector<DatoCubetaHash*> nuevasCubetasSucesivas;

		if( !elementoInsertado)
		{
			int cantidadIntentosMax = 1;
			for (int intento = 0; intento < cantidadIntentosMax && !elementoInsertado; intento++)
			{
				//insertar elemento con tabla extendida...
				std::cout<<numeroDeBloque<<std::endl; //debug
				this->duplicarTablaHash();

				std::cout<<cubetasSucesivas.size()<<std::endl;
				this->archivoCubetas.flush();
				this->archivoTabla.flush();

				if( intento == 0)
				{
					//Usamos numero de bloque y entrada a la tabla "vieja" que contiene cubetas rebalsadas.
					this->redispersarSucesionCubetas(cubetasSucesivas, numeroDeBloque, datoTabla); //contiene a la cubeta que llega como parametro
				}
				else
				{
					this->redispersarSucesionCubetas(nuevasCubetasSucesivas, numeroDeBloque, datoTabla);
				}
				this->archivoCubetas.flush();
				this->archivoTabla.flush();

				while ( cubetasSucesivas.size() > 1 && intento == 0)
				{
					DatoCubetaHash* cubeta  = cubetasSucesivas.back();
					delete cubeta;
					cubetasSucesivas.pop_back();
				} //Este vector cubetasSucesivas NO SE DEBE USAR MAS. No se hace delete de la cubeta original.

				while ( !nuevasCubetasSucesivas.empty() )
				{
					DatoCubetaHash* cubeta = nuevasCubetasSucesivas.back();
					delete cubeta;
					nuevasCubetasSucesivas.pop_back();
				}

				unsigned int nuevoNumeroDeBloque = this->obtenerNumeroDeBloque(elemento->getPalabra());

				DatoTablaHash* datoTablaNuevo = this->levantarDatoTabla( this->calcularOffsetBloqueEnTabla( nuevoNumeroDeBloque));

				uint32_t offsetCubeta = datoTablaNuevo->getOffsetCubeta();
				bool primerCubeta = true;

				while ( (offsetCubeta != 0 || primerCubeta) && !elementoInsertado )
				{
					nuevasCubetasSucesivas.push_back( this->levantarDatoCubeta( offsetCubeta ));
					elementoInsertado = nuevasCubetasSucesivas.back()->insertarElementoHash(*elemento);

					if(elementoInsertado)
					{
						datoTablaNuevo->setCantidadDeElementos( datoTablaNuevo->getCantidadDeElementos() + 1);
						this->escribirDatoTabla(datoTablaNuevo, this->calcularOffsetBloqueEnTabla( nuevoNumeroDeBloque));
						this->escribirDatoCubeta(nuevasCubetasSucesivas.back(), offsetCubeta);
					}
					else
					{
						offsetCubeta = nuevasCubetasSucesivas.back()->getOffsetCubetaContinuacion();
					}
					primerCubeta = false;
				}

				delete datoTablaNuevo;
			}


			//Si aún no se pudo insertar, extendemos la cubeta
			//CUARTO...
			if (!elementoInsertado)
			{
				unsigned int numeroBloqueConTablaExtendida = this->obtenerNumeroDeBloque( elemento->getPalabra());
				uint32_t offsetDatoTablaPosCrecimiento = this->calcularOffsetBloqueEnTabla( numeroBloqueConTablaExtendida );
				DatoTablaHash* datoTablaPosCrecimiento = this->levantarDatoTabla( offsetDatoTablaPosCrecimiento );

				DatoCubetaHash* datoCubetaExtension = new DatoCubetaHash();
				elementoInsertado = datoCubetaExtension->insertarElementoHash(*elemento);
				uint32_t offsetNuevaCubeta = this->nuevaCubetaAlFinal(datoCubetaExtension);

				//Encadenamos la anterior ultima cubeta con la recien escrita (ahora ultima).
				uint32_t offsetUltimaCubetaDeSerie; //ultima cubeta de la sucesion anterior de cubetas.

				if (nuevasCubetasSucesivas.size() > 1)
				{
					//tomamos el offset de la ultima, que es apuntada por la anterior (penultima).
					offsetUltimaCubetaDeSerie = nuevasCubetasSucesivas.at( cubetasSucesivas.size() - 2)->getOffsetCubetaContinuacion();
				}
				else
				{
					offsetUltimaCubetaDeSerie = datoTablaPosCrecimiento->getOffsetCubeta();
				}

				//Escribimos cubeta que quedo penultima
				nuevasCubetasSucesivas.back()->setOffsetCubetaContinacion(offsetNuevaCubeta);
				this->escribirDatoCubeta( nuevasCubetasSucesivas.back(), offsetUltimaCubetaDeSerie);

				//Actualizamos cantidad de elementos del bloque
				datoTablaPosCrecimiento->setCantidadDeElementos( datoTablaPosCrecimiento->getCantidadDeElementos() + 1);
				this->escribirDatoTabla(datoTablaPosCrecimiento, offsetDatoTablaPosCrecimiento);

				delete datoCubetaExtension;
				delete datoTablaPosCrecimiento;
			}

			//liberamos recursos
			//delete datoTabla; en metodo invocador
			while ( !nuevasCubetasSucesivas.empty() )
			{
				DatoCubetaHash* cubeta = nuevasCubetasSucesivas.back();
				delete cubeta;
				nuevasCubetasSucesivas.pop_back();
			}

		}
	}

	//liberación de recursos.
}

void Hash::insertarElemento(ElementoHash elemento)
{
	std::pair<std::string, uint32_t> registroHash(elemento.getPalabra(), elemento.getOffsetALibro());

	this->insertarClave(registroHash);
}

void Hash::insertarClave(std::pair<std::string, uint32_t> registroHash)
{
	//Elementos a insertar
	uint32_t offsetALibro = registroHash.second;
	std::string palabraClave = registroHash.first;

	ElementoHash elementoAInsertar(palabraClave, offsetALibro);

	//Primero obtenemos el bloque al que irï¿½a la palabra
	unsigned int numeroDeBloqueAPriori = this->obtenerNumeroDeBloque(palabraClave);
	uint32_t offsetDatoTabla = this->calcularOffsetBloqueEnTabla(numeroDeBloqueAPriori);

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

	}
	else
	{
		//Delegamos el manejo del desborde a otro método
		std::cout<<"redispersoooooo.."<<std::endl;
		this->manejarDesbordeCubeta(&elementoAInsertar, datoCubeta, datoTablaAPriori, numeroDeBloqueAPriori);

		//este método libera los recursos de datoCubeta y datoTabla.
	}

	//liberación local de recursos.
	delete datoCubeta;
	delete datoTablaAPriori;
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

void Hash::escribirArchivoIndice(fstream &archivoSalidaIndice)
{
	stringstream ssIndice;
	ssIndice << "INDICE HASH\n\n";
	ssIndice << "Nombre de archivo de tabla de hash: " << this->nombreArchivoTabla << "\n";
	ssIndice << "Nombre de archivo de cubetas de hash (datos): " << this->nombreArchivoCubetas << "\n";
	ssIndice << "Cantidad de entradas de la tabla (bloques direccionables): " << this->cantidadDeBloques << "\n";
	ssIndice << "Cantidad de cubetas (unidades de almacenamiento de datos) efectivas: " << this->cantidadDeCubetas << "\n";

	archivoSalidaIndice<<ssIndice.str();
}

void Hash::escribirArchivosTablaDatosYEspaciosLibres(fstream &archivoSalidaTabla, fstream &archivoSalidaDatos, fstream &archivoSalidaEspaciosLibres)
{


	archivoSalidaTabla << "TABLA DE HASH\n\n";
	archivoSalidaDatos << "CUBETAS DE HASH\n\n";
	archivoSalidaEspaciosLibres << "REGISTRO DE ESPACIOS LIBRES\n";

	archivoSalidaEspaciosLibres << "Se muestran las cubetas que no tienen Elementos (claves) guardados, aunque están siempre incializadas y prestas a recibirlos\n\n";

	//Se recorren en orden las entradas de la tabla, y las cubetas a medida que son direccionadas.
	for( unsigned int numeroDeBloque = 0; numeroDeBloque < this->cantidadDeBloques; numeroDeBloque++)
	{
		DatoTablaHash* datoTabla = this->levantarDatoTabla( this->calcularOffsetBloqueEnTabla(numeroDeBloque));
		stringstream ssTabla;

		//Escribimos archivo de tabla
		ssTabla << "Número de Bloque: " << numeroDeBloque << "\n";
		ssTabla << "*** Cantidad de Elementos del bloque: " << datoTabla->getCantidadDeElementos() << "\n";
		ssTabla << "*** Offset a la Cubeta de Datos Inicial del bloque: " << datoTabla->getOffsetCubeta() << "\n";
		ssTabla << "\n";

		//Escribimos cubetas de la entrada de la tabla en archivo de salida de cubetas.
		bool quedanCubetas = true;
		uint32_t offsetCubeta = datoTabla->getOffsetCubeta();
		unsigned int numeroDeCubetaSucesiva = 1;
		while (quedanCubetas)
		{
			DatoCubetaHash* datoCubeta = this->levantarDatoCubeta( offsetCubeta );
			stringstream ssCubetas;

			ssCubetas << "Cubeta del Bloque Número " << numeroDeBloque << "\n";
			ssCubetas << "Número de cubeta del mismo bloque: " << numeroDeCubetaSucesiva << "\n";
			ssCubetas << "Cantidad de Elementos (Claves) almacenados en la cubeta: " << datoCubeta->getCantidadDeElementos() << "\n";
			ssCubetas << "Bytes libres en la cubeta: " << datoCubeta->getBytesLibres() <<"\n";
			ssCubetas << "Offset en disco de la cubeta Actual: " << offsetCubeta << "		";
			ssCubetas << "Offset de cubeta continuación: " << datoCubeta->getOffsetCubetaContinuacion() << "\n";

			//Registro de cubetas libres:
			if (datoCubeta->getCantidadDeElementos() == 0)// && numeroDeCubetaSucesiva > 1)
			{
				stringstream ssLibre;
				ssLibre << "Bloque que contiene la cubeta libre: " << numeroDeBloque << "\n";
				ssLibre << "Número de cubeta sucesiva del bloque: " << numeroDeCubetaSucesiva << "\n";
				ssLibre << "Offset de la cubeta en el archivo: " << offsetCubeta << "\n";

				archivoSalidaEspaciosLibres << ssLibre.str();
			}

			delete datoCubeta;

			archivoSalidaDatos << ssCubetas.str();
			archivoSalidaDatos<< "\n";
			quedanCubetas = (offsetCubeta != 0);
			offsetCubeta = datoCubeta->getOffsetCubetaContinuacion();
			numeroDeCubetaSucesiva++;
		}
		archivoSalidaDatos<< "\n\n";


		delete datoTabla;

		//Reiniciamos flujo de datos
		archivoSalidaTabla<<ssTabla.str();
		ssTabla.str("");
		ssTabla.clear();
	}
}

void Hash::escribirEstructuraEnArchivos(std::string baseNombreArchivo)
{
	//TODO tomar el path en que deben ponerse estos archivos de la clase de paulus...

	//Se generan los archivos según especificaciones del enunciado del TP.
	std::string nombreArchivoSalidaIndice;
	nombreArchivoSalidaIndice.append(baseNombreArchivo);
	nombreArchivoSalidaIndice.append("_indice.txt");

	std::string nombreArchivoSalidaTabla;
	nombreArchivoSalidaTabla.append(baseNombreArchivo);
	nombreArchivoSalidaTabla.append("_tabla.txt");

	std::string nombreArchivoSalidaLibres;
	nombreArchivoSalidaLibres.append(baseNombreArchivo);
	nombreArchivoSalidaLibres.append("_libres.txt");

	std::string nombreArchivoSalidaDatos;
	nombreArchivoSalidaDatos.append(baseNombreArchivo);
	nombreArchivoSalidaDatos.append("_datos.txt");

	//ABRIMOS ARCHIVOS
	//***************
	fstream archivoSalidaIndice;
	bool arcIndiceOk = ManejadorArchivo::Crear(nombreArchivoSalidaIndice.c_str(), archivoSalidaIndice, false);

	fstream archivoSalidaTabla;
	bool arcTablaOk = ManejadorArchivo::Crear(nombreArchivoSalidaTabla.c_str(), archivoSalidaTabla, false);

	fstream archivoSalidaLibres;
	bool arcLibresOk = ManejadorArchivo::Crear(nombreArchivoSalidaLibres.c_str(), archivoSalidaLibres, false);

	fstream archivoSalidaDatos;
	bool arcDatosOk = ManejadorArchivo::Crear(nombreArchivoSalidaDatos.c_str(), archivoSalidaDatos, false);

	if ( arcIndiceOk && arcTablaOk && arcLibresOk && arcDatosOk)
	{
		//ESCRITURA DE ARCHIVOS
		//*********************

		//ARCHIVO DE INDICE
		this->escribirArchivoIndice(archivoSalidaIndice);

		//ARCHIVOs DE TABLA Y DE DATOS
		this->escribirArchivosTablaDatosYEspaciosLibres(archivoSalidaTabla, archivoSalidaDatos, archivoSalidaLibres);

		//SALIDA POR PANTALLA Y CIERRE DE ARCHIVOS
		//****************************************
		std::cout<<"Generados los siguientes archivos: "<<std::endl;
		std::cout<<"********* *** *******************"<<std::endl<<std::endl;
		std::cout<<nombreArchivoSalidaIndice<<std::endl;
		std::cout<<nombreArchivoSalidaTabla<<std::endl;
		std::cout<<nombreArchivoSalidaLibres<<std::endl;
		std::cout<<nombreArchivoSalidaDatos<<std::endl;

		ManejadorArchivo::Cerrar(archivoSalidaIndice);
		ManejadorArchivo::Cerrar(archivoSalidaTabla);
		ManejadorArchivo::Cerrar(archivoSalidaLibres);
		ManejadorArchivo::Cerrar(archivoSalidaDatos);
	}
	else
	{
		if(arcIndiceOk)
			ManejadorArchivo::Cerrar(archivoSalidaIndice);
		if(arcTablaOk)
			ManejadorArchivo::Cerrar(archivoSalidaTabla);
		if(arcLibresOk)
			ManejadorArchivo::Cerrar(archivoSalidaLibres);
		if(arcDatosOk)
			ManejadorArchivo::Cerrar(archivoSalidaDatos);
		std::cout<<"ERROR EN LA GENERACIÓN DE ARCHIVOS DE SALIDA"<<std::endl;
	}
}

Hash::~Hash()
{
	Cerrar(archivoTabla);
	Cerrar(archivoCubetas);
}

