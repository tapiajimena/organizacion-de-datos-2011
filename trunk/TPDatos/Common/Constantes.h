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

/* VALORES DE CONFIGURACION*/

#define IDENTIFICADOR_CARPETA_TRABAJO "#CARPETA_TRABAJO"
#define IDENTIFICADOR_CARPETA_REPORTES "#CARPETA_REPORTES"
#define IDENTIFICADOR_ARCHIVO_STOPWORDS "#ARCHIVO_STOPWORDS"

#define ARCHIVO_CONFIGURACION_DEFAULT "conf.ini"

#define CARPETA_TRABAJO_DEFAULT "/Indices"
#define ARCHIVO_STOPWORDS "stopWords.txt"


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

/* CONSTANTES DEFINIDAS PARA ARCHIVO DE LIBROS */

/* Define la cantidad de bytes utilizada para la metadata del tamanio del libro */
#define METADATA_SIZE_BOOK 4

/* CONSTANTES DEFINIDAS PARA ARCHIVO DE TERMINOS */

/* Define el fin de una palabra en el archivo de t�rminos*/
#define FIN_DE_TERMINO "|"

/* CONSTANTES DEFINIDAS PARA ARCHIVO DE CONTROL */

/* En caso que no se haya podido encontrar un offset con tamanio libre suficiente
 * para albergar un nuevo libro, devuelve que se debe ingresar al fin del archivo de libros */
#define FIN_DE_ARCHIVO -1

/* Define el caracter utilizado como separador */
#define CONTROL_TOKEN "|"

/*Usado para el ArchivoControlLibros al momento de guardar el archivo de control*/
#define INICIALIZACION_ARCHIVO_LIBRO_CONTROL "|0|-|-|-|-|"

/* Define la cantidad de caracteres de cada stopword */
#define CONTROL_LENGTH 256

/* CONSTANTES DEFINIDAS PARA EL ARBOL */
#define SIZE_BLOQUE 512

#define OVERFLOWDED -10

#define MAX_SIZE_DATO 100000 //cambiar a cuenta valida

#define DUPLICADO -30

#define ERROR -1

/* CONSTANTES DEFINIDAS PARA EL HASH */
#define TAMANIOCUBETA 1024 //Tamanio de cubeta: cantidad de elementos (4), lista de offsets (n*4), offset prox. cubeta(4)

#define TAMANIODATOTABLA 8 //Tamanio del elemento de la tabla de hash: offset a cubeta inicial y cantidad de elementos

#define BYTENULOENDISCO '.' //Byte que se considera nulo. Se usa para rellenar espacio libre en las cubetas del hash.

/* CONSTANTES DEFINIDAS PARA VALORES DE RETORNO */
#define EXITO 0

#define ERROR_ARCHIVO 1



/* VALORES DE CONTROLADOR INDICE*/

#define INDICE_AUTOR  'A'
#define INDICE_EDITORIAL  'E'
#define INDICE_TITULO  'T'
#define INDICE_PALABRAS  'P'

#define CONSULTA_INDICE_AUTOR  'Z'
#define CONSULTA_INDICE_EDITORIAL  'Y'
#define CONSULTA_INDICE_TITULO  'X'
#define CONSULTA_INDICE_PALABRAS  'W'

#define CARPETA_DEFAULT_INDICES "Indices/"

#define EXTENSION_ARCHIVO_INDICE ".dat"
#define EXTENSION_ARCHIVO_REPORTE ".txt"

#define ARCHIVO_TABLA 	"ArchivoTabla"
#define ARCHIVO_CUBETAS "ArchivoCubetas"
#define ARCHIVO_BIBLIOTECA "Biblioteca"
#define ARCHIVO_CONTROL_BIBLIOTECA "BibliotecaControl.txt"

#define ARCHIVO_INDICE_AUTOR "IndiceAutor"
#define ARCHIVO_INDICE_EDITORIAL "IndiceEditorial"
#define ARCHIVO_INDICE_PALABRAS "IndicePalabra"
#define ARCHIVO_INDICE_TITULO "IndiceTitulo"

#define ARCHIVO_TABLA_SUFIX "_Tabla"
#define ARCHIVO_INDICE_SUFIX "_Indice"
#define ARCHIVO_ESPACIOSLIBRES_SUFIX "_EspaciosLibres"
#define ARCHIVO_BLOQUES_SUFIX "_Bloques"


/* MANEJADOR INSTRUCCIONES */
#define MAX_COMANDOS 10







#endif /* CONSTANTES_H_ */
