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
#include "ModuloDeInterfaz/Libro.h"
#include "ModuloDeTipos/DatoLibro.h"
#include "ModuloDeTipos/DatoNodo.h"
#include "ModuloDeArchivos/ArchivoLibro.h"
#include "ModuloDeArchivos/ArchivoControlLibro.h"
#include "ModuloDeArchivos/ControladorBiblioteca.h"
#include "ModuloDeArchivos/ManejadorArchivo.h"
#include "ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.h"
#include "ModuloEstructuras/Diccionario.h"
#include "ModuloDeInterfaz/ManejadorInstrucciones.h"

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
//    fstream fs;
//    Libro *libro = new Libro();
//    ParserDeLibros *parserLibros = new ParserDeLibros("../Common/stopwordstest.txt");
//    ManejadorArchivo::Crear("pruebaParser.par", fs, false);
//    libro = parserLibros->parsearLibro("doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");
//
//    //Se imprimen por archivo primeras 100 Palabras Clave
//    EstructuraPalabrasClave *palabrasClave = libro->getPalabrasClave();
//    EstructuraPalabrasClave::iterator it_palabrasClave;
//    int x = 0;
//    //se escribe en un archivo
//    for(it_palabrasClave = palabrasClave->begin();it_palabrasClave != palabrasClave->end() && x < 100;it_palabrasClave++)
//        fs << it_palabrasClave->first << std::endl;
//
//    delete(libro);
//    delete(parserLibros);
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
	/*
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


    //Prueba de NodoInterno persistiendolo mediante DatoNodo
    //NodoInternoArbol* nodito = new NodoInternoArbol();
    list<int> hijos;
    hijos.push_front(2);
    hijos.push_front(3);
    hijos.push_front(5);

    list<string> claves;
    claves.push_front("casa");
    claves.push_front("travesti");
    claves.push_front("servetto");

   // nodito->setClaves(claves);
   // nodito->setHijos(hijos);

    //DatoNodo* datoNodo = new DatoNodo((NodoInternoArbol*)nodito);
     * */

}


void testControladorBiblioteca()
{
	//TODO falta testear el eliminar y el tema de los indices
	ControladorBiblioteca* control = new ControladorBiblioteca("prueba.dat","pruebaControl.crt");

	control->ingresarLibro("doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");
	DatoLibro libro = control->recuperarLibro(0);

	Logger::log("ControlBiblioteca","recuperarLibro",libro.getDato());
}

void testDiccionario(){
	Diccionario* d = new Diccionario("stopWords.txt");
	d->cargarDiccionario();
	d->mostrar();

	if (d->existePalabra("jime")) cout << "existe" << endl;
	if (d->existePalabra("tapia")) cout << "existe" << endl;
	if (!d->existePalabra("jajaja")) cout << "no existe" << endl;

	delete(d);
}

void testInstrucciones(){

	ManejadorInstrucciones* mi = new ManejadorInstrucciones();
	mi->armarInstruccion();
}

int main()
{
	//testDato();
	//testParser();
    //testBiblioteca();
	testControladorBiblioteca();
	testPersistenciaNodoInterno();

    return 0;
}
