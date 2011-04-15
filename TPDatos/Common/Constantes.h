/*
* Constantes.h
*  
*	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
*	Catedra	: SERVETTO-FERRER-FERNANDEZ
*	Materia	: Organizacion de Datos (75.06) - FIUBA
*      
*  
*  Contenedor de las constantes utilizadas en la aplicacion.
*      
*/   

#ifndef CONSTANTES_H_
#define CONSTANTES_H_


/* CONSTANTES DEFINIDAS PARA ARCHIVO DE STOPWORDS */

/* Define el caracter utilizado como separador */
#define STOPWORDS_TOKEN "\n"

/* Define la cantidad de caracteres de cada stopword */
#define STOPWORDS_LENGTH 30

/* Define fin de línea en una cadena*/
#define CARACTER_FIN_DE_LINEA "\n"

/* Define los caracteres que separan una palabra de otra */
#define SEPARADORES_DE_PALABRAS " .,-;:¿?¡!'<@>)("

/* Define los caracteres que separan palabras pero no son signos de puntuación
 * Se usa para obtener títulos de libros o nombres de editoriales con la puntuación original
 */
#define SEPARADORES_DE_PALABRAS_CON_PUNTUACION " <>"

/* Cadenas de caracteres clave que identifican un atributo de un libro */
#define IDENTIFICADOR_TITULO "#TITULO_LIBRO"

#define IDENTIFICADOR_AUTOR "#AUTOR_LIBRO"

#define IDENTIFICADOR_EDITORIAL "#EDITORIAL_LIBRO"


/* CONSTANTES DEFINIDAS PARA ARCHIVO DE CONTROL */

/* Define el caracter utilizado como separador */
#define CONTROL_TOKEN "|"

/*Usado para el ArchivoControlLibros al momento de guardar el archivo de control*/
#define INICIALIZACION_ARCHIVO_LIBRO_CONTROL "|0|-|-|-|-"

#endif /* CONSTANTES_H_ */
