
#include "MockCalculadorDeNormas.h"


CalculadorDeNormas::CalculadorDeNormas(ControladorIndice* controladorIndice, ArchivoTerminos* archivoTerminos){
	this->controladorIndice = controladorIndice;
	this->archivoTerminos = archivoTerminos;
	
	srand(time(NULL));
}

CalculadorDeNormas::~CalculadorDeNormas(){

}

float CalculadorDeNormas::calcularSimilitudConsultaConDocumento(uint32_t id_documento, list<Termino*>* consulta){
	
	list<Termino*>* terminosConsulta = consulta;
	list<Termino*>* terminosDocumento  = NULL;

	return (float)rand()/(float)RAND_MAX;
	
}


