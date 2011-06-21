/*
 * CaseFoldedString.h
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#ifndef CASEFOLDEDSTRING_H_
#define CASEFOLDEDSTRING_H_

#include <iostream>
#include <string>
#include "./Common/Utilitarios/ServiceClass.h"
//#include <QString>
//#include <qtextstream.h>


using namespace std;
class CaseFoldedString
{
private:
	string palabraFoldeada;
public:
	CaseFoldedString();

	string caseFoldWord(string word);

	virtual ~CaseFoldedString();
};

#endif /* CASEFOLDEDSTRING_H_ */
