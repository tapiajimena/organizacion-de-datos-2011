/*
 * FrontCoderString.cpp
 *
 *    Autor   	 : GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *    Catedra    : SERVETTO-FERRER-FERNANDEZ
 *    Materia    : Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "FrontCodedString.h"

FrontCodedString::FrontCodedString() {
	this->cantidadLetrasPalabraActual = 0;
	this->cantidadLetrasPalabraAnterior = 0;
}

list<FrontCodedString*>* FrontCodedString::frontCode(
		list<string*>* listaDePalabras) {
	list<FrontCodedString*>* resultado = new list<FrontCodedString*> ();

	FrontCodedString* frontCodedString = new FrontCodedString();

	string* palabraInicial = listaDePalabras->front();

	//quito a la palabraInicial de la lista
	//para empezar a encodear a partir de la segunda
	listaDePalabras->pop_front();

	//la palabraInicial se guarda sin encodear
	frontCodedString->palabraEncodeada = *palabraInicial;
	frontCodedString->cantidadLetrasPalabraAnterior = 0;
	frontCodedString->cantidadLetrasPalabraActual = palabraInicial->length();
	resultado->push_back(frontCodedString);

	string* palabraAnterior = palabraInicial;
	for (list<string*>::const_iterator ci = listaDePalabras->begin(); ci
			!= listaDePalabras->end(); ++ci) {

		frontCodedString = frontCode(palabraAnterior, (*ci));

		palabraAnterior=(*ci);
		resultado->push_back(frontCodedString);
	}

	return resultado;
}

list<string*>* FrontCodedString::frontDecode(
		list<FrontCodedString*>* palabrasFrontCodeadas) {

	list<string*>* resultado = new list<string*> ();
	string* palabraDecodificada = new string();

	//tomo el primer elemento no encodeado
	//para comenzar a realizar las comparaciones
	FrontCodedString* anterior = palabrasFrontCodeadas->front();

	//quito el primer elemento de la lista para empezar a iterar
	//por el segundo
	palabrasFrontCodeadas->pop_front();

	//guardo la primera palabra que no estaba encodeada.
	palabraDecodificada = &(anterior->palabraEncodeada);

	resultado->push_back(palabraDecodificada);

	string* palabraDecodificadaAnterior = palabraDecodificada;
	for (list<FrontCodedString*>::const_iterator ci =
			palabrasFrontCodeadas->begin(); ci != palabrasFrontCodeadas->end(); ++ci) {

		palabraDecodificada = new string();

		palabraDecodificada->append(palabraDecodificadaAnterior->substr(0,(*ci)->cantidadLetrasPalabraAnterior));
		palabraDecodificada->append((*ci)->palabraEncodeada);

		palabraDecodificadaAnterior = palabraDecodificada;
		resultado->push_back(palabraDecodificada);
	}

	return resultado;

}

//private
FrontCodedString* FrontCodedString::frontCode(string* palabraAnterior,
		string* palabraAEncodear) {
	FrontCodedString* resultado = new FrontCodedString();
	short int sizePalabraActual = palabraAEncodear->length();

	short int i = 0;
	while ((i + 1) <= palabraAnterior->length() && (i + 1)
			<= sizePalabraActual) {
		if (((*palabraAEncodear)[i]) == (*palabraAnterior)[i]) {
			i++;
		} else
			break;
	}
	resultado->cantidadLetrasPalabraAnterior = i;
	resultado->cantidadLetrasPalabraActual = (sizePalabraActual - i);
	resultado->palabraEncodeada = palabraAEncodear->substr(resultado->cantidadLetrasPalabraAnterior,
			cantidadLetrasPalabraActual-1);

	return resultado;

}

FrontCodedString::~FrontCodedString() {
	// TODO Auto-generated destructor stub
}

short int FrontCodedString::getCantidadLetrasPalabraActual() const {
	return cantidadLetrasPalabraActual;
}

short int FrontCodedString::getCantidadLetrasPalabraAnterior() const {
	return cantidadLetrasPalabraAnterior;
}

string FrontCodedString::getPalabraEncodeada() const {
	return palabraEncodeada;
}

void FrontCodedString::setCantidadLetrasPalabraActual(
		short int cantidadLetrasPalabraActual) {
	this->cantidadLetrasPalabraActual = cantidadLetrasPalabraActual;
}

void FrontCodedString::setCantidadLetrasPalabraAnterior(
		short int cantidadLetrasPalabraAnterior) {
	this->cantidadLetrasPalabraAnterior = cantidadLetrasPalabraAnterior;
}

void FrontCodedString::setPalabraEncodeada(string palabraEncodeada) {
	this->palabraEncodeada = palabraEncodeada;
}

