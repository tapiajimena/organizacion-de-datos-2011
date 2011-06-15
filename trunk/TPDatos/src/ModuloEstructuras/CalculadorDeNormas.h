/*
 * CalculadorDeNormas.h
 *
 *  Created on: 14/06/2011
 *      Author: santi
 */

#ifndef CALCULADORDENORMAS_H_
#define CALCULADORDENORMAS_H_

#include <stdint.h>
#include <math.h>
#include "../../Common/Utilitarios/ServiceClass.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"
#include "../ModuloEstructuras/Configuracion.h"
//#include "../ModuloDeIndices/Hash/Hash.h"
//arbol B+ (indice de triadas).
//algo de las triadas... (Jime)


class CalculadorDeNormas {
private:
	//path de trabajo
	string		pathCarpeta;

	int cantidadTotalDeDocumentos;

	//Devuelve la cantidad total de documentos que contienen al menos una vez un término
	int calcularDocumentosQueContienenTermino(uint32_t idTermino);

	int calcularAparicionesDeTerminoEnDocumento(uint32_t idDocumento, uint32_t idTermino);

	int calcularNormaDeDocumeto(uint32_t idDocumento);

	//Devuelve el coseno del ángulo vectorial entre dos documentos o...
	//... un documento y una consulta (la consulta se toma como documento de pocos terminos)
	float calcularSimilitudConsultaDocumento(uint32_t idDocumento, std::vector<std::string> consulta);

public:
	CalculadorDeNormas();
	virtual ~CalculadorDeNormas();
};

#endif /* CALCULADORDENORMAS_H_ */
