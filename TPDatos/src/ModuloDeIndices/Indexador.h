/*
 * Indexador.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#ifndef INDEXADOR_H_
#define INDEXADOR_H_

#include "../ModuloEstructuras/Configuracion.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"
#include "../ModuloControladores/ControladorIndice.h"
#include "../ModuloControladores/ControladorBiblioteca.h"


class Indexador
{
private:
	string					pathCarpeta;//path de trabajo
	ParserDeAtributo*		parser;
	ControladorIndice* 		controlIndice;
	ControladorBiblioteca* 	controlBiblioteca;

public:
	Indexador();

	/*
	 * Crea el ambiente necesario para poder registrar una indexacion de
	 * un libro
	 * @param pathDeTrabajo la ruta a la carpeta que se va a usar para
	 * almacenar los archivos.
	 */
	Indexador(string pathDeTrabajo);

	/*
	 * Da la orden a un indice para que indexe segun el tipo de indice.
	 * @param tipoIndice la indexacion deseada puede ser A,E,T o P
	 * Ver tipos Indices definidos como ctes INDICE_
	 */
	void indexar(char tipoIndice);

	/*
	 * Da la orden a un indice para que elimine la indexacion de un libro.
	 * Incluyendo la eliminacion del libro de la biblioteca
	 * @param tipoIndice la indexacion deseada puede ser A,E,T o P
	 * Ver tipos Indices definidos como ctes INDICE_
	 */
	void eliminarIndexado(uint32_t idLibro);

	virtual ~Indexador();
};

#endif /* INDEXADOR_H_ */
