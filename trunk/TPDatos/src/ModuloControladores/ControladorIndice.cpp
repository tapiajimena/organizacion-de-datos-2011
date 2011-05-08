/*
 * ControladorIndice.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#include "ControladorIndice.h"


ControladorIndice::ControladorIndice()
{
	Configuracion* conf = Configuracion::GetInstancia();
	this->pathCarpeta = conf->getPathCarpetaTrabajo();
	this->indiceHash = NULL;
	this->indiceArbol = NULL;
}


ControladorIndice::ControladorIndice(string pathCarpeta)
{
	this->pathCarpeta = pathCarpeta;
	this->indiceHash = NULL;
	this->indiceArbol = NULL;

}


void ControladorIndice::nuevoIndiceAutor()
{
	this->indiceArbol = new BPlusTree(
			pathCarpeta + ARCHIVO_INDICE_AUTOR + EXTENSION_ARCHIVO_INDICE,
			SIZE_BLOQUE);
	this->indiceHash = NULL;
}


void ControladorIndice::nuevoIndiceEditorial()
{
	this->indiceArbol = new BPlusTree(
			pathCarpeta + ARCHIVO_INDICE_EDITORIAL + EXTENSION_ARCHIVO_INDICE,
			SIZE_BLOQUE);
	this->indiceHash = NULL;
}


void ControladorIndice::nuevoIndiceTitulo()
{
	this->indiceHash = new Hash(
			pathCarpeta + ARCHIVO_INDICE_TITULO + EXTENSION_ARCHIVO_INDICE,
			pathCarpeta + ARCHIVO_INDICE_TITULO + "_Cubetas" + EXTENSION_ARCHIVO_INDICE);
	this->indiceArbol = NULL;
}


void ControladorIndice::nuevoIndicePalabras()
{
	this->indiceHash = new Hash(
			pathCarpeta+ARCHIVO_INDICE_PALABRAS + EXTENSION_ARCHIVO_INDICE,
			pathCarpeta + ARCHIVO_INDICE_PALABRAS + "_Cubetas" + EXTENSION_ARCHIVO_INDICE);
	this->indiceArbol = NULL;
}


void ControladorIndice::indexar(pair<Libro*,uint32_t> parLibroOffset, char tipoIndice)
{
	//si queda tiempo crear clases
	if ((tipoIndice == INDICE_AUTOR)||(tipoIndice == INDICE_EDITORIAL))
		indexarPorAutorOEditorial(parLibroOffset);
	else if(tipoIndice == INDICE_TITULO)
		indexarPorTitulo(parLibroOffset);
	else if(tipoIndice == INDICE_PALABRAS)
		indexarPorPalabras(parLibroOffset);
	else
		Logger::log("ControladorIndice","indexar","El tipo de indice no existe, verifique que sea A,E,T,P");
}


void ControladorIndice::eliminarIndexado(Libro* libroRemover, uint32_t idLibro, list<char>* tiposIndices)
{
	list<char>::iterator it;

	for(it = tiposIndices->begin(); it != tiposIndices->end(); it++)
	{
		cout<<endl<<"LA PORQUERIA ES INDICE DE: "<< *it<<endl;
		//Logger::log("ControladorIndice","eliminarIndexado","Elminando indice tipo " + *it );
		eliminarIndexadoPorTipo(*it,libroRemover, idLibro);
	}
}

void ControladorIndice::eliminarIndexadoPorTipo(char tipo, Libro* libroRemover,uint32_t idLibro)
{
	CaseFoldedString caseFold;
	DatoElementoNodo* elementoNodo 	= new DatoElementoNodo();
	pair<std::string, uint32_t>  parClaveIdLibro;

	if(tipo == INDICE_AUTOR)
	{
		elementoNodo->agregarLibro(idLibro);
		//se remueven los indices de autor del arbol
		elementoNodo->setClave(caseFold.caseFoldWord(libroRemover->getAutor()));

		BPlusTree* indiceAutorArbol = new BPlusTree(
				pathCarpeta + ARCHIVO_INDICE_AUTOR + EXTENSION_ARCHIVO_INDICE,
				SIZE_BLOQUE);

		//cout<<endl<<"Se remueve del arbol: "<<elementoNodo->getClave();
		//cout<<endl<<"Se remueve del arbol: "<<elementoNodo->getLibros().front()<<endl;

		indiceAutorArbol->remove(elementoNodo);
		delete(indiceAutorArbol);
	}
	else if(tipo == INDICE_EDITORIAL)
	{
		//se remueven los indices de editorial del arbol
		elementoNodo->setClave(libroRemover->getEditorial());
		BPlusTree* indiceEditorialArbol = new BPlusTree(
				pathCarpeta + ARCHIVO_INDICE_EDITORIAL + EXTENSION_ARCHIVO_INDICE,
				SIZE_BLOQUE);
		indiceEditorialArbol->remove(elementoNodo);
		delete(indiceEditorialArbol);
	}
	else if (tipo == INDICE_TITULO)
	{
		//se remueven los indices de titulo del hash
		Hash* indiceTituloHash= new Hash(
				pathCarpeta + ARCHIVO_INDICE_TITULO + EXTENSION_ARCHIVO_INDICE,
				pathCarpeta + ARCHIVO_CUBETAS + EXTENSION_ARCHIVO_INDICE);
		parClaveIdLibro.first = libroRemover->getTitulo();
		parClaveIdLibro.second= idLibro;
		indiceTituloHash->eliminarElemento(parClaveIdLibro);
		delete(indiceTituloHash);
	}
	else if (tipo == INDICE_PALABRAS)
	{
		//se remueven los indices de palabras el hash
		Hash* indicePalabrasHash= new Hash(pathCarpeta + ARCHIVO_INDICE_PALABRAS + EXTENSION_ARCHIVO_INDICE,
									 pathCarpeta + ARCHIVO_TABLA + EXTENSION_ARCHIVO_INDICE);


		libroRemover->getPalabrasClave();
		if ((libroRemover->getPalabrasClave() != NULL) && (!libroRemover->getPalabrasClave()->empty()))
		{
			cout<<"Hola Mundo!!"<<endl;
			EstructuraPalabrasClave::iterator it_mapaPalabras;
			for(it_mapaPalabras = libroRemover->getPalabrasClave()->begin(); it_mapaPalabras != libroRemover->getPalabrasClave()->end(); it_mapaPalabras++)
			{
				//cout<<endl<<"SE VA A ELIMINAR "<< (*it_mapaPalabras).first<<endl;
				//cout<<endl<<"SE VA A ELIMINAR id "<< idLibro<<endl;
				parClaveIdLibro.first = (*it_mapaPalabras).first;
				parClaveIdLibro.second= idLibro;
				indicePalabrasHash->eliminarElemento(parClaveIdLibro);
			}
			delete(indicePalabrasHash);
		}
		else
			cout<<endl<<"EST NULL"<<endl;
	}
	else
		Logger::log("ControladorIndice","eliminarIndexadoPorTipo", "El tipo de indice no existe.");

	delete (elementoNodo);

}

void ControladorIndice::generarReporte(char tipoIndice, string nombreArchivo)
{
	Configuracion* conf = Configuracion::GetInstancia();
	if ((tipoIndice == 'A')||(tipoIndice == 'E'))
		this->indiceArbol->dump(conf->getPathCarpetaReportes() + nombreArchivo
								+ tipoIndice + EXTENSION_ARCHIVO_REPORTE);
	else
		this->indiceHash->escribirEstructuraEnArchivos(conf->getPathCarpetaReportes()
								+ nombreArchivo	+ tipoIndice + EXTENSION_ARCHIVO_REPORTE);
}

void ControladorIndice::indexarPorAutorOEditorial(pair<Libro*,uint32_t> parLibroOffset)
{
	CaseFoldedString caseFold;

	cout<<endl<<"EL ELEMENTOOOOoo: "<<caseFold.caseFoldWord(parLibroOffset.first->getAutor())<<endl ;
	indiceArbol->insert(new DatoElementoNodo(caseFold.caseFoldWord(parLibroOffset.first->getAutor()),
						parLibroOffset.second));
}


void ControladorIndice::indexarPorTitulo(pair<Libro*,uint32_t> parLibroOffset)
{
	pair<string,uint32_t> registroHash(parLibroOffset.first->getTitulo(), parLibroOffset.second);
	this->indiceHash->insertarClave(registroHash);
}


void ControladorIndice::indexarPorPalabras(pair<Libro*,uint32_t> parLibroOffset)
{
	string 	aux;
	pair<string,uint32_t> 				registroHash;
	EstructuraPalabrasClave::iterator 	it;

	for(it =parLibroOffset.first->getPalabrasClave()->begin();it!=parLibroOffset.first->getPalabrasClave()->end();++it)
	{
		aux = ServiceClass::normalizarString((*it).first);
		//cout<<endl<<"SE ENVIA: "<<aux<<endl;
		//cout<<endl<<"SE ENVIA: "<<parLibroOffset.second<<endl;
		registroHash.first = aux;
		registroHash.second= parLibroOffset.second;
		this->indiceHash->insertarClave(registroHash);
	}
}


ControladorIndice::~ControladorIndice()
{
	if (indiceHash != NULL)
	{
		Logger::log("ControladorIndice","~ControladorIndice", "Se elimina el Hash");
		delete (indiceHash);
	}

	if (indiceArbol != NULL)
	{
		Logger::log("ControladorIndice","~ControladorIndice", "Se elimina el Arbol");
		delete (indiceArbol);
	}
}




