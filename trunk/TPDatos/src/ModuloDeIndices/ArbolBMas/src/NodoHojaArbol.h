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
	list<uint32_t> idLibros;
	uint32_t idSiguienteHoja;


public:
	NodoHojaArbol();


	int insertar(Dato* dato);
	void partir(NodoArbol* hermano, int sizeBloque, Dato* keyPromovida, int* idPromovido);
	int eliminar(Dato* dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int nodosLibres);


	int modificar(Dato* dato);
	Dato* buscar(Dato* dato);
	list<uint32_t> getClaves();

	virtual bool isOverflowded(int sizeBloque)=0;
	virtual bool isUnderflowded(int sizeBloque)=0;

	NodoHojaArbol(list<uint32_t> idLibros, int idSiguienteHoja);

	virtual ~NodoHojaArbol();
};

#endif /* NODOHOJAARBOL_H_ */
