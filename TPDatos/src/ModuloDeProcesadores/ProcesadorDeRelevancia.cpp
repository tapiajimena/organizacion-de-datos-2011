/*
 * ProcesadorDeRelevancia.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 */

#include "ProcesadorDeRelevancia.h"

//Public
ProcesadorDeRelevancia::ProcesadorDeRelevancia(){
}

ProcesadorDeRelevancia::ProcesadorDeRelevancia(ControladorIndice* controladorIndice, ArchivoTerminos* archivoTerminos){
	this->controladorIndice = controladorIndice;
	this->archivoTerminos = archivoTerminos;
	this->calculadorDeNormas = new CalculadorDeNormas(controladorIndice, archivoTerminos);
}

ProcesadorDeRelevancia::~ProcesadorDeRelevancia(){
	delete (this->calculadorDeNormas); 
}

void ProcesadorDeRelevancia::mostrarLibrosRelevantes(string consulta){
	list<Termino*>* terminos = generarTerminosAPartirDeConsulta(consulta);
	
	
	//Obtengo Libros Relevantes por Proximidad
	list<uint32_t>* librosRelevantesPorProximidad = obtenerLibrosResultadoPorProximidadDeLaConsulta(terminos);
	list<TriadaConsultaPorProximidad*>* resultadoPorProximidad = new list<TriadaConsultaPorProximidad*>();
	list<TriadaConsultaPorProximidad*>::const_iterator ci_triada;
	if (librosRelevantesPorProximidad->size() > 0){
		//no puede existir proxididad con otro termino
		//si solo se busca uno xD	
		if (terminos->size() > 1){
			delete (resultadoPorProximidad);
			resultadoPorProximidad = obtenerTriadasConsultaPorProximidad(librosRelevantesPorProximidad, terminos);
	
			//Muestro Resultado Por Proximidad
			cout<<"---Resultado Por Proximidad---"<<endl<<endl;
			for (ci_triada = resultadoPorProximidad->begin();
				ci_triada != resultadoPorProximidad->end();
					++ci_triada){
				cout<<"'Id Libro': "<<(*ci_triada)->id_libro;
				cout<<" 'Orden': "<<(*ci_triada)->orden;
				cout<<" 'Proximidad': "<<(*ci_triada)->proximidad<<endl<<endl;
			}
		}
	
	}
	
	
	//Obtengo Libros Relevantes por Peso
	list<uint32_t>* librosRelevantesPorPeso = obtenerLibrosResultadoPorPesoDeLaConsulta(terminos);
	list<DuplaConsultaPorPeso*>* resultadoPorPeso = new list<DuplaConsultaPorPeso*>();
	list<DuplaConsultaPorPeso*>::const_iterator ci_dupla;
	if (librosRelevantesPorPeso->size() > 0) {
		delete (resultadoPorPeso);
		resultadoPorPeso = obtenerDuplasConsultaPorPeso(librosRelevantesPorPeso, terminos);
		 
		//Muestro Resultado Por Pesos
		cout<<"---Resultado Por Pesos---"<<endl<<endl;
		for (ci_dupla = resultadoPorPeso->begin();
			ci_dupla != resultadoPorPeso->end();
				++ci_dupla){
			cout<<"'Id Libro': "<<(*ci_dupla)->id_libro;
			cout<<" 'Similitud': "<<(*ci_dupla)->similitud<<endl<<endl;	
		}
	}
	
	//Libero Recursos
	list<Termino*>::const_iterator ci_termino;
	for(ci_termino=terminos->begin();
		ci_termino!=terminos->end();
			++ci_termino){
		delete (*ci_termino);
	}
	delete (terminos);
	delete (librosRelevantesPorProximidad);
	delete (librosRelevantesPorPeso);
	
	for (ci_triada = resultadoPorProximidad->begin();
		ci_triada != resultadoPorProximidad->end();
			++ci_triada){
		delete (*ci_triada);
	}
	delete (resultadoPorProximidad);
	
	
	for (ci_dupla = resultadoPorPeso->begin();
		ci_dupla != resultadoPorPeso->end();
			++ci_dupla){
		delete (*ci_dupla);
	}
	delete (resultadoPorPeso);
}


//Private
Termino* ProcesadorDeRelevancia::obtenerTermino(string nombre){
	
	list<DatoTriada*>* triadasTermino = this->controladorIndice->recuperarTriadas(nombre);
	
	Termino* termino = new Termino(nombre, triadasTermino);

	return termino;
}

list<Termino*>* ProcesadorDeRelevancia::generarTerminosAPartirDeConsulta(string consulta){

	Termino* terminoAux = NULL;
	list<Termino*>* terminosDeLaConsulta = new list<Termino*>();

	char* nombreTerminos;
	char* nombreTermino;

	nombreTerminos = new char[consulta.size() + 1];
	strcpy(nombreTerminos, consulta.c_str());

	nombreTermino = strtok(nombreTerminos, " ,.-");
	while (nombreTermino != NULL) {
		terminoAux = this->obtenerTermino(nombreTermino);
		terminosDeLaConsulta->push_back(terminoAux);
		nombreTermino = strtok(NULL, " ,.-");
	}
	
	delete[] nombreTerminos;
		
	return terminosDeLaConsulta;
}

list<uint32_t>* ProcesadorDeRelevancia::obtenerLibrosResultadoDeLaConsulta(list<Termino*>* terminos){
	
	
	list<Termino*>* terminosDeLaConsulta = terminos;
	list<Termino*>::const_iterator ci_terminoDeLaConsulta;
		
	list<uint32_t>* librosResultado = new list<uint32_t>();
	list<uint32_t>::const_iterator ci_libroResultado;

	list<uint32_t>* librosAux = NULL;
	for (ci_terminoDeLaConsulta = terminosDeLaConsulta->begin();
		ci_terminoDeLaConsulta != terminosDeLaConsulta->end();
			++ci_terminoDeLaConsulta) {

		librosAux = (*ci_terminoDeLaConsulta)->obtenerLibros();
		for (ci_libroResultado	= librosAux->begin();
			ci_libroResultado != librosAux->end();
				++ci_libroResultado) {
		
			librosResultado->push_back((*ci_libroResultado));
			
		}
		delete (librosAux);

	}
	librosResultado->sort();
	librosResultado->unique();				
	
	return librosResultado;
}

list<uint32_t>* ProcesadorDeRelevancia::obtenerLibrosResultadoPorProximidadDeLaConsulta(list<Termino*>* terminos){

	list<Termino*>* terminosDeLaConsulta = terminos;
	list<Termino*>::const_iterator ci_terminoDeLaConsulta;
	
	list<uint32_t>* librosResultado = this->obtenerLibrosResultadoDeLaConsulta(terminos);
	list<uint32_t>::const_iterator ci_libroResultado;
	
	list<uint32_t>* librosBusquedaPorProximidad = new list<uint32_t>();

	bool libroContieneTodosLosTerminosDeLaConsulta = true;
	for (ci_libroResultado = librosResultado->begin();
		ci_libroResultado != librosResultado->end();
			++ci_libroResultado) {

		libroContieneTodosLosTerminosDeLaConsulta = true;
		for (ci_terminoDeLaConsulta = terminosDeLaConsulta->begin();
			ci_terminoDeLaConsulta != terminosDeLaConsulta->end();
				++ci_terminoDeLaConsulta) {
			if (libroContieneTodosLosTerminosDeLaConsulta){
				libroContieneTodosLosTerminosDeLaConsulta = 
				(*ci_terminoDeLaConsulta)->estaEnLibro(*ci_libroResultado);
			}
		}

		if (libroContieneTodosLosTerminosDeLaConsulta) {
			librosBusquedaPorProximidad->push_back(*ci_libroResultado);
		}

	}
					
	delete (librosResultado);	
	return librosBusquedaPorProximidad;
}

list<uint32_t>* ProcesadorDeRelevancia::obtenerLibrosResultadoPorPesoDeLaConsulta(list<Termino*>* terminos){

	list<Termino*>* terminosDeLaConsulta = terminos;
	list<Termino*>::const_iterator ci_terminoDeLaConsulta;
	
	list<uint32_t>* librosResultado = this->obtenerLibrosResultadoDeLaConsulta(terminos);
	list<uint32_t>::const_iterator ci_libroResultado;
	
	list<uint32_t>* librosBusquedaPorPeso = new list<uint32_t>();

	bool libroContieneTodosLosTerminosDeLaConsulta = true;
	for (ci_libroResultado = librosResultado->begin();
		ci_libroResultado != librosResultado->end();
			++ci_libroResultado) {

		libroContieneTodosLosTerminosDeLaConsulta = true;
		for (ci_terminoDeLaConsulta = terminosDeLaConsulta->begin();
			ci_terminoDeLaConsulta	!= terminosDeLaConsulta->end();
				++ci_terminoDeLaConsulta) {
			if(libroContieneTodosLosTerminosDeLaConsulta){	
				libroContieneTodosLosTerminosDeLaConsulta
					= (*ci_terminoDeLaConsulta)->estaEnLibro(*ci_libroResultado);
			}
		}

		if ((!libroContieneTodosLosTerminosDeLaConsulta) || (terminos->size() == 1)) {
			librosBusquedaPorPeso->push_back(*ci_libroResultado);
		}
	}				
	
	delete (librosResultado);
	
	return librosBusquedaPorPeso;
}

list<PosicionesMasProximasTermino*>* ProcesadorDeRelevancia::obtenerPosicionesMasProximasTerminosEnLibro(uint32_t id_libro, list<Termino*>* terminos){

	list<PosicionesMasProximasTermino*>* posicionesMasProximasTerminos = new list<PosicionesMasProximasTermino*>();

	PosicionesMasProximasTermino* posicionesMasProximasTermino = NULL;
	Termino* terminoAnterior = NULL;
	Termino* terminoPosterior = NULL;
	
	list<Termino*>* terminosDeLaConsulta = terminos;
	list<Termino*>::const_iterator ci_terminoDeLaConsulta;
	
	//caso especial en que la cantidad de terminos de la
	//consulta es igual a 2, eso implica que no se puede
	//iterar por los terminos internos de la consulta. :S
	if (terminosDeLaConsulta->size() == 2){
		posicionesMasProximasTermino =
			terminos->front()->obtenerMejoresPosiciones(id_libro, (Termino*)terminos->front(),(Termino*)terminos->back());
		posicionesMasProximasTerminos->push_back(posicionesMasProximasTermino);
		
	} else {
	 
		for (ci_terminoDeLaConsulta = ++terminosDeLaConsulta->begin();
			ci_terminoDeLaConsulta	!= --terminosDeLaConsulta->end();
				++ci_terminoDeLaConsulta) {
		
			terminoPosterior = (*(++ci_terminoDeLaConsulta));
			--ci_terminoDeLaConsulta;
			terminoAnterior = (*(--ci_terminoDeLaConsulta));
			++ci_terminoDeLaConsulta;
		
			posicionesMasProximasTermino =
				(*ci_terminoDeLaConsulta)->obtenerMejoresPosiciones(id_libro,(Termino*) terminoAnterior,(Termino*) terminoPosterior);

			posicionesMasProximasTerminos->push_back(posicionesMasProximasTermino);
		}
	}

	return posicionesMasProximasTerminos;
} 

TriadaConsultaPorProximidad* ProcesadorDeRelevancia::obtenerTriadaConsultaPorProximidad(uint32_t id_libro, list<PosicionesMasProximasTermino*>* posiciones){
	TriadaConsultaPorProximidad* triadaDeProximidad = new TriadaConsultaPorProximidad;
	
	triadaDeProximidad->id_libro = id_libro;
	triadaDeProximidad->orden = 0;
	triadaDeProximidad->proximidad = 0;
	
	long posicionMasProximaTerminoAnteriorActual = 0;
	long posicionMasProximaTerminoPosteriorActual = 0;
	
	list<PosicionesMasProximasTermino*>* posicionesMasProximasTerminos = posiciones;
	list<PosicionesMasProximasTermino*>::const_iterator ci_posicionesMasProximasTermino;
	for (ci_posicionesMasProximasTermino = posicionesMasProximasTerminos->begin();
		ci_posicionesMasProximasTermino	!= posicionesMasProximasTerminos->end();
			++ci_posicionesMasProximasTermino) {
		
		posicionMasProximaTerminoAnteriorActual
				= (*ci_posicionesMasProximasTermino)->posicionMasProximaTerminoAnterior;
		posicionMasProximaTerminoPosteriorActual
				= (*ci_posicionesMasProximasTermino)->posicionMasProximaTerminoPosterior;
				
		if (posicionMasProximaTerminoPosteriorActual != -1 && posicionMasProximaTerminoAnteriorActual != -1) {
		
			triadaDeProximidad->proximidad += ((double)1/(double)(
				posicionMasProximaTerminoPosteriorActual - posicionMasProximaTerminoAnteriorActual));
			triadaDeProximidad->orden += 1;
			
		} else if (posicionMasProximaTerminoPosteriorActual == -1 && posicionMasProximaTerminoAnteriorActual == -1){
		
			triadaDeProximidad->proximidad += 0;
		
		} else if (posicionMasProximaTerminoAnteriorActual == -1) {
		
			triadaDeProximidad->proximidad += ((double)1/(double)(
				posicionMasProximaTerminoPosteriorActual - posicionMasProximaTerminoAnteriorActual));
				
		} else {
			triadaDeProximidad->proximidad += ((double)1/(double)(
				posicionMasProximaTerminoAnteriorActual - posicionMasProximaTerminoPosteriorActual));
		}
	}
		
	return triadaDeProximidad;
}

list<TriadaConsultaPorProximidad*>* ProcesadorDeRelevancia::obtenerTriadasConsultaPorProximidad(list<uint32_t>* libros, list<Termino*>* terminos){
	list<TriadaConsultaPorProximidad*>* triadasDeProximidad = new list<TriadaConsultaPorProximidad*>();
	
	list<PosicionesMasProximasTermino*>* posicionesMasProximasTerminos = NULL;
	list<PosicionesMasProximasTermino*>::const_iterator ci_posicionesMasProximasTermino;
	
	list<uint32_t>::const_iterator ci_libroBusquedaPorProximidad;
	for (ci_libroBusquedaPorProximidad = libros->begin();
		ci_libroBusquedaPorProximidad != libros->end();
			++ci_libroBusquedaPorProximidad){
			
		posicionesMasProximasTerminos = this->obtenerPosicionesMasProximasTerminosEnLibro(*ci_libroBusquedaPorProximidad, terminos);
		triadasDeProximidad->push_back(this->obtenerTriadaConsultaPorProximidad(*ci_libroBusquedaPorProximidad, posicionesMasProximasTerminos));
		
		for (ci_posicionesMasProximasTermino = posicionesMasProximasTerminos->begin();
			ci_posicionesMasProximasTermino != posicionesMasProximasTerminos->end();
				++ci_posicionesMasProximasTermino){
			delete (*ci_posicionesMasProximasTermino);
		}
		delete posicionesMasProximasTerminos;
	
	}
	
	triadasDeProximidad->sort(ComparadorTriadaConsultaPorProximidad());
	
	return triadasDeProximidad;
}

list<DuplaConsultaPorPeso*>* ProcesadorDeRelevancia::obtenerDuplasConsultaPorPeso(list<uint32_t>* libros, list<Termino*>* terminos){
	list<DuplaConsultaPorPeso*>* duplasConsultaPorPeso = new list<DuplaConsultaPorPeso*>();
	DuplaConsultaPorPeso* duplaAux = NULL;
	
	list<uint32_t>::const_iterator ci_libro;
	for (ci_libro = libros->begin();ci_libro != libros->end();++ci_libro){	
		duplaAux = new DuplaConsultaPorPeso;
		duplaAux->id_libro = (*ci_libro);
		duplaAux->similitud = this->calculadorDeNormas->calcularSimilitudConsultaConDocumento((*ci_libro), terminos);
		//duplaAux->similitud = this->calculadorDeNormas->calcularSimilitudConsultaConDocumento((*ci_libro), terminos);
		duplasConsultaPorPeso->push_back(duplaAux);
	}
	
	duplasConsultaPorPeso->sort(ComparadorDuplaConsultaPorPeso());
	
	return duplasConsultaPorPeso;
}
