/*
 * main.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#include <iostream>

#include "./Common/Constantes.h"
#include "./Common/Utilitarios/Logger.h"

#include "ModuloEstructuras/Diccionario.h"

#include "ModuloDeTipos/DatoNodo.h"
#include "ModuloDeTipos/DatoLibro.h"
#include "ModuloDeTipos/DatoTablaHash.h"
#include "ModuloDeTipos/DatoCubetaHash.h"

#include "ModuloDeArchivos/ArchivoLibro.h"
#include "ModuloDeArchivos/ManejadorArchivo.h"
#include "ModuloDeArchivos/ArchivoControlLibro.h"
#include "ModuloControladores/ControladorBiblioteca.h"

#include "ModuloDeIndices/Indexador.h"
#include "ModuloDeIndices/ArbolBMas/src/ArbolBMas.h"
#include "ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.h"
#include "ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.h"
//#include "ModuloDeIndices/ArbolBMas/src/TestArbol.h"

#include "ModuloEstructuras/Libro.h"
#include "ModuloParser/ParserDeTitulo.h"
#include "ModuloParser/ParserDeAutor.h"
#include "ModuloParser/ParserDeEditorial.h"
#include "ModuloParser/ParserDePalabras.h"
#include "ModuloDeInterfaz/ManejadorInstrucciones.h"

#include "ModuloDeIndices/Hash/Hash.h"
#include "ModuloDeIndices/Hash/ElementoHash.h"

using namespace std;


void testAgregarLibros()
{
	//FIXME cuando se intentan agregar archivos que no existen hay sigsegv
	ControladorBiblioteca* controlBiblioteca = new ControladorBiblioteca(((string)"Indices/")+ARCHIVO_BIBLIOTECA,
																	((string)"Indices/")+ARCHIVO_CONTROL_BIBLIOTECA);
	controlBiblioteca->ingresarLibro("librotest.txt");
	controlBiblioteca->ingresarLibro("librotest.txt");
	controlBiblioteca->ingresarLibro("librotest.txt");

	delete (controlBiblioteca);
}

void testListarLibrosDeBiblioteca()
{
	ControladorBiblioteca* controlBiblioteca = new ControladorBiblioteca(((string)"Indices/")+ARCHIVO_BIBLIOTECA,
																	((string)"Indices/")+ARCHIVO_CONTROL_BIBLIOTECA);

	list<uint32_t>::iterator it;
	list<uint32_t> biblioteca = controlBiblioteca->recuperarLibrosDeBiblioteca();

	for(it=biblioteca.begin(); it != biblioteca.end(); ++it)
		cout<<"ID LIBRO: "<<*it<<endl;


	delete (controlBiblioteca);

}

void testIndexar(char tipoIndice)
{
	Indexador* indexador = new Indexador();

	indexador->indexar(tipoIndice);
	delete (indexador);
}

void testEliminarIndexado(uint32_t idLibro)
{
	Indexador* indexador = new Indexador();

	//tambien lo elimina de la biblioteca
	indexador->eliminarIndexado(idLibro);
	delete (indexador);
}

int main(int argc, char *argv[])
{
	//testAgregarLibros();

	ManejadorInstrucciones* m = new ManejadorInstrucciones(argv,argc);

	m->ejecutarInstruccionElegida();

    return 0;
}
















