/*
 date: 14/03/11


*/
#include <iostream>
#include "ModuloDeInterfaz/ParserDeLibros.h"
#include "ModuloDeInterfaz/Libro.h"
#include "ModuloDeTipos/DatoLibro.h"
#include "ModuloDeTipos/DatoNodo.h"
#include "ModuloDeArchivos/ArchivoLibro.h"
#include "ModuloDeArchivos/ArchivoControlLibro.h"
#include "ModuloDeArchivos/ManejadorArchivo.h"
#include "ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.h"


using namespace std;

//testeo de clase Dato y DatoLibro
void testDato()
{
	DatoLibro* dato = new DatoLibro("PIRULO EL DEL BOSQUE!!!");

	cout<<dato->toCharPointer()<<endl;
	dato->vaciar();
	if (dato->estaVacio())
		cout<<"NO ESTA MAS!!";
	cout<<dato->toCharPointer();

	delete(dato);
}

void cargarLibros(ArchivoLibro* arcReg, ArchivoControlLibro* arcControl)
{
	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Arthur Conan Doyle - Estudio en Escarlata.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Stephen King - Cell.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Stephen King - Historias fantásticas.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Stephen King - La Expedición.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Stephen King - La torre Oscura I.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Stephen King - The Dead Zone.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Umberto Eco - El Nombre de la Rosa.txt");


	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Arthur Conan Doyle - Estudio en Escarlata.txt");
}


void testParser()
{
    fstream fs;
    Libro *libro = new Libro();
    ParserDeLibros *parserLibros = new ParserDeLibros("../Common/stopwordstest.txt");
    ManejadorArchivo::Crear("pruebaParser.par", fs, false);
    libro = parserLibros->parsearLibro("doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");

    //Se imprimen por archivo primeras 100 Palabras Clave
    EstructuraPalabrasClave *palabrasClave = libro->getPalabrasClave();
    EstructuraPalabrasClave::iterator it_palabrasClave;
    int x = 0;
    //se escribe en un archivo
    for(it_palabrasClave = palabrasClave->begin();it_palabrasClave != palabrasClave->end() && x < 100;it_palabrasClave++)
        fs << it_palabrasClave->first << std::endl;

    delete(libro);
    delete(parserLibros);
}


void testBiblioteca()
{
    DatoLibro *dato = new DatoLibro();
    ArchivoLibro *arcReg = new ArchivoLibro("prueba.dat");
    ArchivoControlLibro *arcControl = new ArchivoControlLibro("pruebaControl.crt");

    cargarLibros(arcReg, arcControl);

    //se recorre toda la biblioteca
    arcReg->irAlInicio();
    DatoLibro libroRecuperado = arcReg->recuperarLibro(265090);
    cout << libroRecuperado.toString() << ";" << endl;

    delete (dato);
    delete (arcReg);
    delete (arcControl);
}

void testPersistenciaNodoInterno()
{
	NodoInternoArbol* nodito = new NodoInternoArbol();

	list<string>* claves = new list<string>();
	claves->push_back("hola");
	claves->push_back("mundo");
	claves->push_back("cruel");

	nodito->setClaves(claves);

	list<int>* hijos = new list<int>();
	hijos->push_back(1);
	hijos->push_back(21);
	hijos->push_back(5);
	hijos->push_back(51);

	nodito->setHijos(hijos);



	DatoNodo* dato = new DatoNodo(nodito);

	string s = dato->getDato();
	cout <<s << endl;

	delete(hijos);
	delete(claves);
	delete(nodito);
	delete(dato);

}

int main()
{
	//testDato();
	//testParser();
    //testBiblioteca();
	testPersistenciaNodoInterno();
    return 0;
}
