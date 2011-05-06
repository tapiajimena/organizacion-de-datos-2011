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

#include "../Common/Constantes.h"
#include "../Common/Utilitarios/Logger.h"

#include "ModuloEstructuras/Configuracion.h"
#include "ModuloEstructuras/Diccionario.h"

#include "ModuloDeTipos/DatoLibro.h"
#include "ModuloDeTipos/DatoTablaHash.h"
#include "ModuloDeTipos/DatoCubetaHash.h"

#include "ModuloDeArchivos/ArchivoLibro.h"
#include "ModuloDeArchivos/ManejadorArchivo.h"
#include "ModuloDeArchivos/ArchivoControlLibro.h"
#include "ModuloControladores/ControladorBiblioteca.h"

#include "ModuloDeIndices/Indexador.h"
#include "ModuloDeIndices/ArbolBMas/BPlusTree.h"
#include "ModuloDeIndices/ArbolBMas/InternalNode.h"
#include "ModuloDeIndices/ArbolBMas/LeafNode.h"
//#include "ModuloDeIndices/ArbolBMas/src/TestArbol.h"

#include "ModuloEstructuras/Libro.h"
#include "ModuloParser/ParserDeTitulo.h"
#include "ModuloParser/ParserDeAutor.h"
#include "ModuloParser/ParserDeEditorial.h"
#include "ModuloParser/ParserDePalabras.h"
#include "ModuloDeInterfaz/ManejadorInstrucciones.h"

#include "ModuloDeIndices/Hash/Hash.h"
#include "ModuloDeIndices/Hash/ElementoHash.h"


#include <locale>
#include <string>
#include <cstdio>
#include <QString>
//#include <gtk/gtk.h>
#include <qtextstream.h>
#include <unicode/uchar.h>
#include <unicode/ustring.h>
#include <unicode/normalizer2.h>
#include <unicode/unistr.h>


int main(int cantidad, char* argumentos[])
{
	string str;
	QByteArray vec;
	QString rdo, latin,rdo2;
	QString aux("Páulo miguel -Fernández123456789&-*/+|1!||@·~½¬{[]}=}\¸¸¿+´}}-_.,,");
	QChar qChar;

	//rdo = aux.normalized(QString::NormalizationForm_C);

	/*
    for (UChar32 c = UCHAR_MIN_VALUE; c <= UCHAR_MAX_VALUE; ++ c)
    {
        cout<<"El car "<<(char)c<<" es " <<c<<endl;
    }
    */


/*
	rdo = aux.normalized(QString::NormalizationForm_D,QChar::Unicode_5_0);
	rdo = rdo.toCaseFolded();

    latin = aux.normalized(QString::NormalizationForm_D,QChar::Unicode_5_0);
    vec = aux.toUtf8();


    cout<<"AUX: " <<aux.toStdString()<<endl;

    //cout<<"NORMALIZADO+CASE: " <<rdo.at(0).toAscii()<<endl;
    //cout<<"EN LATIN: " <<latin.toStdString()<<endl;
    for (int i=0; i < rdo.size(); i++)
    {
    	qChar = rdo.at(i);
    	if ( (qChar.isLetterOrNumber()) || (qChar.isSpace()) || (qChar =='-')|| (qChar =='&'))
    		str+= qChar.toAscii();
    }
    cout<<"RDO: " <<str<<endl;
    */

/*
    ManejadorInstrucciones* instrucciones = new ManejadorInstrucciones(argumentos, cantidad);
    instrucciones->ejecutarInstruccionElegida();
    delete(instrucciones);
*/
	Configuracion* conf = Configuracion::GetInstancia();

	Indexador* indexador = new Indexador();

	indexador->indexar(INDICE_AUTOR);

	Logger::log("Instruccion_ProcesarAutor", "ejecutar",
			"Se indexa por autor.");

	delete(indexador);


/*
	Configuracion* conf = Configuracion::GetInstancia("conf.ini");
	//Indexador* indexador = new Indexador(conf->getPathCarpetaTrabajo());
	//delete(indexador);

	string nombreArchivo = "Reportes";
	ManejadorArchivo::CrearDirectorios(conf->getPathCarpetaReportes());
	ManejadorArchivo::CopiarArchivo(conf->getPathCarpetaTrabajo() + ARCHIVO_CONTROL_BIBLIOTECA,
						conf->getPathCarpetaReportes());
	ManejadorArchivo::RenombrarArchivo( conf->getPathCarpetaReportes() + ARCHIVO_CONTROL_BIBLIOTECA,
									conf->getPathCarpetaReportes() + nombreArchivo +
									ARCHIVO_ESPACIOSLIBRES_SUFIX + EXTENSION_ARCHIVO_REPORTE);
*/
	cout<<"Chau mundo"<<endl;
}

















