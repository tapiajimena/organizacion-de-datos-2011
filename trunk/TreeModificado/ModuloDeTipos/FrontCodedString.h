/*
 * FrontCodedString.h
 *
 *    Autor   	 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#ifndef FRONTCODEDSTRING_H_
#define FRONTCODEDSTRING_H_

#include <list>
#include <string>
#include <iostream>

using namespace std;
class FrontCodedString
{
private:
	string		palabraEncodeada;
	short int	cantidadLetrasPalabraActual;
	short int	cantidadLetrasPalabraAnterior;

	FrontCodedString* frontCode(string* palabraAnterior, string* palabraAEncodear);

public:
	FrontCodedString();

	list<FrontCodedString*>* frontCode(list<string*>* listaDePalabras);

	list<string*>* frontDecode(list<FrontCodedString*>* palabrasFrontCodeadas);

	//getters y setters
    short int getCantidadLetrasPalabraActual() const;
    short int getCantidadLetrasPalabraAnterior() const;
    string getPalabraEncodeada() const;
    void setCantidadLetrasPalabraActual(short int cantidadLetrasPalabraActual);
    void setCantidadLetrasPalabraAnterior(short int cantidadLetrasPalabraAnterior);
    void setPalabraEncodeada(string palabraEncodeada);

    virtual ~FrontCodedString();
};

#endif /* FRONTCODEDSTRING_H_ */
