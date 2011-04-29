/*
 * Configuracion.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 * Contiene la informacion de configuracion, path de trabajo y ruta al archivo de stopwords.
 * Abre el archivo de configuracion lo interpreta y lo cierra.
 *      
 */

#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <iostream>
#include <string.h>

#include "../Common/Constantes.h"
#include "../Common/Utilitarios/Logger.h"
#include "../Common/Utilitarios/ServiceClass.h"
#include "../ModuloEstructuras/Configuracion.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"

using namespace ManejadorArchivo;
class Configuracion
{
private:
	static 	Configuracion* pInstancia;
	string	pathCarpetaTrabajo;
	string	pathArchivoStopWords;


public:
	static Configuracion* GetInstancia();
	static Configuracion* GetInstancia(string pathConfiguracion);

	/*
	 * Getters y setters
	 */
	string getPathArchivoStopWords() const;
    string getPathCarpetaTrabajo() const;
    void setPathArchivoStopWords(string pathArchivoStopWords);
    void setPathCarpetaTrabajo(string pathCarpetaTrabajo);

private:

    /*
     * Obtiene el contenido del archivo de configuracion.
     * Interpreta este archivo de la siguiente forma:
     *Ej:
     * 		#CARPETA_TRABAJO=/Indices
	 *		#ARCHIVO_STOPWORDS=stopwordstest.txt
	 *@param pathConfiguracion ruta al archivo de configuracion
     */
	Configuracion(string pathConfiguracion);
	virtual ~Configuracion();


};

#endif /* CONFIGURACION_H_ */
