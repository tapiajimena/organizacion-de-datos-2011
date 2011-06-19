/*
 * ConsultaIndice.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#ifndef CONSULTAINDICE_H_
#define CONSULTAINDICE_H_

#include "../ModuloEstructuras/Configuracion.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"
#include "../ModuloControladores/ControladorIndice.h"
#include "../ModuloControladores/ControladorBiblioteca.h"
#include "../ModuloEstructuras/CalculadorDeNormas.h"


class ConsultaIndice
{
private:
	string					pathCarpeta;//path de trabajo
	ControladorIndice* 		controlIndice;
	ControladorBiblioteca* 	controlBiblioteca;

public:
	ConsultaIndice();

	/*
	 * Crea el ambiente necesario para poder registrar una indexacion de
	 * un libro
	 * @param pathDeTrabajo la ruta a la carpeta que se va a usar para
	 * almacenar los archivos.
	 */
	ConsultaIndice(string pathDeTrabajo);

	/*
	 *  Da la orden a un indice para que consulte segun el tipo.
	 * @param tipo de estructura la indexacion deseada puede ser QA,QE,QT o QP
	 * Ver tipos Indices definidos como ctes CONSULTA_INDICE_
	 */
	void consultar(char tipoIndice, string consulta);

	void consultarAutor(string consulta);
	void consultarTitulo(string consulta);
	void consultarPalabras(string consulta);
	void consultarEditorial(string consulta);

	/*
	 * Da la orden a un indice para que genere el reporte segun el tipo.
	 * @param tipo de estructura la indexacion deseada puede ser A,E,T o P
	 * Ver tipos Indices definidos como ctes INDICE_
	 */
	void generarReporte(char tipoIndice, string nombreArchivo);


	void crearTipoConsulta(char tipoIndice, string consulta);


	virtual ~ConsultaIndice();
};

#endif /* CONSULTAINDICE_H_ */
