/*
 * Instruccion_ListarArchivosTomados.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ListarArchivosTomados.h"

Instruccion_ListarArchivosTomados::Instruccion_ListarArchivosTomados(char id) : Instruccion(id) {


}


void Instruccion_ListarArchivosTomados::getLibro(uint32_t idLibro)
{
	Configuracion* conf = Configuracion::GetInstancia();
	this->controladorBiblioteca = new ControladorBiblioteca(conf->getPathCarpetaTrabajo()+"/"+ARCHIVO_BIBLIOTECA,
																conf->getPathCarpetaTrabajo()+"/"+ARCHIVO_CONTROL_BIBLIOTECA);
	Libro* libro = this->controladorBiblioteca->cargarNuevoLibroParseado(idLibro);

	cout<<"LIBRO IMPRIME TITULO: "<<libro->getTitulo()<<endl;
	cout<<"LIBRO IMPRIME AUTOR: "<<libro->getAutor()<<endl;
	cout<<"LIBRO IMPRIME EDITORIAL: "<<libro->getEditorial()<<endl;
	cout<<"LIBRO IMPRIME CANTIDAD PALABRAS REGISTRADAS: "<<libro->getPalabrasClave()->size()<<endl;

	delete(libro);
}


void Instruccion_ListarArchivosTomados::ejecutar(){
	Logger::log("Instruccion_ListarArchivosTomados", "ejecutar",
			"Se muestran los libros guardados.");
	Configuracion* conf = Configuracion::GetInstancia();
	ControladorBiblioteca* controlBiblioteca = new ControladorBiblioteca(conf->getPathCarpetaTrabajo()+"/"+ARCHIVO_BIBLIOTECA,
																conf->getPathCarpetaTrabajo()+"/"+ARCHIVO_CONTROL_BIBLIOTECA);
	list<uint32_t>::iterator it;
	list<uint32_t> biblioteca = controlBiblioteca->recuperarLibrosDeBiblioteca();

	for(it=biblioteca.begin(); it != biblioteca.end(); ++it)
	{
		cout<<"ID LIBRO: "<<*it<<endl;
		getLibro(*it);
	}
	delete (controlBiblioteca);
}

Instruccion_ListarArchivosTomados::~Instruccion_ListarArchivosTomados() {
	// TODO Auto-generated destructor stub
}
