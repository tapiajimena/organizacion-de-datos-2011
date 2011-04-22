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
#include "../../../ModuloDeTipos/DatoElementoNodo.h"

class NodoHojaArbol : public NodoArbol{

private:
    uint32_t idSiguienteHoja;
    list<DatoElementoNodo*> elementos;
public:
    NodoHojaArbol();
    NodoHojaArbol(list<uint32_t> idLibros, int idSiguienteHoja);
    int insertar(string clave);
    void partir(NodoArbol *hermano, int sizeBloque, string clavePromovida, int idNodoPromovido);
    int eliminar(Dato *dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int nodosLibres);
    int remover(Dato *dato, uint32_t offset, fstream fs, unsigned int cantidadNodos, fstream arcLibros, unsigned int cantidadNodosLibres);
    int modificar(Dato *dato);
    Dato *buscar(Dato *dato);
    bool agregarElemento(DatoElementoNodo* elemento);
    bool isOverflowded(int sizeBloque);
    bool isUnderflowded(int sizeBloque);
    char getTipoNodo() const;
    void setTipoNodo(char tipoNodo);
    void setId(int id);
    int getId() const;
    uint32_t getIdSiguienteHoja() const;
    void setIdSiguienteHoja(uint32_t idSiguienteHoja);
    int getNivel() const;
    void setNivel(int nivel);
    virtual ~NodoHojaArbol();
    list<DatoElementoNodo*> getElementos() const;
    void setElementos(list<DatoElementoNodo*> elementos);

};

#endif /* NODOHOJAARBOL_H_ */
