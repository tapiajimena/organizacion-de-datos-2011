/*
 * ArchivoTerminos.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ArchivoTerminos.h"


ArchivoTerminos::ArchivoTerminos(string nombreArchivo)
{
	char* cstrPath = new char[nombreArchivo.size() + 1];
	strcpy(cstrPath, nombreArchivo.c_str());

	if (ManejadorArchivo::Existe(cstrPath, this->archivoTerminos)) {
		ManejadorArchivo::Abrir(cstrPath, this->archivoTerminos, true);
	} else {
		ManejadorArchivo::CrearSiNoExiste(cstrPath, this->archivoTerminos);
	}
	delete[] cstrPath;
}

ArchivoTerminos::~ArchivoTerminos()
{
	ManejadorArchivo::Cerrar(archivoTerminos);
}

uint32_t ArchivoTerminos::ingresarTermino(string palabra)
{
	stringstream ss;

	uint32_t offsetDeTermino = (uint32_t) ManejadorArchivo::GetSizeArchivo( this->archivoTerminos);
	cout << "ingreso " << palabra << "en: " << offsetDeTermino << endl;

	ss << palabra;
	ss << FIN_DE_TERMINO;

	string aux = ss.str();
	aux = aux.substr(0, aux.length() - 1);

	stringstream ss1;
	ss1 << aux;

	cout << ss1.str() << endl;
	ManejadorArchivo::Escribir(this->archivoTerminos, &ss,offsetDeTermino);

	return (uint32_t) offsetDeTermino;
}

string ArchivoTerminos::obtenerTermino(uint32_t idTermino)
{
	string termino;
	string aux;
	uint32_t PRR = idTermino; //Posicion de Registro Relativo de archivo.
	bool finTermino = false;

	ManejadorArchivo::IrAlInicio(this->archivoTerminos);
	ManejadorArchivo::PosicionarPunteroLecturaEn(this->archivoTerminos, PRR);

	while(!finTermino)
	{
		//cout << "***" << idTermino << endl;
		aux = ManejadorArchivo::LeerCaracteres(this->archivoTerminos,1);
		//cout << "==== " << idTermino << endl;
		if((int)aux[0] != 124)
			termino += aux;
		else
			finTermino = true;
	}
	return termino;
}

vector<pair<string, uint32_t> > ArchivoTerminos::obtenerTerminos()
{
	//Para dejar el archivo en la misma posición, tras terminar el método.
	uint32_t offsetPrevio = this->archivoTerminos.tellg();

	uint32_t PRR = 0; // PRR = Posicion de Registro Relativo en archivo.
	uint32_t tamanioArchivoTerminos = ManejadorArchivo::GetSizeArchivo(this->archivoTerminos);

	ManejadorArchivo::IrAlInicio(this->archivoTerminos);
	string termino;

	vector<pair<string, uint32_t> > listaTerminos;

	pair<string, uint32_t> elementoTermino;

	//cout<<"arranco... PRR = "<<PRR<<"    Tamanio archivo: "<<tamanioArchivoTerminos<<endl;

	while( PRR < tamanioArchivoTerminos)
	{
		//cout<<"PRR (ID): "<<PRR<<endl;
		termino = this->obtenerTermino(PRR);
		//cout<<"Termino: "<<termino<<endl;

		elementoTermino.first = termino;
		elementoTermino.second = PRR; // PRR = idTermino

		PRR = this->archivoTerminos.tellg();// + 1?; //tomamos la siguiente posicion, considerando el separador de terminos.

		listaTerminos.push_back(elementoTermino);
	}

	this->archivoTerminos.seekg(offsetPrevio, ios::beg);
	return listaTerminos;

}

/*
vector<pair<string, uint32_t> > ArchivoTerminos::obtenerTerminos()
{
	//Para dejar el archivo en la misma posición, tras terminar el método.
	uint32_t offsetPrevio = this->archivoTerminos.tellg();

	uint32_t PRR = 0; //puntero local

	vector<pair<string, uint32_t> > listaTerminos;

	uint32_t tamanioArchivoTerminos = ManejadorArchivo::GetSizeArchivo(this->archivoTerminos);

	ManejadorArchivo::PosicionarPunteroLecturaEn(this->archivoTerminos, 0);

	string palabra = "";
	string letra = "";
	char* letraChar;
	uint32_t offsetTermino = 0;

	pair<string, uint32_t> elementoTermino;

	while( PRR < tamanioArchivoTerminos)
	{
		//este metodo de la clase leerCaracteres no anda bien, o se pisa, que se yo que corno le pasa
		//letraChar = ManejadorArchivo::LeerCaracteres(this->archivoTerminos, 1).at(0); //aca lee basura... ??

		letraChar = new char[1];
		this->archivoTerminos.read(letraChar, 1);

		if(*letraChar != FIN_DE_TERMINO)
		{
			letra = letraChar; //error en el valgrind. var. no inicializada
			palabra.append(letra);
		}
		else
		{
			if(palabra.size() > 0)
			{
				elementoTermino.first = palabra;
				elementoTermino.second = offsetTermino;
				listaTerminos.push_back(elementoTermino);
			}
			palabra = "";
			offsetTermino = PRR + 1;
		}
		delete[] letraChar;
		PRR = this->archivoTerminos.tellg();
	}

	this->archivoTerminos.seekg(offsetPrevio, ios::beg);
	return listaTerminos;
}
*/
