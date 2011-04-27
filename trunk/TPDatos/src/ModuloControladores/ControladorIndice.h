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
 */

#ifndef CONTROLADORINDICE_H_
#define CONTROLADORINDICE_H_

#include <stdint.h>

#include "../../Common/Utilitarios/ServiceClass.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"
#include "../ModuloEstructuras/Libro.h"
#include "../ModuloDeIndices/Hash/Hash.h"
#include "../ModuloDeIndices/ArbolBMas/src/ArbolBMas.h"


using namespace std;
class ControladorIndice
{
private:
	Hash* 		indiceHash;
	ArbolBMas* 	indiceArbol;
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
	void eliminarIndexado(Libro* libroRemover);

private:

	/*
	 * Indexan en un indice Arbol el autor o editorial
	 *
	 */
	void indexarPorAutorOEditorial(pair<Libro*,uint32_t> parLibroOffset);

	/*
	 * Indexan en un indice Hash el titulo o palabras.
	 *
	 */
	void indexarPorTitulo(pair<Libro*,uint32_t> parLibroOffset);
	void indexarPorPalabras(pair<Libro*,uint32_t> parLibroOffset);

public:
	virtual ~ControladorIndice();

};

#endif /* CONTROLADORINDICE_H_ */
