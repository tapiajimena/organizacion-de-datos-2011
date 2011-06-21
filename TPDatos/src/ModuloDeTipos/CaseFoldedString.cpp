/*
 * CaseFoldedString.cpp
 *  
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *      
 *  
 *      
 *      
 */

#include "CaseFoldedString.h"

CaseFoldedString::CaseFoldedString() {


}

/*
//USANDO QT
string CaseFoldedString::caseFoldWord(string word)
{
	string str;
	QChar qChar;
	QByteArray vec;
	QString rdo, latin,rdo2;
	QString aux(word.c_str());


	rdo = aux.normalized(QString::NormalizationForm_D,QChar::Unicode_5_0);
	rdo = rdo.toCaseFolded();


    for (int i=0; i < rdo.size(); i++)
    {
    	qChar = rdo.at(i);
    	if ( (qChar.isLetterOrNumber()) || (qChar.isSpace()) || (qChar =='-')|| (qChar =='&'))
    		str+= qChar.toAscii();
    }

    return str;
}
*/

string CaseFoldedString::caseFoldWord(string word)
{
	word = ServiceClass::toDowncase(word);
	word = ServiceClass::normalizarString(word);

	return word;
}


CaseFoldedString::~CaseFoldedString()
{

}
