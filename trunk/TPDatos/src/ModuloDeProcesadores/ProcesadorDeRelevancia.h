/*
 * ProcesadorDeRelevancia.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 */


#ifndef PROCESADOR_DE_RELEVANCIA_H_
#define PROCESADOR_DE_RELEVANCIA_H_

#include "../ModuloControladores/ControladorIndice.h"
#include "../ModuloDeArchivos/ArchivoTerminos.h"
#include "../ModuloDeTipos/MockCalculadorDeNormas.h"
#include "../ModuloDeTipos/Termino.h"
#include "../ModuloDeTipos/DuplaConsultaPorPeso.h"
#include "../ModuloDeTipos/TriadaConsultaPorProximidad.h"
//#include "../ModuloEstructuras/CalculadorDeNormas.h"

#include <iostream>
#include <list>
#include <string.h>
#include <stdint.h>



using namespace std;
class ProcesadorDeRelevancia {

private:
	ControladorIndice* controladorIndice;
	ArchivoTerminos* archivoTerminos;
	CalculadorDeNormas* calculadorDeNormas;
	
	Termino* obtenerTermino(string nombre);
	list<Termino*>* generarTerminosAPartirDeConsulta(string consulta);
	list<uint32_t>* obtenerLibrosResultadoDeLaConsulta(list<Termino*>* terminos);
	list<uint32_t>* obtenerLibrosResultadoPorProximidadDeLaConsulta(list<Termino*>* terminos);
	list<uint32_t>* obtenerLibrosResultadoPorPesoDeLaConsulta(list<Termino*>* terminos);
	list<PosicionesMasProximasTermino*>* obtenerPosicionesMasProximasTerminosEnLibro(uint32_t id_libro, list<Termino*>* terminos);
	TriadaConsultaPorProximidad* obtenerTriadaConsultaPorProximidad(uint32_t id_libro, list<PosicionesMasProximasTermino*>* posiciones);
	list<TriadaConsultaPorProximidad*>* obtenerTriadasConsultaPorProximidad(list<uint32_t>* libros, list<Termino*>* terminos);
	list<DuplaConsultaPorPeso*>* obtenerDuplasConsultaPorPeso(list<uint32_t>* libros, list<Termino*>* terminos);
	

public:

	ProcesadorDeRelevancia();
	
	ProcesadorDeRelevancia(ControladorIndice* controladorIndice, ArchivoTerminos* archivoTerminos);
	
	void mostrarLibrosRelevantes(string consulta);
	
	virtual ~ProcesadorDeRelevancia();

};

#endif /* PROCESADOR_DE_RELEVANCIA_H_ */
