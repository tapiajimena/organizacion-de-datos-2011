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


using namespace std;
class FrontCodedString
{
private:
	string		palabraEncodeada;
	short int	cantidadLetrasPalabraActual;
	short int	cantidadLetrasPalabraAnterior;

public:
	FrontCodedString();
	FrontCodedString* frontCode(FrontCodedString* anterior, string* palabra);
	list<string*>* frontDecode(list<FrontCodedString*>* palabrasFrontCodeadas);


	virtual ~FrontCodedString();
};

#endif /* FRONTCODEDSTRING_H_ */
