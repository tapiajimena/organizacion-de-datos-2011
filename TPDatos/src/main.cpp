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
#include "ModuloControladores/ControladorBiblioteca.h"
#include "ModuloDeArchivos/ManejadorArchivo.h"
#include "ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.h"
#include "ModuloDeInterfaz/ParserDeTitulo.h"
#include "ModuloDeInterfaz/ParserDeAutor.h"
#include "ModuloDeInterfaz/ParserDeEditorial.h"
#include "ModuloDeInterfaz/ParserDePalabras.h"
#include "ModuloEstructuras/Diccionario.h"
#include "ModuloDeInterfaz/ManejadorInstrucciones.h"
#include "../Pruebas/TestArchivoControlLibro.h"


using namespace std;

//testeo de clase Dato y DatoLibro
void testDato() {
	DatoLibro* dato = new DatoLibro("PIRULO EL DEL BOSQUE!!!");

	cout << dato->toCharPointer() << endl;
	dato->vaciar();
	if (dato->estaVacio())
		cout << "NO ESTA MAS!!";
	cout << dato->toCharPointer();

	delete (dato);
}

void cargarLibros(ArchivoLibro* arcReg, ArchivoControlLibro* arcControl) {
	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro(
			"doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro(
			"doc/libros/Arthur Conan Doyle - Estudio en Escarlata.txt");

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
	arcReg->agregarLibro(
			"doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro(
			"doc/libros/Arthur Conan Doyle - Estudio en Escarlata.txt");
}

void testParser() {
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

void testBiblioteca() {
	DatoLibro *dato = new DatoLibro();
	ArchivoLibro *arcReg = new ArchivoLibro("prueba.dat");
	ArchivoControlLibro *arcControl = new ArchivoControlLibro(
			"pruebaControl.crt");

	cargarLibros(arcReg, arcControl);

	//se recorre toda la biblioteca
	arcReg->irAlInicio();
	DatoLibro libroRecuperado = arcReg->recuperarLibro(265090);
	cout << libroRecuperado.toString() << ";" << endl;

	delete (dato);
	delete (arcReg);
	delete (arcControl);
}

void testPersistenciaNodoInterno() {
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

void testParsersDeAtributos() {
	std::cout << "INICIO TEST DE PARSERS INDIVIDUALES*********************"
			<< std::endl << std::endl;

	std::string
			seudoLibro =
					"lala \n #TITULO_LIBRO acentos������A� titulooooooo ok! \n lolololol la le \n #EDITORIAL_LIBRO ed�toriaaaal ok! \n lollolo \n #AUTOR_LIBRO JLBorges \n klsdjfaslkfj";
	DatoLibro* datoLibro = new DatoLibro(seudoLibro);

	ParserDeTitulo* parserTitulo = new ParserDeTitulo();
	ParserDeAutor* parserAutor = new ParserDeAutor();
	ParserDeEditorial* parserEditorial = new ParserDeEditorial();
	ParserDePalabras* parserPalabras =
			new ParserDePalabras("stopwordstest.txt");

	Libro* libroTitulo = parserTitulo->parsear(datoLibro);
	Libro* libroAutor = parserAutor->parsear(datoLibro);
	Libro* libroEditorial = parserEditorial->parsear(datoLibro);
	Libro* libroPalabras = parserPalabras->parsear(datoLibro);

	std::string titulo = libroTitulo->getTitulo();
	std::string autor = libroAutor->getAutor();
	std::string editorial = libroEditorial->getEditorial();
	std::cout << "Titulo Parseado: " << titulo << "#" << std::endl;
	std::cout << "Autor Parseado: " << autor << "#" << std::endl;
	std::cout << "Editorial Parseada: " << editorial << "#" << std::endl;

	std::cout << "Lista de Palabras" << std::endl;
	std::cout << "*****************" << std::endl;
	EstructuraPalabrasClave::iterator it_palabras;
	EstructuraPalabrasClave* palabras = libroPalabras->getPalabrasClave();
	for (it_palabras = palabras->begin(); it_palabras != palabras->end(); it_palabras++) {
		std::cout << (*it_palabras).first << "   " << (*it_palabras).second
				<< std::endl;
	}

	std::cout << "FIN TEST PARSERS**************" << std::endl;

	delete libroAutor;
	delete libroEditorial;
	delete libroTitulo;
	delete libroPalabras;
	delete datoLibro;
	delete parserTitulo;
	delete parserAutor;
	delete parserEditorial;
	delete parserPalabras;
}

void testDiccionario() {
	Diccionario* d = new Diccionario("stopWords.txt");
	d->cargarDiccionario();
	d->mostrar();

	if (d->existePalabra("jimena"))
		cout << "EXISTE" << endl;
	if (d->existePalabra("tapia"))
		cout << "EXISTE" << endl;
	if (!d->existePalabra("jajaja"))
		cout << "NO EXISTE" << endl;

	delete (d);
}

void testDatoControlLibro() {

	list<char> indices;
	indices.push_back('T');
	indices.push_back('A');
	indices.push_back('P');
	indices.push_back('E');

	DatoControlLibro* dcl = new DatoControlLibro(2, 4, &indices, 19);

	indices.push_back('J');

	cout << dcl->serializar() << endl;

	dcl->setIndexado(&indices);

	list<char>::iterator it;
	for (it = dcl->getIndexado()->begin(); it != dcl->getIndexado()->end(); it++)
		cout << *it << endl;

	delete (dcl);
}

void testArchivoControlLibro() {
	TestArchivoControlLibro* test = new TestArchivoControlLibro("controlLibro.txt");

	list<char> indices;
	indices.push_back('T');
	indices.push_back('A');
	indices.push_back('P');
	indices.push_back('E');

	test->ejecutarPrueba();

}

void testParserArchivoLibros() {

	fstream archivo;
	archivo.open("controlLibro.txt");

	ParserArchivoControl* p = new ParserArchivoControl(CONTROL_TOKEN);

	map<uint32_t, DatoControlLibro*>* mp = p->getLibros(&archivo);

	map<uint32_t, DatoControlLibro*>::iterator it;

	for (it = mp->begin(); it != mp->end(); it++)
		cout << (*it).first << " => " << ((*it).second)->serializar() << endl;

	archivo.close();

	delete (p);

}

void testAuxiliar() {
	map<uint32_t, DatoControlLibro*> mymap;
	map<uint32_t, DatoControlLibro*>::iterator it;

	list<char> indices;
	indices.push_back('T');
	indices.push_back('A');
	indices.push_back('P');
	indices.push_back('E');

	DatoControlLibro* dcl = new DatoControlLibro(2, 4, &indices, 19);
	DatoControlLibro* dcl2 = new DatoControlLibro(dcl);

	indices.push_back('J');

	dcl2->setIndexado(&indices);

	mymap.insert(pair<uint32_t, DatoControlLibro*> (2, dcl));
	mymap.insert(pair<uint32_t, DatoControlLibro*> (4, dcl2));

	for (it = mymap.begin(); it != mymap.end(); it++)
		cout << (*it).first << " => " << ((*it).second)->serializar() << endl;

	delete (dcl);
	delete (dcl2);
}

void testControladorBiblioteca() {
	ControladorBiblioteca* cb = new ControladorBiblioteca("librotest.txt","controlLibro.txt");

	cb->ingresarLibro(
			"doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");
//	DatoLibro libro = cb->recuperarLibro(0);
//
//	Logger::log("ControlBiblioteca", "recuperarLibro", libro.getDato());

}

int main(int argc, char* argv[]) {
	//testDato();
	//testParser();
	//testBiblioteca();
	//testControladorBiblioteca();
	//testPersistenciaNodoInterno();
	//testParserArchivoLibros();
	//testDatoControlLibro();
	//testAuxiliar();
	//testParsersDeAtributos();

	//MAIN "POSTA"

	ManejadorInstrucciones* mi;

	int valorRetorno = EXITO;

	//	if (argc > 0) {
	//		mi = new ManejadorInstrucciones(argv, argc);
	//		mi->ejecutarInstruccionElegida();
	//	} else {
	//		valorRetorno = ERROR_ARCHIVO;
	//	}

	testArchivoControlLibro();

	//testControladorBiblioteca();

	return valorRetorno;
}
