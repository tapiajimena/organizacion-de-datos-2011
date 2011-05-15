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

Hash::Hash(std::string nombreArchivoTabla, std::string nombreArchivoCubetas) {

	CrearSiNoExiste(nombreArchivoTabla.c_str(), archivoTabla);
	CrearSiNoExiste(nombreArchivoCubetas.c_str(), archivoCubetas);

	this->nombreArchivoTabla = nombreArchivoTabla;
	this->nombreArchivoCubetas = nombreArchivoCubetas;

	this->cantidadDeBloques = 0;
	this->cantidadDeCubetas = 0;

	if (ManejadorArchivo::GetSizeArchivo(this->archivoTabla) == 0) {
		//Creamos los dos primeros bloques de la tabla (vacï¿½as).
		DatoTablaHash datoTabla0 = DatoTablaHash();
		DatoTablaHash datoTabla1 = DatoTablaHash();

		//Agregamos los dos primeros bloques...
		datoTabla0.setOffsetCubeta(0);
		datoTabla0.setCantidadDeElementos(0);

		datoTabla1.setOffsetCubeta(TAMANIOCUBETA);
		datoTabla1.setCantidadDeElementos(0);

		this->escribirDatoTabla(&datoTabla0, this->calcularOffsetBloqueEnTabla(
				0));
		this->escribirDatoTabla(&datoTabla1, this->calcularOffsetBloqueEnTabla(
				1));
		this->cantidadDeBloques = 2;
		//Y sus correspondientes cubetas...
		DatoCubetaHash datoCubeta0 = DatoCubetaHash(); //inicializan en cero.
		DatoCubetaHash datoCubeta1 = DatoCubetaHash();

		this->escribirDatoCubeta(&datoCubeta0, datoTabla0.getOffsetCubeta());
		this->escribirDatoCubeta(&datoCubeta1, datoTabla1.getOffsetCubeta());
		this->cantidadDeCubetas = 2;
	} else {
		//Calculamos la cantidad de bloques
		this->cantidadDeBloques = (unsigned int) (GetSizeArchivo(archivoTabla)
				/ TAMANIODATOTABLA);

		this->cantidadDeCubetas
				= (unsigned int) (GetSizeArchivo(archivoCubetas)
						/ TAMANIOCUBETA);
	}
}

unsigned int Hash::getCantidadDeBloques() {
	return this->cantidadDeBloques;
}

std::string Hash::getNombreArchivoTabla() {
	return this->nombreArchivoTabla;
}

std::string Hash::getNombreArchivoCubetas() {
	return this->nombreArchivoCubetas;
}
//FUNCIONES DE HASH ************************************************

//Suma del valor ASCII de los caracteres (deprecated). Andar anda, pero dispersa muy mal.
/*
unsigned int Hash::funcionHash(std::string claveADispersar) {
	unsigned int valorHash = 0;
	for (unsigned int x = 0; x < claveADispersar.size(); x++) {
		valorHash = valorHash + (unsigned int) claveADispersar.at(x);
	}

	return valorHash;
}
*/

//Algoritmo DJB2 ( http://www.cse.yorku.ca/~oz/hash.html , es muy conocido)
unsigned int Hash::funcionHash(std::string claveADispersar)
{
	//char* str = new char[claveADispersar.size()];
	//copy(claveADispersar.begin(), claveADispersar.end(), str);

	unsigned int hash = 5381;
	int nroCaracter = 0;
	int c;

	while (nroCaracter < claveADispersar.size()) //c = *str++)
	{
		c = (int)claveADispersar.at(nroCaracter);
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
		nroCaracter++;
	}

	//delete []str;
	return hash;
}

// ************************************************
unsigned int Hash::obtenerNumeroDeBloque(unsigned int valorDispersado,
		unsigned int cantidadDeBloques) {
	unsigned int valorRetorno = (unsigned int) valorDispersado
			% cantidadDeBloques;

	return valorRetorno;
}

unsigned int Hash::obtenerNumeroDeBloque(std::string claveADispersar) {
	unsigned int valorHash = this->funcionHash(claveADispersar);

	return this->obtenerNumeroDeBloque(valorHash, this->cantidadDeBloques);
}

uint32_t Hash::calcularOffsetBloqueEnTabla(unsigned int numeroBloque) {
	return (numeroBloque * TAMANIODATOTABLA); //Se busca en la tabla 1ero y luego en archivo de cubetas.
}

DatoTablaHash* Hash::levantarDatoTabla(uint32_t offsetDatoTabla) {
	DatoTablaHash* datoTabla = NULL;
	std::stringstream ss;

	ManejadorArchivo::RecuperarEstructura(this->archivoTabla, ss,
			offsetDatoTabla, TAMANIODATOTABLA);

	datoTabla = new DatoTablaHash(&ss);

	return datoTabla;
}

DatoCubetaHash* Hash::levantarDatoCubeta(uint32_t offsetCubeta) {
	DatoCubetaHash* datoCubeta = NULL;

	std::stringstream ss;

	ManejadorArchivo::RecuperarEstructura(this->archivoCubetas, ss,
			offsetCubeta, TAMANIOCUBETA);

	datoCubeta = new DatoCubetaHash(&ss);

	return datoCubeta;
}

std::vector< std::pair<DatoCubetaHash*, uint32_t> > Hash::levantarSucesionDeCubetas(uint32_t offsetPrimerCubeta)
{
	std::vector< std::pair<DatoCubetaHash*, uint32_t> > sucesionDeCubetas;
	std::pair<DatoCubetaHash*, uint32_t> parCubetaOffset( this->levantarDatoCubeta(offsetPrimerCubeta), offsetPrimerCubeta);
	sucesionDeCubetas.push_back( parCubetaOffset);

	uint32_t offsetProximaCubeta = sucesionDeCubetas.back().first->getOffsetCubetaContinuacion();

	while (offsetProximaCubeta != 0)
	{
		parCubetaOffset.first = this->levantarDatoCubeta( offsetProximaCubeta);
		parCubetaOffset.second = offsetProximaCubeta;

		sucesionDeCubetas.push_back( parCubetaOffset );

		offsetProximaCubeta = sucesionDeCubetas.back().first->getOffsetCubetaContinuacion();
	}

	return sucesionDeCubetas;
}

bool Hash::elementoYaInsertado(std::vector< std::pair<DatoCubetaHash*, uint32_t> >sucesionDeCubetas, ElementoHash elemento)
{
	bool encontrado = false;
	std::vector< std::pair<DatoCubetaHash*, uint32_t> >::iterator it_cubetas = sucesionDeCubetas.begin();

	while (!encontrado && it_cubetas!=sucesionDeCubetas.end())
	{
		encontrado = it_cubetas->first->contieneElemento(elemento);
		it_cubetas++;
	}

	return encontrado;
}

void Hash::escribirDatoCubeta(DatoCubetaHash* datoCubeta, uint32_t offsetCubeta) {
	stringstream ss;//(ios_base::in | ios_base::out);
	datoCubeta->serializarCubeta(&ss);

	int caracteres = ss.str().size();

	for (int x = 0; x < TAMANIOCUBETA - caracteres; x++) {
		ss << BYTENULOENDISCO;
	}

	ManejadorArchivo::Escribir(archivoCubetas, &ss, offsetCubeta);

	//este método Escribir de abajo no reserva espacio adicional en disco para alcanzar TAMANIOCUBETA, no me sirve.
	//ManejadorArchivo::Escribir(&archivoCubetas, &ss, offsetCubeta, TAMANIOCUBETA);

}

void Hash::escribirDatoTabla(DatoTablaHash* datoTabla, uint32_t offsetDatoTabla) {
	//stringstream ss(ios_base::in | ios_base::out);
	stringstream ss;
	datoTabla->serializarDatoTabla(&ss);
	ManejadorArchivo::Escribir(&archivoTabla, &ss, offsetDatoTabla,
			TAMANIODATOTABLA);
}

std::vector<uint32_t> Hash::acumularResultados(DatoCubetaHash* &datoCubeta, std::string palabra)
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
		std::vector<ElementoHash> elementosDeCubeta = datoCubeta->getElementos();

		for (unsigned int x = 0; x < elementosDeCubeta.size(); x++)
		{
			ElementoHash elemento = elementosDeCubeta.at(x);

			if (elemento.getPalabra() == palabra)
			{
				//Verificamos si el offset de ese libro ya fue ingresado. Si asï¿½ fue, no se vuelve a ingresar.
				bool yaFueIngresado = false;
				std::vector<uint32_t>::iterator it;

				for (it = resultados.begin(); it != resultados.end() && !yaFueIngresado; it++)
				{
					if ((*it) == elemento.getOffsetALibro())
						yaFueIngresado = true;
				}

				if (!yaFueIngresado)
				{
					resultados.push_back(elemento.getOffsetALibro());
				}

			}
		}

		if (siguienteCubeta)
		{
			delete datoCubeta;
			datoCubeta = this->levantarDatoCubeta(offsetSiguienteCubeta);
		}
	}
	return resultados;
}

//std::vector<unsigned int> Hash::obtenerBloquesConMismaCubeta(
std::vector< std::pair<DatoTablaHash*, uint32_t> > Hash::obtenerBloquesConMismaCubeta( unsigned int nroDeBloque, uint32_t offsetCubeta)
{
	std::vector< std::pair<DatoTablaHash*, uint32_t> > entradasDeTabla; // Par: datoTablaHash leído y su offset en disco

	//Ahora levantamos todos los bloques parientes que apunten a la misma cubeta.
	for (unsigned int numeroBloqueTemporal = 0;
			numeroBloqueTemporal < this->getCantidadDeBloques();
			numeroBloqueTemporal++)
	{
		uint32_t offsetDatoTabla = this->calcularOffsetBloqueEnTabla(numeroBloqueTemporal);//*it_nrosBloque );
		DatoTablaHash* datoTabla = this->levantarDatoTabla(offsetDatoTabla); //recordar que datoTabla equivale a bloque. La tabla contiene bloques que direccionan cubetas.

		if (datoTabla->getOffsetCubeta() == offsetCubeta && numeroBloqueTemporal != nroDeBloque)
		{
			std::pair<DatoTablaHash*, uint32_t> datoTablaYNroBloque( datoTabla, offsetDatoTabla);
			entradasDeTabla.push_back( datoTablaYNroBloque );
		}
		else
		{
			delete datoTabla;
		}
	}

	return entradasDeTabla;
}

uint32_t Hash::nuevaCubetaAlFinal(DatoCubetaHash* datoCubeta) {
	uint32_t offsetNuevaCubeta = this->cantidadDeCubetas * TAMANIOCUBETA;
	this->escribirDatoCubeta(datoCubeta, offsetNuevaCubeta);
	this->cantidadDeCubetas++;

	return offsetNuevaCubeta;
}

void Hash::duplicarTablaHash()
{
	unsigned int nuevaCantidadDeBloques = (unsigned int) this->cantidadDeBloques * 2;

	for (unsigned int nroBloque = this->cantidadDeBloques; nroBloque <= nuevaCantidadDeBloques - 1; nroBloque++)
	{
		uint32_t offsetNuevoBloqueTabla = this->calcularOffsetBloqueEnTabla(nroBloque);
		DatoTablaHash nuevoDatoTabla; //(estructura estï¿½tica)

		//Bloque al que se direccionarÃ­an los elementos del actual con la funciÃ³n de hash nueva (segÃºn cantidad de bloques vieja).
		unsigned int nroBloqueAnteriorEquivalente = nroBloque % this->cantidadDeBloques;

		uint32_t offsetBloqueEquivalenteAnterior = this->calcularOffsetBloqueEnTabla(nroBloqueAnteriorEquivalente);

		DatoTablaHash* datoTablaEquivalenteAnterior = this->levantarDatoTabla(offsetBloqueEquivalenteAnterior);

		nuevoDatoTabla.setOffsetCubeta(datoTablaEquivalenteAnterior->getOffsetCubeta());
		nuevoDatoTabla.setCantidadDeElementos(datoTablaEquivalenteAnterior->getCantidadDeElementos());

		//No se usa ahora, pero vale la pena recordar esta relaciÃ³n: [X mod 2N] mod N = X mod N

		//Nota: no se actualiza (ni se debe hacerlo) la cantidad de bloques hasta terminar de duplicar toda la tabla.
		this->escribirDatoTabla(&nuevoDatoTabla, offsetNuevoBloqueTabla);

		delete datoTablaEquivalenteAnterior;
	}

	this->cantidadDeBloques = nuevaCantidadDeBloques;
}

void Hash::redispersarSucesionCubetas(std::vector<std::pair<DatoCubetaHash*, uint32_t> > sucesionDeCubetas, unsigned int numeroDeBloque, DatoTablaHash* datoTabla)
{
	std::vector< std::pair<DatoTablaHash*, uint32_t> > bloquesConMismaCubeta = this->obtenerBloquesConMismaCubeta(numeroDeBloque, datoTabla->getOffsetCubeta());

	//Inicializamos cubetas vacías para los bloques que compartían la cubeta desbordada.
	for (std::vector< std::pair<DatoTablaHash*, uint32_t> >::iterator it_bloques = bloquesConMismaCubeta.begin();
			it_bloques != bloquesConMismaCubeta.end();
			it_bloques++)
	{
		DatoCubetaHash* datoCubeta = new DatoCubetaHash();
		uint32_t offsetCubeta = this->nuevaCubetaAlFinal(datoCubeta);

		DatoTablaHash* datoTablaInicializado = it_bloques->first;
		datoTablaInicializado->setCantidadDeElementos(0);
		datoTablaInicializado->setOffsetCubeta(offsetCubeta);

		this->escribirDatoTabla(datoTablaInicializado, it_bloques->second);
		delete datoTablaInicializado;
		delete datoCubeta;
	}

	//Ahora redispersamos los datos de la cubeta compartida anteriormente (la sucesiï¿½n de cubetas estï¿½ en memoria).

	for (std::vector<std::pair<DatoCubetaHash*, uint32_t> >::iterator it_sucesionDeCubetas = sucesionDeCubetas.begin();
			it_sucesionDeCubetas != sucesionDeCubetas.end();
			it_sucesionDeCubetas++)
	{
		std::vector<ElementoHash> elementos = it_sucesionDeCubetas->first->getElementos(); //nos da una copia.

		for (std::vector<ElementoHash>::iterator it_elementos =	elementos.begin();
				it_elementos != elementos.end();
				it_elementos++)
		{
			unsigned int nuevoNumeroDeBloque = this->obtenerNumeroDeBloque(it_elementos->getPalabra());

			//Si al elemento le corresponde otro nï¿½mero de bloque, se lo redispersa en la tabla.
			if (nuevoNumeroDeBloque != numeroDeBloque)
			{
				//Redispersamos el elemento en la tabla (cae y se escribe en otro bloque y su direcciï¿½n se corresponde con el tamaï¿½o de tabla actual):
				this->insertarElemento(*it_elementos);

				//Y lo eliminamos de la cubeta a la que no le corresponde mï¿½s.
				it_sucesionDeCubetas->first->eliminarElementoHash(*it_elementos);
				datoTabla->setCantidadDeElementos( datoTabla->getCantidadDeElementos() - 1);
			}
		}

		//Reescribimos la cubeta que eventualmente perdiï¿½ elementos al redistribuirlos.
		this->escribirDatoCubeta(it_sucesionDeCubetas->first, it_sucesionDeCubetas->second);
	}

	this->escribirDatoTabla(datoTabla, this->calcularOffsetBloqueEnTabla(numeroDeBloque));
}

//Metodos primarios para trabajar desborde de cubeta******************************

//Cuarta y última instancia de resolución de desborde de cubeta
bool Hash::insertarEnNuevaCubetaYExtenderCubetaAnterior(std::vector<std::pair<DatoCubetaHash*, uint32_t> > sucesionDeCubetas, DatoTablaHash* datoTabla, unsigned int numeroDeBloque, ElementoHash* elemento)
{
	bool elementoInsertado = false;

	DatoCubetaHash* datoCubetaExtension = new DatoCubetaHash();
	elementoInsertado = datoCubetaExtension->insertarElementoHash(*elemento); //siempre entra en una cubeta nueva.
	uint32_t offsetNuevaCubeta = this->nuevaCubetaAlFinal(datoCubetaExtension);


	//Escribimos cubeta que quedo penultima
	sucesionDeCubetas.back().first->setOffsetCubetaContinacion(offsetNuevaCubeta);
	this->escribirDatoCubeta(sucesionDeCubetas.back().first, sucesionDeCubetas.back().second);

	//Actualizamos cantidad de elementos del bloque
	datoTabla->setCantidadDeElementos(datoTabla->getCantidadDeElementos() + 1);
	this->escribirDatoTabla(datoTabla, this->calcularOffsetBloqueEnTabla( numeroDeBloque ));

	//std::vector<std::pair<DatoTablaHash*, uint32_t> > bloquesConMismaCubeta = this->obtenerBloquesConMismaCubeta( numeroDeBloque, sucesionDeCubetas.begin()->second);
	//this->actualizarCantidadDeElementosDeBloquesQueCompartenCubeta( bloquesConMismaCubeta, +1);

	delete datoCubetaExtension;

	return elementoInsertado;
}

//Tercera instancia de resolución de desborde
bool Hash::probarInsertarTrasDuplicarTamanioDeTabla(std::vector<std::pair<DatoCubetaHash*, uint32_t> > &sucesionDeCubetas,
													ElementoHash* elemento, DatoTablaHash* &datoTabla, unsigned int &numeroDeBloque)
{
	bool elementoInsertado = false;

	int cantidadIntentosMax = 1; //Por ahora dejar siempre en uno!!!

	for (int intento = 0; intento < cantidadIntentosMax	&& !elementoInsertado; intento++)
	{
		//insertar elemento con tabla extendida...
		this->duplicarTablaHash();
		//this->archivoCubetas.flush();
		//this->archivoTabla.flush();

		this->redispersarSucesionCubetas(sucesionDeCubetas, numeroDeBloque, datoTabla);
		//this->archivoCubetas.flush();
		//this->archivoTabla.flush();

		//Tras duplicar la tabla no sabemos si el dato se insertará en el mismo bloque que con el tamaño anterior
		while (!sucesionDeCubetas.empty())
		{
			DatoCubetaHash* cubeta = sucesionDeCubetas.back().first;
			delete cubeta;
			sucesionDeCubetas.pop_back();
		}

		//Calculamos la nueva entrada en la tabla con el nuevo tamaño de hash...
		numeroDeBloque = this->obtenerNumeroDeBloque(elemento->getPalabra());

		DatoTablaHash* datoTablaNuevo = this->levantarDatoTabla(this->calcularOffsetBloqueEnTabla(numeroDeBloque));

		uint32_t offsetCubeta = datoTablaNuevo->getOffsetCubeta();
		bool primerCubeta = true;

		while ((offsetCubeta != 0 || primerCubeta) && !elementoInsertado)
		{
			std::pair<DatoCubetaHash*, uint32_t> parCubetaOffset( this->levantarDatoCubeta(offsetCubeta), offsetCubeta);
			sucesionDeCubetas.push_back(parCubetaOffset);
			elementoInsertado = sucesionDeCubetas.back().first->insertarElementoHash(*elemento);

			if (elementoInsertado)
			{
				this->escribirDatoCubeta(sucesionDeCubetas.back().first, offsetCubeta);

				datoTablaNuevo->setCantidadDeElementos(	datoTablaNuevo->getCantidadDeElementos() + 1);
				this->escribirDatoTabla(datoTablaNuevo,	this->calcularOffsetBloqueEnTabla(numeroDeBloque));

				//std::vector<std::pair<DatoTablaHash*, uint32_t> > bloquesConMismaCubeta = this->obtenerBloquesConMismaCubeta(numeroDeBloque, offsetCubeta);
				//this->actualizarCantidadDeElementosDeBloquesQueCompartenCubeta(bloquesConMismaCubeta, +1);
			}
			else
			{
				offsetCubeta = sucesionDeCubetas.back().first->getOffsetCubetaContinuacion();
			}
			primerCubeta = false;
		}

		//Actualizamos los valores de puntero a la tabla, para poder seguir operando de ser necesario y que apunten
		//a donde se tiene que insertar el dato
		delete datoTabla;
		datoTabla = datoTablaNuevo;
		//numeroDeBloque ya se actualizó, y lo mismo que datoTabla, está pasado como parámetro por referencia
	}
	return elementoInsertado;
}

//Segunda instancia de resolución de desborde
bool Hash::probarInsertarEnSucesionDeCubetasTrasRedispersion(std::vector<std::pair<DatoCubetaHash*, uint32_t> > &sucesionDeCubetas,
															ElementoHash* elemento, DatoTablaHash* datoTabla, unsigned int numeroDeBloque)
{
	bool elementoInsertado = false;

	//redispersamos sucesión de cubetas...
	this->redispersarSucesionCubetas(sucesionDeCubetas, numeroDeBloque, datoTabla);

	//e intentamos meter el dato en alguna cubeta de la sucesiï¿½n, a ver si se hizo lugar...
	for (std::vector<std::pair<DatoCubetaHash*, uint32_t> >::iterator it_sucesionDeCubetas = sucesionDeCubetas.begin();
			it_sucesionDeCubetas != sucesionDeCubetas.end() && !elementoInsertado;
			it_sucesionDeCubetas++)
	{

		//todo sacar
		//this->archivoCubetas.flush();
		//this->archivoTabla.flush();


		elementoInsertado = it_sucesionDeCubetas->first->insertarElementoHash(*elemento);

		if (elementoInsertado)
		{
			this->escribirDatoCubeta(it_sucesionDeCubetas->first, it_sucesionDeCubetas->second);

			//Cantidad de elementos del bloque...
			datoTabla->setCantidadDeElementos(datoTabla->getCantidadDeElementos() + 1);
			this->escribirDatoTabla(datoTabla, this->calcularOffsetBloqueEnTabla(numeroDeBloque));

			//Y de todos los bloques que comparten las cubetas
			//std::vector<std::pair<DatoTablaHash*, uint32_t> > bloquesQueCompartenCubeta = this->obtenerBloquesConMismaCubeta( numeroDeBloque, it_sucesionDeCubetas->second);
			//this->actualizarCantidadDeElementosDeBloquesQueCompartenCubeta(bloquesQueCompartenCubeta, +1);

		}
	}

	return elementoInsertado;
}


//Primer instancia de resolucion de desborde
bool Hash::probarInsertarEnSucesionDeCubetas(std::vector< std::pair<DatoCubetaHash*, uint32_t> > cubetasSucesivas, ElementoHash* elemento, DatoTablaHash* datoTabla, unsigned int numeroDeBloque)
{

	bool elementoInsertado = false;

	std::vector< std::pair<DatoCubetaHash*, uint32_t> >::iterator it_parCubetaOffset = cubetasSucesivas.begin();

	while( it_parCubetaOffset != cubetasSucesivas.end() && !elementoInsertado)
	{
		elementoInsertado = it_parCubetaOffset->first->insertarElementoHash(*elemento);

		if (!elementoInsertado)
		{
			it_parCubetaOffset++; //si se inserta el elemento, it_parCubetaOffset queda apuntando a la cubeta en que se insertó
		}
	}

	if(elementoInsertado)
	{
		//Actualizamos la cantidad de elementos del bloque en el que entramos...
		datoTabla->setCantidadDeElementos( datoTabla->getCantidadDeElementos() + 1);
		this->escribirDatoTabla( datoTabla, this->calcularOffsetBloqueEnTabla(numeroDeBloque));

		//...y la actualizamos en todos los bloques que compartan la cubeta
		//std::vector<std::pair<DatoTablaHash*, uint32_t> > bloquesQueCompartenCubeta = this->obtenerBloquesConMismaCubeta(numeroDeBloque, it_parCubetaOffset->second);
		//this->actualizarCantidadDeElementosDeBloquesQueCompartenCubeta(bloquesQueCompartenCubeta, +1);

		this->escribirDatoCubeta( it_parCubetaOffset->first, it_parCubetaOffset->second);
	}

	return elementoInsertado;
}

//Rerrefactorizo metodo
void Hash::insertarElementoEnCubeta(ElementoHash* elemento,
									std::vector< std::pair<DatoCubetaHash*, uint32_t> > &sucesionDeCubetas,
									DatoTablaHash* &datoTabla,
									unsigned int numeroDeBloque)
{
	bool elementoInsertado = false;
	bool tablaDuplicada = false;

	//1er intento: probamos insertar el elemento en las cubetas de datos ya creadas para ese bloque
	elementoInsertado = probarInsertarEnSucesionDeCubetas( sucesionDeCubetas, elemento, datoTabla, numeroDeBloque);

	if(!elementoInsertado)
	{
		if( sucesionDeCubetas.size() >= 1)
		{
			//2do intento: si la cubeta tiene extensiones (pero no se pudo insertar en ellas),
			// probamos inicializar cubetas vacías para todos los bloques que comparten la sucesión de cubetas
			// y redispersar todos los elementos y luego volvemos a tratar de insertar nuestro elemento.
			elementoInsertado = this->probarInsertarEnSucesionDeCubetasTrasRedispersion(sucesionDeCubetas, elemento, datoTabla, numeroDeBloque);
		}

		if( !elementoInsertado)
		{
			//3er intento: duplicamos el tamaño de tabla y tratamos de insertar el elemento nuevamente.
			elementoInsertado = this->probarInsertarTrasDuplicarTamanioDeTabla(sucesionDeCubetas, elemento, datoTabla, numeroDeBloque);

			tablaDuplicada = true;

			if( !elementoInsertado )
			{
				//4to intento y último: creamos una cubeta nueva al final y extendemos el bloque al que
				//corresponde la clave del elemento a ingresar. Asumimos que un elemento siempre cabe en una cubeta nueva.
				elementoInsertado = this->insertarEnNuevaCubetaYExtenderCubetaAnterior(sucesionDeCubetas, datoTabla, numeroDeBloque, elemento);

				//en esta instancia elementoInsertado debe ser siempre true.
				//elementoInsertado = true;
			}
		}
	}
}

 void Hash::actualizarCantidadDeElementosDeBloquesQueCompartenCubeta(std::vector< std::pair<DatoTablaHash*, uint32_t> > bloquesQueCompartenCubeta, int diferenciaElementos)
 {
	for( std::vector< std::pair<DatoTablaHash*, uint32_t> >::iterator it_bloques = bloquesQueCompartenCubeta.begin();
			it_bloques != bloquesQueCompartenCubeta.end();
			it_bloques++)
	{
		DatoTablaHash* datoTablaCubetaCompartida = it_bloques->first;
		datoTablaCubetaCompartida->setCantidadDeElementos( datoTablaCubetaCompartida->getCantidadDeElementos() + diferenciaElementos);
		this->escribirDatoTabla(datoTablaCubetaCompartida, it_bloques->second);
		delete datoTablaCubetaCompartida;
	}

 }

void Hash::eliminarElemento(ElementoHash elemento)
{
	unsigned int numeroBloque = this->obtenerNumeroDeBloque(elemento.getPalabra());

	uint32_t offsetDatoTabla = this->calcularOffsetBloqueEnTabla(numeroBloque);

	DatoTablaHash* datoTabla = this->levantarDatoTabla(offsetDatoTabla);

	uint32_t offsetCubetaActual = datoTabla->getOffsetCubeta();

	std::vector< std::pair<DatoTablaHash*, uint32_t> > bloquesCompartiendoCubeta = this->obtenerBloquesConMismaCubeta( numeroBloque, offsetCubetaActual);

	DatoCubetaHash* datoCubeta = this->levantarDatoCubeta(offsetCubetaActual);

	bool encontrado = false;
	bool siguienteCubeta = true; //indica si hay siguiente cubeta donde continuan los datos de la presente.
	uint32_t offsetSiguienteCubeta;

	while (siguienteCubeta && !encontrado)
	{
		if (datoCubeta->contieneElemento(elemento))
		{
			datoCubeta->eliminarElementoHash(elemento);
			this->eliminarElementoCubetaEnDisco(offsetCubetaActual,datoCubeta);

			//eliminamos el dato de la tabla...
			this->actualizarCantidadDeElementosDeBloquesQueCompartenCubeta(bloquesCompartiendoCubeta, -1);
			datoTabla->setCantidadDeElementos( datoTabla->getCantidadDeElementos() - 1);
			this->escribirDatoTabla(datoTabla, offsetDatoTabla);

			encontrado = true;
		}
		else
		{
			offsetSiguienteCubeta = datoCubeta->getOffsetCubetaContinuacion();
			if (offsetSiguienteCubeta != 0)
			{
				delete datoCubeta;
				datoCubeta = this->levantarDatoCubeta(offsetSiguienteCubeta);
			}
			else
			{
				siguienteCubeta = false;
			}
		}
	}

	delete datoTabla;
	delete datoCubeta;

}

void Hash::eliminarElementoCubetaEnDisco(uint32_t offsetCubetaActual, DatoCubetaHash* datoCubetaActual) {
	escribirDatoCubeta(datoCubetaActual,offsetCubetaActual);
}

void Hash::insertarElemento(ElementoHash elemento) {
	std::pair<std::string, uint32_t> registroHash(elemento.getPalabra(),
			elemento.getOffsetALibro());

	this->insertarClave(registroHash);
}

void Hash::insertarClave(std::pair<std::string, uint32_t> registroHash) {
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

	std::vector< std::pair<DatoCubetaHash*, uint32_t> > sucesionDeCubetas = this->levantarSucesionDeCubetas(offsetCubeta);

	if ( !elementoYaInsertado(sucesionDeCubetas, elementoAInsertar))
	{
		//Método mágico...
		this->insertarElementoEnCubeta(&elementoAInsertar, sucesionDeCubetas, datoTablaAPriori, numeroDeBloqueAPriori);

	}

	//liberación de recursos...
	while ( !sucesionDeCubetas.empty())
	{
		DatoCubetaHash* cubeta = sucesionDeCubetas.back().first;
		delete cubeta;
		sucesionDeCubetas.pop_back();
	}

	delete datoTablaAPriori;

	//Debug:
	this->archivoCubetas.flush();
	this->archivoTabla.flush();
}

void Hash::eliminarElemento(std::pair<std::string, uint32_t> registroHash)
{
	ElementoHash elemento(registroHash.first, registroHash.second);

	this->eliminarElemento(elemento);
}

std::vector<uint32_t> Hash::buscarPalabraEnHash(std::string palabraClave) {

	unsigned int numeroBloque = this->obtenerNumeroDeBloque(palabraClave);
	uint32_t offsetDatoTabla = this->calcularOffsetBloqueEnTabla(numeroBloque);

	DatoTablaHash* datoTabla = this->levantarDatoTabla(offsetDatoTabla);

	DatoCubetaHash* datoCubeta = this->levantarDatoCubeta(datoTabla->getOffsetCubeta());

	std::vector<uint32_t> resultadosBusqueda = this->acumularResultados(datoCubeta, palabraClave);

	delete datoTabla;
	delete datoCubeta;

	return resultadosBusqueda;
}

std::vector<uint32_t> Hash::buscarFraseEnHash(std::string fraseConPalabrasClave) {
	std::string fraseConPalabrasClaveNormalizada =
			ServiceClass::normalizarString(fraseConPalabrasClave);

	std::vector<std::string> listaPalabrasClave =
			ServiceClass::obtenerListaPalabras(
					fraseConPalabrasClaveNormalizada, SEPARADORES_DE_PALABRAS);

	std::list<uint32_t> listaResultadosAcumulados;

	std::vector<uint32_t> resultadosParciales;
	std::vector<uint32_t> resultadosFinales;

	if (listaPalabrasClave.size() > 0) {
		//resultados de la primera palabra
		resultadosParciales = buscarPalabraEnHash(listaPalabrasClave.at(0));

		//Lo pasamos a una lista para que sea mï¿½s eficiente la eliminaciï¿½n de claves no comunes.
		for (unsigned int nroResultado = 0; nroResultado
				< listaResultadosAcumulados.size(); nroResultado++) {
			listaResultadosAcumulados.insert(listaResultadosAcumulados.begin(),
					resultadosParciales.at(nroResultado));
		}

		//Mientras queden palabras por procesar y no se hayan descartado todos los resultados...
		unsigned int nroPalabraClave = 1; //(la palabra nro cero se procesï¿½ arriba)
		while (nroPalabraClave < listaPalabrasClave.size()
				&& listaResultadosAcumulados.size() > 0) {
			//Buscamos resultados de las palabras clave
			resultadosParciales = buscarPalabraEnHash(listaPalabrasClave.at(
					nroPalabraClave));

			//Se eliminan los resultados que no sean comunes a TODAS las palabras clave.
			std::list<uint32_t>::iterator it_resultados =
					listaResultadosAcumulados.begin();

			while (it_resultados != listaResultadosAcumulados.end()) {
				uint32_t resultadoActual = *it_resultados;

				bool resultadoAcumuladoExisteTambienEnBusquedaActual = false;

				unsigned int x = 0;
				while (x < resultadosParciales.size()
						&& !resultadoAcumuladoExisteTambienEnBusquedaActual) {
					if (resultadoActual == resultadosParciales.at(x))
						resultadoAcumuladoExisteTambienEnBusquedaActual = true;
				}

				//Si el resultado no estaba en la bï¿½squeda actual, se elimina de resultados acumulados.
				if (!resultadoAcumuladoExisteTambienEnBusquedaActual) {
					std::list<uint32_t>::iterator it_elimiacion = it_resultados;
					it_resultados++;
					listaResultadosAcumulados.erase(it_elimiacion);
				} else {
					it_resultados++;
				}
			}
		}
		for (std::list<uint32_t>::iterator it_resultados =
				listaResultadosAcumulados.begin(); it_resultados
				!= listaResultadosAcumulados.end(); it_resultados++) {
			resultadosFinales.push_back(*it_resultados);
		}

	}

	return resultadosFinales;
}

void Hash::escribirArchivoIndice(fstream &archivoSalidaIndice) {
	stringstream ssIndice;
	ssIndice << "INDICE HASH\n\n";
	ssIndice << "Nombre de archivo de tabla de hash: "
			<< this->nombreArchivoTabla << "\n";
	ssIndice << "Nombre de archivo de cubetas de hash (datos): "
			<< this->nombreArchivoCubetas << "\n";
	ssIndice << "Cantidad de entradas de la tabla (bloques direccionables): "
			<< this->cantidadDeBloques << "\n";
	ssIndice
			<< "Cantidad de cubetas (unidades de almacenamiento de datos) efectivas: "
			<< this->cantidadDeCubetas << "\n";

	archivoSalidaIndice << ssIndice.str();
}

void Hash::escribirArchivosTablaDatosYEspaciosLibres(
		fstream &archivoSalidaTabla, fstream &archivoSalidaDatos,
		fstream &archivoSalidaEspaciosLibres) {

	archivoSalidaTabla << "TABLA DE HASH\n\n";
	archivoSalidaDatos << "CUBETAS DE HASH\n\n";
	archivoSalidaEspaciosLibres << "REGISTRO DE ESPACIOS LIBRES\n";

	archivoSalidaEspaciosLibres
			<< "Se muestran las cubetas que no tienen Elementos (claves) guardados, aunque estï¿½n siempre incializadas y prestas a recibirlos\n\n";

	//Se recorren en orden las entradas de la tabla, y las cubetas a medida que son direccionadas.
	for (unsigned int numeroDeBloque = 0; numeroDeBloque
			< this->cantidadDeBloques; numeroDeBloque++) {
		DatoTablaHash* datoTabla = this->levantarDatoTabla(
				this->calcularOffsetBloqueEnTabla(numeroDeBloque));
		stringstream ssTabla;

		//Escribimos archivo de tabla
		ssTabla << "Nï¿½mero de Bloque: " << numeroDeBloque << "\n";
		ssTabla << "*** Cantidad de Elementos del bloque: "
				<< datoTabla->getCantidadDeElementos() << "\n";
		ssTabla << "*** Offset a la Cubeta de Datos Inicial del bloque: "
				<< datoTabla->getOffsetCubeta() << "\n";
		ssTabla << "\n";

		//Escribimos cubetas de la entrada de la tabla en archivo de salida de cubetas.
		bool quedanCubetas = true;
		uint32_t offsetCubeta = datoTabla->getOffsetCubeta();
		unsigned int numeroDeCubetaSucesiva = 1;
		while (quedanCubetas) {
			DatoCubetaHash* datoCubeta = this->levantarDatoCubeta(offsetCubeta);
			stringstream ssCubetas;

			ssCubetas << "Cubeta del Bloque Nï¿½mero " << numeroDeBloque << "\n";
			ssCubetas << "Nï¿½mero de cubeta del mismo bloque: "
					<< numeroDeCubetaSucesiva << "\n";
			ssCubetas
					<< "Cantidad de Elementos (Claves) almacenados en la cubeta: "
					<< datoCubeta->getCantidadDeElementos() << "\n";
			ssCubetas << "Bytes libres en la cubeta: "
					<< datoCubeta->getBytesLibres() << "\n";
			ssCubetas << "Offset en disco de la cubeta Actual: "
					<< offsetCubeta << "		";
			ssCubetas << "Offset de cubeta continuaciï¿½n: "
					<< datoCubeta->getOffsetCubetaContinuacion() << "\n";

			//Registro de cubetas libres:
			if (datoCubeta->getCantidadDeElementos() == 0)// && numeroDeCubetaSucesiva > 1)
			{
				stringstream ssLibre;
				ssLibre << "Bloque que contiene la cubeta libre: "
						<< numeroDeBloque << "\n";
				ssLibre << "Nï¿½mero de cubeta sucesiva del bloque: "
						<< numeroDeCubetaSucesiva << "\n";
				ssLibre << "Offset de la cubeta en el archivo: "
						<< offsetCubeta << "\n";

				archivoSalidaEspaciosLibres << ssLibre.str();
			}

			delete datoCubeta;

			archivoSalidaDatos << ssCubetas.str();
			archivoSalidaDatos << "\n";
			quedanCubetas = (offsetCubeta != 0);
			offsetCubeta = datoCubeta->getOffsetCubetaContinuacion();
			numeroDeCubetaSucesiva++;
		}
		archivoSalidaDatos << "\n\n";

		delete datoTabla;

		//Reiniciamos flujo de datos
		archivoSalidaTabla << ssTabla.str();
		ssTabla.str("");
		ssTabla.clear();
	}
}

void Hash::escribirEstructuraEnArchivos(std::string baseNombreArchivo) {

	//Se generan los archivos segï¿½n especificaciones del enunciado del TP.
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
	bool arcIndiceOk = ManejadorArchivo::Crear(
			nombreArchivoSalidaIndice.c_str(), archivoSalidaIndice, false);

	fstream archivoSalidaTabla;
	bool arcTablaOk = ManejadorArchivo::Crear(nombreArchivoSalidaTabla.c_str(),
			archivoSalidaTabla, false);

	fstream archivoSalidaLibres;
	bool arcLibresOk = ManejadorArchivo::Crear(
			nombreArchivoSalidaLibres.c_str(), archivoSalidaLibres, false);

	fstream archivoSalidaDatos;
	bool arcDatosOk = ManejadorArchivo::Crear(nombreArchivoSalidaDatos.c_str(),
			archivoSalidaDatos, false);

	if (arcIndiceOk && arcTablaOk && arcLibresOk && arcDatosOk) {
		//ESCRITURA DE ARCHIVOS
		//*********************

		//ARCHIVO DE INDICE
		this->escribirArchivoIndice(archivoSalidaIndice);

		//ARCHIVOs DE TABLA Y DE DATOS
		this->escribirArchivosTablaDatosYEspaciosLibres(archivoSalidaTabla,
				archivoSalidaDatos, archivoSalidaLibres);

		//SALIDA POR PANTALLA Y CIERRE DE ARCHIVOS
		//****************************************
		std::cout << "Generados los siguientes archivos: " << std::endl;
		std::cout << "********* *** *******************" << std::endl
				<< std::endl;
		std::cout << nombreArchivoSalidaIndice << std::endl;
		std::cout << nombreArchivoSalidaTabla << std::endl;
		std::cout << nombreArchivoSalidaLibres << std::endl;
		std::cout << nombreArchivoSalidaDatos << std::endl;

		ManejadorArchivo::Cerrar(archivoSalidaIndice);
		ManejadorArchivo::Cerrar(archivoSalidaTabla);
		ManejadorArchivo::Cerrar(archivoSalidaLibres);
		ManejadorArchivo::Cerrar(archivoSalidaDatos);
	} else {
		if (arcIndiceOk)
			ManejadorArchivo::Cerrar(archivoSalidaIndice);
		if (arcTablaOk)
			ManejadorArchivo::Cerrar(archivoSalidaTabla);
		if (arcLibresOk)
			ManejadorArchivo::Cerrar(archivoSalidaLibres);
		if (arcDatosOk)
			ManejadorArchivo::Cerrar(archivoSalidaDatos);
		std::cout << "ERROR EN LA GENERACIï¿½N DE ARCHIVOS DE SALIDA"
				<< std::endl;
	}
}

Hash::~Hash() {
	Cerrar(archivoTabla);
	Cerrar(archivoCubetas);
}

