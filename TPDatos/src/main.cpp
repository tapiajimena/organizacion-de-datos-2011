/*
 date: 14/03/11


*/
#include <iostream>
#include "ModuloDeInterfaz/ParserDeLibros.h"
#include "ModuloDeInterfaz/Libro.h"
#include "ModuloDeTipos/DatoLibro.h"
#include "ModuloDeArchivos/ArchivoLibro.h"
#include "ModuloDeArchivos/ArchivoControlLibro.h"
#include "ModuloDeArchivos/ManejadorArchivo.h"


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

using namespace std;
int main()
{

	DatoLibro* dato = new DatoLibro();
	ArchivoLibro* arcReg = new ArchivoLibro("prueba.dat");
	ArchivoControlLibro* arcControl = new ArchivoControlLibro("pruebaControl.crt");


	fstream fs;
	Libro* libro = new Libro();
	ParserDeLibros* parserLibros = new ParserDeLibros("../Common/stopwordstest.txt");
	ManejadorArchivo::Crear("pruebaParser.par", fs, false);
	libro = parserLibros->parsearLibro("doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");

	//Se imprimen por archivo primeras 100 Palabras Clave
	EstructuraPalabrasClave* palabrasClave = libro->getPalabrasClave();
	int x = 0;
	for (EstructuraPalabrasClave::iterator it_palabrasClave = palabrasClave->begin();
			it_palabrasClave != palabrasClave->end() && x < 100;
			it_palabrasClave++)
		fs<<it_palabrasClave->first<<std::endl;


	cargarLibros(arcReg, arcControl);
	/*
	//se recorre toda la biblioteca
	arcReg->irAlInicio();
	cout<< arcReg->leerRegistroVariable()<<";"<<endl;
 	 */


	delete(dato);
	delete(libro);
    delete(arcReg);
    delete(arcControl);
    delete(parserLibros);

    return 0;
}
