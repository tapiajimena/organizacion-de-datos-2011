/*
 * NodoInternoArbol.h
 *
 *    Autor   	 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 * Clase que representa los nodos internos (no hoja) del arbol.
 *
 */

#ifndef NODOINTERNOARBOL_H_
#define NODOINTERNOARBOL_H_


#include <list>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "NodoArbol.h"

using namespace std;

class NodoInternoArbol : public NodoArbol {
private:
	list<int> hijos;
	list<string> claves;

public:
	NodoInternoArbol();

	int insertar(DatoElementoNodo elemento);
	void partir(NodoArbol* hermano, int sizeBloque, DatoElementoNodo clavePromovida, int idNodoPromovido);
	int eliminar(Dato* dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int cantidadNodosLibres);
	int remover(Dato* dato, uint32_t offset, fstream* fs, unsigned int* nodeCounter, fstream* freefs, unsigned int* freeNodeCounter);
	void agregarClaveHijo(DatoElementoNodo clave, int idHijo);
	uint32_t buscarClave(DatoElementoNodo clave);

    void serializar(iostream* s);
    void hidratar(iostream* s);

    void agregarHijo(int idHijo);
    void agregarClave(string clave);

	bool isOverflowded(int blockSize);
    bool isUnderflowded(int blockSize);


	/* Getters y Setters */
    char getTipoNodo() const;
    void setTipoNodo(char tipoNodo);

    void setId(int id);
    int getId() const;

    int getNivel() const;
    void setNivel(int nivel);

    void setClaves(list<string> claves);
    void setHijos(list<int> hijos);

    list<string> getClaves();
    list<int> getHijos();


	virtual ~NodoInternoArbol();
};

#endif /* NODOINTERNOARBOL_H_ */
