/*
 * ManejadorInstrucciones.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Clase que representa la logica del menu de instrucciones
 *	que se reciben por consola.
 *
 */

#ifndef MANEJADORINSTRUCCIONES_H_
#define MANEJADORINSTRUCCIONES_H_

#include <iostream>
#include <istream>
#include <sstream>

#include "../../Common/Utilitarios/Logger.h"

#include "../ModuloDeInterfaz/Instruccion_ListarArchivosTomados.h"
#include "../ModuloDeInterfaz/Instruccion_ObtenerArchivo.h"
#include "../ModuloDeInterfaz/Instruccion_ProcesarAutor.h"
#include "../ModuloDeInterfaz/Instruccion_ProcesarEditorial.h"
#include "../ModuloDeInterfaz/Instruccion_ProcesarPalabras.h"
#include "../ModuloDeInterfaz/Instruccion_ProcesarTitulo.h"
#include "../ModuloDeInterfaz/Instruccion_QuitarArchivo.h"
#include "../ModuloDeInterfaz/Instruccion_TomarTexto.h"
#include "../ModuloDeInterfaz/Instruccion_VerEstructura.h"

using namespace std;

class ManejadorInstrucciones {
private:
	Instruccion* instruccion;
	string comando[10];
public:
	ManejadorInstrucciones(char* argumentos[], int cantidad);

	/* *
	 * Metodo que se encarga de armar cada instrucción
	 * obteniendo los datos de la lectura de un archivo
	 */
	char armarInstruccion();

	/**
	 * Se encarga ejecutar la instruccion correspondiente
	 * dependiendo del parametro.
	 * @param id: identificador de la instruccion a ejecutar.
	 */
	void ejecutarInstruccion(char id);

	/**
	 * Devuelve el identificador de la instruccion que corresponde
	 * al parametro pasado.
	 */
	char obtenerIDinstruccion(string id);

	/**
	 * Metodo principal de la clase que elige y ejecuta la
	 * instruccion correspondiente.
	 */
	void ejecutarInstruccionElegida();

	virtual ~ManejadorInstrucciones();
};

#endif /* MANEJADORINSTRUCCIONES_H_ */
