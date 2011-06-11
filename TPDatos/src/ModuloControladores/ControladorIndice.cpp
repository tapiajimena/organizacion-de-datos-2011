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
	if (tipoIndice == INDICE_AUTOR)
		indexarPorAutorOEditorial(parLibroOffset,true);
	else if(tipoIndice == INDICE_EDITORIAL)
		indexarPorAutorOEditorial(parLibroOffset,false);
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
				pathCarpeta + ARCHIVO_INDICE_TITULO + "_Cubetas" + EXTENSION_ARCHIVO_INDICE);
		parClaveIdLibro.first = libroRemover->getTitulo();
		parClaveIdLibro.second= idLibro;
		indiceTituloHash->eliminarElemento(parClaveIdLibro);
		delete(indiceTituloHash);
	}
	else if (tipo == INDICE_PALABRAS)
	{
		//se remueven los indices de palabras el hash
		Hash* indicePalabrasHash= new Hash(
							pathCarpeta + ARCHIVO_INDICE_PALABRAS + EXTENSION_ARCHIVO_INDICE,
							pathCarpeta + ARCHIVO_INDICE_PALABRAS + "_Cubetas" + EXTENSION_ARCHIVO_INDICE);

		libroRemover->getPalabrasClave();
		if ((libroRemover->getPalabrasClave() != NULL) && (!libroRemover->getPalabrasClave()->empty()))
		{
			EstructuraPalabrasClave::iterator it_mapaPalabras;
			EstructuraPalabrasClave* palabras = libroRemover->getPalabrasClave();
			for(it_mapaPalabras = palabras->begin(); it_mapaPalabras != palabras->end(); it_mapaPalabras++)
			{
				parClaveIdLibro.first = (*it_mapaPalabras).first;
				parClaveIdLibro.second= idLibro;

				indicePalabrasHash->eliminarElemento(parClaveIdLibro);
			}
		}
		else
			Logger::log("ControladorIndice","eliminarIndexadoPorTipo","La lista de palabras a eliminar es nula");

		delete(indicePalabrasHash);
	}
	else
		Logger::log("ControladorIndice","eliminarIndexadoPorTipo", "El tipo de indice no existe.");

	delete (elementoNodo);

}

void ControladorIndice::generarReporte(char tipoIndice, string nombreArchivo)
{
	Configuracion* conf = Configuracion::GetInstancia();
	if (tipoIndice == INDICE_AUTOR)
		this->indiceArbol->dump(conf->getPathCarpetaReportes() + nombreArchivo
								+ "_Autor" + EXTENSION_ARCHIVO_REPORTE);
	else if (tipoIndice == INDICE_EDITORIAL)
		this->indiceArbol->dump(conf->getPathCarpetaReportes() + nombreArchivo
								+ "_Editorial" + EXTENSION_ARCHIVO_REPORTE);
	else if (tipoIndice == INDICE_TITULO)
		this->indiceHash->escribirEstructuraEnArchivos(conf->getPathCarpetaReportes()
						+ nombreArchivo	+ "_Titulo" + EXTENSION_ARCHIVO_REPORTE);
	else if (tipoIndice == INDICE_PALABRAS)
		this->indiceHash->escribirEstructuraEnArchivos(conf->getPathCarpetaReportes()
						+ nombreArchivo	+ "_Palabras" + EXTENSION_ARCHIVO_REPORTE);
}


void ControladorIndice::consultarPorAutorOEditorial(string consulta)
{
	CaseFoldedString caseFold;

	DatoElementoNodo* encontrado = NULL;
	string consultaCaseFold = caseFold.caseFoldWord(consulta);

	Logger::log("ControladorIndice","consultarPorAutorOEditorial", "Se busca la consulta");
	encontrado = indiceArbol->find(new DatoElementoNodo(consultaCaseFold,0));
	if ((encontrado) && (encontrado->getClave()!="")
			&& (consultaCaseFold.compare(encontrado->getClave()) == 0))
	{
		uint32_t idLibro = NULL;
		list<uint32_t>::iterator it;
		list<uint32_t> aux = encontrado->getLibros();
		for (it = aux.begin(); it != aux.end(); ++it) {
			idLibro = *it;
			cout<< "\t *Libro: "<<idLibro<<endl;
		}
	}
	else
	{
		Logger::log("ControladorIndice","consultarPorAutorOEditorial", "No se obtuvieron resultados");
		cout<<"No se obtuvieron resultados"<<endl;
	}
}


void ControladorIndice::consultarPorTitulo(string consulta)
{
	Logger::log("ControladorIndice","consultarPorTitulo", "Se realiza una consulta por titulo");
	vector<uint32_t> aux = this->indiceHash->buscarPalabraEnHash(consulta);

	if (!aux.empty())
	{
		uint32_t idLibro = NULL;
		vector<uint32_t>::iterator it;
		for (it = aux.begin(); it != aux.end(); ++it)
		{
			idLibro = *it;
			cout<< "\t *Libro: "<<idLibro<<endl;
		}
	}
	else
	{
		Logger::log("ControladorIndice","consultarPorTitulo", "No se obtuvieron resultados");
		cout<<"No se obtuvieron resultados"<<endl;
	}
}


void ControladorIndice::consultarPorPalabras(string consulta)
{
	/*
	string 	aux;
	pair<string,uint32_t> 				registroHash;
	EstructuraPalabrasClave::iterator 	it;

	for(it =parLibroOffset.first->getPalabrasClave()->begin();it!=parLibroOffset.first->getPalabrasClave()->end();++it)
	{
		aux = ServiceClass::normalizarString((*it).first);

		registroHash.first = aux;
		registroHash.second= parLibroOffset.second;

		//cout<<"Se envia Clave: "<<aux<<endl;
		//cout<<"Se envia id: "<<parLibroOffset.second<<endl;

		this->indiceHash->insertarClave(registroHash);

	}*/
}



void ControladorIndice::indexarPorAutorOEditorial(pair<Libro*,uint32_t> parLibroOffset, bool autor)
{
	//FIXME revisar que no siempre se este insertando el autor
	CaseFoldedString caseFold;

	if (autor)
		indiceArbol->insert(new DatoElementoNodo(caseFold.caseFoldWord(parLibroOffset.first->getAutor()),
						parLibroOffset.second));
	else
		indiceArbol->insert(new DatoElementoNodo(caseFold.caseFoldWord(parLibroOffset.first->getEditorial()),
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

		registroHash.first = aux;
		registroHash.second= parLibroOffset.second;

		//cout<<"Se envia Clave: "<<aux<<endl;
		//cout<<"Se envia id: "<<parLibroOffset.second<<endl;

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




