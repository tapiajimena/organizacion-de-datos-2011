/*
 * main.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include <iostream>
#include <string>
#include "ModuloDeIndices/Hash/Hash.h"
#include "ModuloDeInterfaz/ManejadorInstrucciones.h"
#include  "ModuloDeArchivos/ArchivoTerminos.h"
#include  "ModuloDeArchivos/ArchivoTriadas.h"

#include "ModuloControladores/ControladorIndice.h"
#include  "ModuloDeProcesadores/ProcesadorDeRelevancia.h"



int main(int cantidad, char* argumentos[])
{
	ManejadorInstrucciones* instrucciones = new ManejadorInstrucciones(argumentos, cantidad);
	instrucciones->ejecutarInstruccionElegida();
	delete(instrucciones);

/*
	ParserDeOcurrenciasDeTerminos* parser = new ParserDeOcurrenciasDeTerminos("words.txt");
	DatoLibro* d = new DatoLibro("la casa es de pirulo");

	Libro* libro = parser->parsear(d);
	vector<string> aux = libro->getOcurrenciasDeTerminos();
	vector<string>::iterator it;
	for(it = aux.begin();it != aux.end(); it++)
		cout<<"EL PRIMERO: "<<(*it)<<endl;

	delete d;
	delete parser;
*/



	 /*
	 Hash* hash = new Hash("Indices/IndicePalabra.dat", "Indices/IndicePalabra_Cubetas.dat");

	 std::vector<uint32_t> idLibros = hash->buscarPalabraEnHash("zum");

	 for(int i =0; i < idLibros.size(); i++)
	 std::cout<<"EL ID ES: "<<idLibros[i]<<endl;

	 return 0;
	 */


	//prueba dumpeo de arbol
	string path =  "Indices/IndiceOcurrenciaTerminos.dat";
	BPlusTree* tree = new BPlusTree(path, BLOCKSIZE);
	tree->dump("ocurrencias.txt");
	delete (tree);



	 /*
	//prueba eliminado de libros
	BPlusTree* tree = new BPlusTree("prueba.dat", BLOCKSIZE);
	DatoElementoNodo* elemento0 = new DatoElementoNodo("PIRULO PALABRA",1 );
	DatoElementoNodo* elemento1 = new DatoElementoNodo("PIRULO PALABRA",2 );
	DatoElementoNodo* elemento2 = new DatoElementoNodo("PIRULO PALABRA",3 );
	DatoElementoNodo* elemento3 = new DatoElementoNodo("PIRULO PALABRA",4 );

	tree->insert(elemento0);
	tree->insert(elemento1);
	tree->insert(elemento2);
	tree->insert(elemento3);

	DatoElementoNodo* elementoElminado = new DatoElementoNodo("PIRULO PALABRA",1 );
	elementoElminado->agregarLibro(2);

	tree->remove(elementoElminado);

	tree->dump("prueba.xml");
	delete (tree);
	*/
/*
	Configuracion* conf = Configuracion::GetInstancia();
	ControladorIndice* controlIndice = new ControladorIndice(conf->getPathCarpetaTrabajo());

	list<DatoTriada> rdo = controlIndice->recuperarTriadas("escarlata");
	list<DatoTriada>::iterator it;
	for(it = rdo.begin(); it != rdo.end(); it++)
	{
		cout<<"LAS TRIADAS: "<<((DatoTriada)*it).getIdTermino()<<endl;
	}

	delete(controlIndice);
*/

}

