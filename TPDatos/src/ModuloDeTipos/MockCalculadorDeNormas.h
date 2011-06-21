
#ifndef MOCK_CALCULADOR_DE_NORMAS_H_
#define MOCK_CALCULADOR_DE_NORMAS_H_

#include "../ModuloControladores/ControladorIndice.h"
#include "../ModuloDeArchivos/ArchivoTerminos.h"
#include "Termino.h"

#include <stdlib.h>
#include <time.h>


class CalculadorDeNormas {

private:
	ControladorIndice* controladorIndice;
	ArchivoTerminos* archivoTerminos;

public:
	CalculadorDeNormas(ControladorIndice* controladorIndice, ArchivoTerminos* archivoTerminos);
	
	float calcularSimilitudConsultaConDocumento(uint32_t documento, list<Termino*>* consulta);
	
	virtual ~CalculadorDeNormas();
};

#endif /* MOCK_CALCULADOR_DE_NORMAS_H_ */


