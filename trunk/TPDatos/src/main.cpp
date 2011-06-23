/*
 * main.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include <string>
#include <iostream>
#include "ModuloDeInterfaz/ManejadorInstrucciones.h"
#include "ModuloControladores/ControladorIndice.h"
#include "ModuloEstructuras/Configuracion.h"
#include "../Common/Constantes.h"



int main(int cantidad, char* argumentos[])
{

	ManejadorInstrucciones* instrucciones = new ManejadorInstrucciones(argumentos, cantidad);
	instrucciones->ejecutarInstruccionElegida();
	delete(instrucciones);


	return 0;
}

