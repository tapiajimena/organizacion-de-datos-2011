/*
 * Libro.h
 *
 */

#ifndef LIBRO_H_
#define LIBRO_H_

#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, int> EstructuraPalabrasClave;

class Libro
{
private:

	std::string _titulo;

	std::string _autor;

	std::string _ISBN;

	//Estructura que guarda las palabras clave del libro y asociadas al número de veces que aparece cada palabra en el libro
	EstructuraPalabrasClave _palabrasClave;

public:

	Libro();

	~Libro();

	std::string getTitulo();

	void setTitulo(std::string titulo);

	std::string getAutor();

	void setAutor(std::string autor);

	std::string getISBN();

	void setISBN(std::string ISBN);

	EstructuraPalabrasClave getPalabrasClave();

	void agregarPalabraClave(std::string palabra);
};

#endif /* LIBRO_H_ */
