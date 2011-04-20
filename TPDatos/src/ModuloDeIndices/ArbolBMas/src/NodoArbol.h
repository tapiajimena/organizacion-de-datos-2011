/*
 * NodoArbol.h
 *
 *    Autor   	 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 *	Clase utilizada como interfaz para los nodos del arbol.
 *
 */

#ifndef NODOARBOL_H_
#define NODOARBOL_H_

#include <list>
#include <fstream>
#include "../../../ModuloDeTipos/Dato.h"

using namespace std;
class NodoArbol {
protected:
	int id;
	long int nodoPadre;
	char tipoNodo;//H si es hoja, I si es interno

public:
	NodoArbol();

	virtual int insertar(Dato* dato)=0;
	virtual void partir(NodoArbol* hermano, int sizeBloque, string clavePromovida, int idNodoPromovido)=0;
	virtual int eliminar(Dato* dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int cantidadNodosLibres)=0;

	virtual bool isOverflowded(int sizeBloque)=0;
	virtual bool isUnderflowded(int sizeBloque)=0;

	/* Setters y Getters */
    virtual char getTipoNodo() const=0;
    virtual void setTipoNodo(char tipoNodo)=0;
	virtual void setId(int id)=0;
    virtual int getId() const=0;

	virtual ~NodoArbol();


};

#endif /* NODOARBOL_H_ */
