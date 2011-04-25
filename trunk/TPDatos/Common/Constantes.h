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
#define SIZE_BLOQUE 32678

#define OVERFLOWDED -10

#define MAX_SIZE_DATO 100000 //cambiar a cuenta valida

#define DUPLICADO -30

#define ERROR -1

/* CONSTANTES DEFINIDAS PARA EL HASH */
#define TAMANIOCUBETA 1024 //Tamanio de cubeta: cantidad de elementos (4), lista de offsets (n*4), offset prox. cubeta(4)

#define TAMANIODATOTABLA 8 //Tamanio del elemento de la tabla de hash: offset a cubeta inicial y cantidad de elementos

/* CONSTANTES DEFINIDAS PARA VALORES DE RETORNO */
#define EXITO 0

#define ERROR_ARCHIVO 1



/* VALORES DE CONTROLADOR INDICE*/

#define INDICE_AUTOR  'A'
#define INDICE_EDITORIAL  'E'
#define INDICE_TITULO  'T'
#define INDICE_PALABRAS  'P'

#define CARPETA_DEFAULT_INDICES "Indices/"

#define ARCHIVO_BIBLIOTECA "Biblioteca.dat"
#define ARCHIVO_INDICE_AUTOR "IndiceAutor.dat"
#define ARCHIVO_INDICE_EDITORIAL "IndiceEditorial.dat"
#define ARCHIVO_INDICE_PALABRAS "IndicePalabra.dat"
#define ARCHIVO_INDICE_TITULO "IndiceTitulo.dat"
#define ARCHIVO_CONTROL_BIBLIOTECA "BibliotecaControl.dat"










#endif /* CONSTANTES_H_ */
