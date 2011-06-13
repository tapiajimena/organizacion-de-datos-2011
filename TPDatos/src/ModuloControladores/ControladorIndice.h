/*
 * ControladorIndice.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *	Se encarga del control de los indices.
 *  Los cuatro tipos de indices que puede crear son:
 *  		-Autor (usa un arbol)
 *  		-Editorial (usa un arbol)
 *  		-Titulo (usa un hash)
 *  		-Palabras (Usa  hash)
 *  Crear instancias concretas del COntroladorIndice (una para cada tipo de indice)
 *  asi se disminuye el tiempo en indexar y consultar
 */

#ifndef CONTROLADORINDICE_H_
#define CONTROLADORINDICE_H_

#include <stdint.h>

#include "../../Common/Utilitarios/ServiceClass.h"
#include "../ModuloDeTipos/CaseFoldedString.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"
#include "../ModuloEstructuras/Configuracion.h"
#include "../ModuloEstructuras/Libro.h"
#include "../ModuloDeIndices/Hash/Hash.h"
#include "../ModuloDeIndices/ArbolBMas/BPlusTree.h"


using namespace std;
class ControladorIndice
{
private:
	Hash* 		indiceHash;
	BPlusTree* 	indiceArbol;
	DatoElementoNodo* datoElementoNodo;
	string		pathCarpeta;//path de trabajo


public:
	/*
	 * Setea el path de trabajo al default
	 */
	ControladorIndice();

	/*
	 * Se setea el path de trabajo
	 */
	ControladorIndice(string pathCarpeta);

	/*
	 * Crean un nuevo indice del tipo autor,
	 * editorial, titulo y palabras.
	 */
	void nuevoIndiceAutor();
	void nuevoIndiceEditorial();
	void nuevoIndiceTitulo();
	void nuevoIndicePalabras();
	void nuevoIndiceOcurrenciaTerminos();

	/*
	 * Analizan una consulta del tipo autor,
	 * editorial, titulo y palabras.
	 * autor si es true se indexa por autor sino
	 * por editorial
	 */
	void consultarPorAutorOEditorial(string consulta);
	void consultarPorTitulo(string consulta);
	void consultarPorPalabras(string consulta);

	/*
	 * Indexan en un indice Arbol el autor o editorial
	 *@param parLibroOffset contiene el libro parseado y su id (offset) en la biblioteca
	 *@param tipoIndice la clase de indexacion a realizar
	 */
	void indexar(pair<Libro*,uint32_t> parLibroOffset, char tipoIndice);

	/*
	 * elimina la indexacion de un libro
	 * @param libro con las claves a eliminar offset de biblioteca donde se encuentra el archivo a
	 * 	eliminar los indices
	 */
	void eliminarIndexado(Libro* libroRemover, uint32_t idLibro, list<char>* tiposIndices);

	void generarReporte(char tipo, string nombreArchivo);

private:

	/*
	 * Indexan en un indice Arbol el autor o editorial
	 *
	 */
	void indexarPorAutorOEditorial(pair<Libro*,uint32_t> parLibroOffset, bool autor);

	/*
	 * Indexan en un indice Hash el titulo o palabras.
	 *
	 */
	void indexarPorTitulo(pair<Libro*,uint32_t> parLibroOffset);
	void indexarPorPalabras(pair<Libro*,uint32_t> parLibroOffset);
	void indexarPorOcurrenciaTerminos(pair<Libro*,uint32_t> parLibroOffset);
	void indexarPorTerminosId(pair<string,uint32_t> parTerminoId);

	void eliminarIndexadoPorTipo(char tipo, Libro* libroRemover,uint32_t idLibro);

public:
	virtual ~ControladorIndice();

};

#endif /* CONTROLADORINDICE_H_ */
