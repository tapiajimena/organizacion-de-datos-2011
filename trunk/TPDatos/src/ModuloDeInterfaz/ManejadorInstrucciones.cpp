/*
 * ManejadorInstrucciones.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ManejadorInstrucciones.h"

ManejadorInstrucciones::ManejadorInstrucciones(char* argumentos[], int cantidad) {
	for (int i = 0; i < cantidad; i++) {
		string aux = argumentos[i];
		this->comando[i] = aux;
		cout << i << ": " << this->comando[i] << endl;
	}
}

char ManejadorInstrucciones::armarInstruccion() {
	Logger::log("ManejadorInstrucciones", "armarInstruccion",
			"Se obtiene la instruccion ingresada como parametro");

	return obtenerIDinstruccion(this->comando[1]);
}

void ManejadorInstrucciones::ejecutarInstruccion(char id) {
	switch (id) {
	case 'i':
		this->instruccion = new Instruccion_TomarTexto(id,
				ServiceClass::normalizarString(this->comando[2]));
		this->instruccion->ejecutar();
		break;
	case 'e':
		this->instruccion = new Instruccion_ProcesarEditorial(id);
		this->instruccion->ejecutar();
		break;
	case 'a':
		this->instruccion = new Instruccion_ProcesarAutor(id);
		this->instruccion->ejecutar();
		break;
	case 't':
		this->instruccion = new Instruccion_ProcesarTitulo(id);
		this->instruccion->ejecutar();
		break;
	case 'p':
		this->instruccion = new Instruccion_ProcesarPalabras(id);
		this->instruccion->ejecutar();
		break;
	case 'l':
		this->instruccion = new Instruccion_ListarArchivosTomados(id);
		this->instruccion->ejecutar();
		break;
	case 'o':
		this->instruccion = new Instruccion_ObtenerArchivo(id,
				ServiceClass::convertirAUint32(this->comando[2]));
		this->instruccion->ejecutar();
		break;
	case 'q':
		this->instruccion = new Instruccion_QuitarArchivo(id,
				ServiceClass::convertirAUint32(this->comando[2]));
		this->instruccion->ejecutar();
		break;
	case 'v':
		this->instruccion = new Instruccion_VerEstructura(id,
				obtenerIDinstruccion(this->comando[2]),
				ServiceClass::normalizarString(this->comando[3]));
		this->instruccion->ejecutar();
		break;
	default:
		Logger::log("ManejadorInstrucciones", "ejecutarInstruccion",
				"Comando no valido.");
		break;
	}
}

char ManejadorInstrucciones::obtenerIDinstruccion(string id) {
	char idInstruccion = ' ';

	for (int i = 0; i < id.size(); i++) {
		if (id[i] == '-')
			idInstruccion = id[i + 1];
	}

	Logger::log("ManejadorInstrucciones", "obtenerIDInstruccion",
			"Se codifica.");

	return idInstruccion;
}

void ManejadorInstrucciones::ejecutarInstruccionElegida() {
	ejecutarInstruccion(armarInstruccion());
}

ManejadorInstrucciones::~ManejadorInstrucciones() {
	delete (this->instruccion);
}
