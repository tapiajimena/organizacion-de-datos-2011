/*
* Libro.h
*
*	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
*	Catedra	: SERVETTO-FERRER-FERNANDEZ
*	Materia	: Organizacion de Datos (75.06) - FIUBA
*
*
*
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
};

#endif /* LIBRO_H_ */
