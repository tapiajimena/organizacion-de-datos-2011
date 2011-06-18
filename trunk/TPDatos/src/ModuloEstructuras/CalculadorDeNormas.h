/*
 * CalculadorDeNormas.h
 *
 *  Created on: 14/06/2011
 *      Author: santi
 */

#ifndef CALCULADORDENORMAS_H_
#define CALCULADORDENORMAS_H_

#include <stdint.h>
#include <string>
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

	Hash* indicePesosGlobales;

	Hash* indiceNormasDocumentos;

	//Se usa solo para generar indices:
	ArchivoTerminos* archivoTerminos;

	int cantidadTotalDeDocumentos; //Se carga al calcular e indexar pesos globales de terminos

	//METODOS PRIVADOS---------------------------------------------------

	//Accede al índice de tríadas y levanta todas las ocurrencias de un término
	std::vector<DatoTriada> levantarTriadasDeTermino(uint32_t idTermino);

	//Devuelve la cantidad total de documentos que contienen al menos una vez un término
	//También llamado "FRECUENCIA GLOBAL DE TERMINO" (cantidad de documentos en que aparece)
	int calcularDocumentosQueContienenTermino(uint32_t idTermino);

	//PESO GLOBAL DE TERMINO
	float calcularPesoGlobalDeTermino(uint32_t idTermino);

	//Devuelve la cantidad total de apariciones de un documento en un término.
	//También llamado "FRECUENCIA LOCAL DE TERMINO" de un documento.
	int calcularAparicionesDeTerminoEnDocumento(uint32_t idDocumento, uint32_t idTermino);

	//Consulta el índice de pesos globales y devuelve el del término. Si no está registrado, devuelve 0
	float obtenerPesoGlobalDeIndice(uint32_t idTermino);

	//Consulta el índice de normas y devuelve la del documento. Si no está registrado, devuelve 0
	float obtenerNormaDocumentoDeIndice(uint32_t idDocumento);

	//PESO LOCAL DE TERMINO
	//Se usa para las consultas de similitud, con las normas ya calculadas y guardadas en un archivo.
	float calcularPesoLocalDeTermino(uint32_t idDocumento, uint32_t idTermino);

	float calcularProductoInterno(uint32_t idDocumento, std::string consulta);

	//Genera un índice de tipo Hash con todos los pesos globales de los términos.
	void generarIndiceDePesosGlobalesDeTerminos();

	//Calcula la norma de un documento
	float calcularNormaDeDocumento(uint32_t idDocumento);

	float calcularNormaConsulta(std::list<uint32_t> consulta);

public:
	CalculadorDeNormas(ControladorIndice* controladorIndice, ControladorTriadas* controladorDeTriadas, ArchivoTerminos* archivoTerminos);

	virtual ~CalculadorDeNormas();

	//Devuelve el coseno del ángulo vectorial entre dos documentos o...
	//... un documento y una consulta (la consulta se toma como documento de pocos terminos)
	float calcularSimilitudConsultaDocumento(uint32_t idDocumento, std::list<uint32_t> consulta);

	void generarArchivoDeNormasDeDocumentos();

	//Busca en el archivo de normas la norma del documento por id. Se debe haber generado el archivo de
	//normas en una corrida anterior. Si el archivo de normas no existe o el idDocumento no está en él, devuelve cero.
	float obtenerNormaDocumentoIndexada();
};

#endif /* CALCULADORDENORMAS_H_ */
