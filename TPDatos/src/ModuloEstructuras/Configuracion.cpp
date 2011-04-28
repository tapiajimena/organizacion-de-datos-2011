/*
 * Configuracion.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "Configuracion.h"

Configuracion* Configuracion::pInstancia= 0;

Configuracion* Configuracion::GetInstancia(string pathConfiguracion)
{
	if (pInstancia == 0)  // ¿Es la primera llamada?
		pInstancia = new Configuracion(pathConfiguracion); // Se crea la instancia

	return pInstancia; // se devuelve la direccion de la instancia
}

Configuracion::Configuracion(string pathConfiguracion)
{
	char linea[512],*aux;
	fstream arcConf;

	Abrir(pathConfiguracion.c_str(), arcConf, false);
	while (!arcConf.eof())
	{
		arcConf.getline(linea,sizeof(linea));
		aux = strtok(linea, "=");
		while (aux != NULL)
		{
			if (strcmp(aux, IDENTIFICADOR_CARPETA_TRABAJO)== 0)
			{
				aux = strtok(NULL, "=");
				setPathCarpetaTrabajo(aux);
			}
			else if  (strcmp(aux, IDENTIFICADOR_ARCHIVO_STOPWORDS)==0)
			{
				aux = strtok(NULL, "=");
				setPathArchivoStopWords(aux);
			}
			else
				Logger::log("ParserDeConfiguracion","parsear", "el tipo no es valido para un archivo de configuracion");
			aux = strtok(NULL, "=");
		}
	}
	Cerrar(arcConf);
}

string Configuracion::getPathArchivoStopWords() const
{
    return pathArchivoStopWords;
}

string Configuracion::getPathCarpetaTrabajo() const
{
    return pathCarpetaTrabajo;
}

void Configuracion::setPathArchivoStopWords(string pathArchivoStopWords)
{
    this->pathArchivoStopWords = pathArchivoStopWords;
}

void Configuracion::setPathCarpetaTrabajo(string pathCarpetaTrabajo)
{
    this->pathCarpetaTrabajo = pathCarpetaTrabajo;
}

Configuracion::~Configuracion()
{

}
