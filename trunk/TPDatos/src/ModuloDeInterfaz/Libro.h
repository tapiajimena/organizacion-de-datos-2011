/*
 * Libro.h
 *
 */

#ifndef LIBRO_H_
#define LIBRO_H_

#include <string>
#include <vector>

class Libro
{
private:

	std::string _titulo;

	std::string _autor;

	std::string _ISBN;

	std::vector<std::string> _listaPalabras;

public:

	Libro();

	~Libro();

	std::string getTitulo();

	void setTitulo(std::string titulo);

	std::string getAutor();

	void setAutor(std::string autor);

	std::string getISBN();

	void setISBN(std::string ISBN);

	std::vector<std::string> getListaPalabras();

	void agregarPalabra(std::string palabra);
};

#endif /* LIBRO_H_ */
