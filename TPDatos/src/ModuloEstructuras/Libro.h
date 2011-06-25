/*
* Libro.h
*
*	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
*	Catedra	: SERVETTO-FERRER-FERNANDEZ
*	Materia	: Organizacion de Datos (75.06) - FIUBA
*
*
*	Esta clase se usa como ODT, Object Data Transfer, es decir, s�lo para pasar informaci�n de un
*	lado a otro.
*
*/

#ifndef LIBRO_H_
#define LIBRO_H_

#include <string>
#include <vector>
#include <map>
#include <stdint.h>


//Guarda claves string unicas y un int con la cantidad de apariciones
typedef std::map<std::string, int> EstructuraPalabrasClave;

class Libro
{
private:

	std::string _titulo;

	std::string _autor;

	//std::string _ISBN;

	std::string _editorial;

	//Offset en disco del inicio del registro de archivo respecto del inicio de archivo.
	uint32_t offset;

	//Estructura que guarda las palabras clave del libro y asociadas al número de veces que aparece cada palabra en el libro
	EstructuraPalabrasClave* _palabrasClave;

	//Lista de ocurrencias de t�rminos. El ID es el del documento, y la posici�n es la posici�n en el vector.
	//No se cuentan las stopwords
	//(se hace lo mismo con las consultas, de manera que consulta coincide bien con documento literalmente)
	std::vector<std::string> listaOcurrenciasDeTerminos;

public:

	Libro();

	~Libro();

	std::string getTitulo();

	void setTitulo(std::string titulo);

	std::string getAutor();

	void setAutor(std::string autor);

	void setEditorial(std::string);

	std::string getEditorial();

	std::string getISBN();

	void setISBN(std::string ISBN);

	EstructuraPalabrasClave* getPalabrasClave();

	void agregarPalabraClave(std::string palabra);

	uint32_t getOffset() const;

    void setOffset(uint32_t offset);
    void setPalabrasClave(EstructuraPalabrasClave *_palabrasClave);

    //Toma las palabras clave de un libro y se las carga para s�
    void copiarEstructuraDePalabrasClave(Libro* libro);

    //Devuelve una COPIA de la lista de ocurrencias de t�rminos.
    std::vector<std::string> getOcurrenciasDeTerminos();

    //Carga el t�rmino en la lista de ocurrencias de t�rminos. La carga debe ser secuencial
    //desde el parser, de manera que la posici�n en el libro est� dada por el orden en que
    //se ingresaron a la lista de ocurrencias.
    void cargarOcurrenciaDeTermino(std::string termino);
};

#endif /* LIBRO_H_ */
