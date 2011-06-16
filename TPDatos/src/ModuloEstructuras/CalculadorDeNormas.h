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
#include "../ModuloControladores/ControladorTriadas.h"
#include "../ModuloControladores/ControladorIndice.h"
#include "../ModuloDeTipos/DatoTriada.h"
#include "../ModuloDeIndices/Hash/Hash.h"

class CalculadorDeNormas {
private:
	//ATRIBUTOS----------------------------------------------------------

	//path de trabajo
	string		pathCarpeta;

	ControladorTriadas* controladorDeTriadas;

	ControladorIndice* controladorIndice;

	int cantidadTotalDeDocumentos;

	//METODOS PRIVADOS---------------------------------------------------

	std::vector<DatoTriada> levantarTriadasDeTermino(uint32_t idTermino);

	//Devuelve la cantidad total de documentos que contienen al menos una vez un término
	//También llamado "FRECUENCIA GLOBAL DE TERMINO" (cantidad de documentos en que aparece)
	int calcularDocumentosQueContienenTermino(uint32_t idTermino);

	//PESO GLOBAL DE TERMINO
	float calcularPesoGlobalDeTermino(uint32_t idTermino);

	//Devuelve la cantidad total de apariciones de un documento en un término.
	//También llamado "FRECUENCIA LOCAL DE TERMINO" de un documento.
	int calcularAparicionesDeTerminoEnDocumento(uint32_t idDocumento, uint32_t idTermino);

	//PESO LOCAL DE TERMINO
	//Se usa para las consultas de similitud, con las normas ya calculadas y guardadas en un archivo.
	float calcularPesoLocalDeTermino(uint32_t idDocumento, uint32_t idTermino);

	float calcularProductoInterno(uint32_t idDocumento, std::string consulta);

	float obtenerNormaDocumento(uint32_t idDocumento);

	float obtenerNormaConsulta(std::string consulta);

public:
	CalculadorDeNormas(ControladorIndice* controladorIndice, ControladorTriadas* controladorDeTriadas);

	virtual ~CalculadorDeNormas();

	//Devuelve el coseno del ángulo vectorial entre dos documentos o...
	//... un documento y una consulta (la consulta se toma como documento de pocos terminos)
	float calcularSimilitudConsultaDocumento(uint32_t idDocumento, std::vector<std::string> consulta);

	//Calcula la norma de un documento
	float calcularNormaDeDocumento(uint32_t idDocumento);
};

#endif /* CALCULADORDENORMAS_H_ */
