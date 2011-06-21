/*
 * Instruccion_ConsultarTerminosProximos.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "Instruccion_ConsultarTerminosProximos.h"


Instruccion_ConsultarTerminosProximos::Instruccion_ConsultarTerminosProximos(char id, string consulta):Instruccion(id)
{
	this->titulo = consulta;
}


void Instruccion_ConsultarTerminosProximos::ejecutar()
{
	CaseFoldedString caseFold = CaseFoldedString();
	Configuracion* conf = Configuracion::GetInstancia();
	ConsultaIndice* consulta = new ConsultaIndice(conf->getPathCarpetaTrabajo());

	Logger::log("Instruccion_ConsultarTerminosProximos", "ejecutar",
			"Se ejecuta la consulta.");

	if(consulta->esConsultable()){

		DatoLibro* datoLibro = new DatoLibro(caseFold.caseFoldWord(titulo)+" ");
		Libro* libro = new Libro();
		ParserDeOcurrenciasDeTerminos* parser = new ParserDeOcurrenciasDeTerminos(conf->getPathArchivoStopWords());
		libro = parser->parsear(datoLibro);

		string consultaTerminos = "";

		vector<string> palabras = libro->getOcurrenciasDeTerminos();
		vector<string>::const_iterator it_map;

		for(it_map=palabras.begin();it_map!=palabras.end();++it_map){
			consultaTerminos += (*it_map);
			consultaTerminos += " ";

		}

		if (consultaTerminos.length() > 3)
			consulta->consultarTerminosProximos(consultaTerminos);
		else
			cout<<CARACTER_TAB<<"Verifique que la consulta busque palabras con mas significados."<<endl<<endl;

		delete(datoLibro);
		delete(libro);
		delete(parser);
	}
	else
		cout<<MENSAJE_INDICE_NO_CONSULTABLE<<endl;

	Logger::log("Instruccion_ConsultarTerminosProximos", "ejecutar",
			"Se devuelve la consulta.");
	delete(consulta);
}

Instruccion_ConsultarTerminosProximos::~Instruccion_ConsultarTerminosProximos() {

}
