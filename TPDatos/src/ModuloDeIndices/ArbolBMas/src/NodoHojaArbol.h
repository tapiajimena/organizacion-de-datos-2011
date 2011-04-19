/*
 * NodoHojaArbol.h
 *
 *    Autor   	 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 *	Clase utilizada para la representacion de los nodos hoja del arbol.
 *
 */

#ifndef NODOHOJAARBOL_H_
#define NODOHOJAARBOL_H_

#include "NodoArbol.h"

class NodoHojaArbol : public NodoArbol{

private:
	list<uint32_t>* idLibros;
	uint32_t 		idSiguienteHoja;


public:
	NodoHojaArbol();
	NodoHojaArbol(list<uint32_t> idLibros, int idSiguienteHoja);

	int insertar(Dato* dato);
	void partir(NodoArbol* hermano, int sizeBloque, string clavePromovida, int idNodoPromovido);
	int eliminar(Dato* dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int nodosLibres);
	int remover(Dato* dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int cantidadNodosLibres);
	int modificar(Dato* dato);
	Dato* buscar(Dato* dato);

	bool isOverflowded(int sizeBloque);
	bool isUnderflowded(int sizeBloque);


	/* Setters y Getters */
    char getTipoNodo() const;
    void setTipoNodo(char tipoNodo);
	void setId(int id);
    int getId() const;
    list<uint32_t>* getIdLibros() const;
    uint32_t getIdSiguienteHoja() const;
    void setIdLibros(list<uint32_t>* idLibros);
    void setIdSiguienteHoja(uint32_t idSiguienteHoja);

    virtual ~NodoHojaArbol();
};

#endif /* NODOHOJAARBOL_H_ */
