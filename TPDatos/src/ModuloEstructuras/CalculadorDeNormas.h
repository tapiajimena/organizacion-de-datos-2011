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

//Modelo de vector de documento.
//uint32_t: ID del t�rmino
//int: cantidad de apariciones del t�rmino en el documento.
//De esta forma se evita definir un vector con tantas posiciones como t�rminos tengamos en el diccionario.
//Es algo m�s enredado para codificar, pero mucho m�s eficiente.
typedef std::map<uint32_t, int> VectorDeDocumento;

class CalculadorDeNormas {
private:
	//ATRIBUTOS----------------------------------------------------------

	//path de trabajo
	string		pathCarpeta;

	//ControladorTriadas* controladorDeTriadas;

	ControladorIndice* controladorIndice;

	Hash* indicePesosGlobales;

	Hash* indiceNormasDocumentos;

	//Se usa solo para generar indices:
	ArchivoTerminos* archivoTerminos;

	int cantidadTotalDeDocumentos; //Se carga al calcular e indexar pesos globales de terminos

	//METODOS PRIVADOS---------------------------------------------------

	//Accede al �ndice de tr�adas y levanta todas las ocurrencias de un t�rmino
	std::list<DatoTriada*>* levantarTriadasDeTermino(uint32_t idTermino);

	//Devuelve la cantidad total de documentos que contienen al menos una vez un t�rmino
	//Tambi�n llamado "FRECUENCIA GLOBAL DE TERMINO" (cantidad de documentos en que aparece)
	int calcularDocumentosQueContienenTermino(uint32_t idTermino);

	//PESO GLOBAL DE TERMINO
	float calcularPesoGlobalDeTermino(uint32_t idTermino);

	//Devuelve la cantidad total de apariciones de un documento en un t�rmino.
	//Tambi�n llamado "FRECUENCIA LOCAL DE TERMINO" de un documento.
	int calcularAparicionesDeTerminoEnDocumento(uint32_t idDocumento, uint32_t idTermino);

	//Consulta el �ndice de pesos globales y devuelve el del t�rmino. Si no est� registrado, devuelve 0
	float obtenerPesoGlobalDeIndice(uint32_t idTermino);

	//Consulta el �ndice de normas y devuelve la del documento. Si no est� registrado, devuelve 0
	float obtenerNormaDocumentoDeIndice(uint32_t idDocumento);

	//PESO LOCAL DE TERMINO
	//Se usa para las consultas de similitud, con las normas ya calculadas y guardadas en un archivo.
	float calcularPesoLocalDeTermino(uint32_t idDocumento, uint32_t idTermino);

	//Calcula el producto interno de dos vectores de documento (la consulta es tambien un vector de documento)
	float calcularProductoInterno(VectorDeDocumento* vectorDocumento1, VectorDeDocumento* vectorDocumento2);

	//Genera un �ndice de tipo Hash con todos los pesos globales de los t�rminos.
	void generarIndiceDePesosGlobalesDeTerminos();

	//Se usa para documentos y consultas por igual.
	VectorDeDocumento* cargarVectorDeTerminos(std::list<uint32_t> ocurrenciasDeTerminos);

	//Este toma el Id de documento, levanta sus triadas y carga el vector.
	VectorDeDocumento* cargarVectorDeTerminos(uint32_t idDocumento);

	//Calcula la norma de un documento (deprecated)
	//float calcularNormaDeDocumento(uint32_t idDocumento);

	//Tanto para documentos como para consultas.
	float calcularNormaVectorDeTerminos(VectorDeDocumento* vectorDeTerminos);

public:
	//CalculadorDeNormas(ControladorIndice* controladorIndice, ControladorTriadas* controladorDeTriadas, ArchivoTerminos* archivoTerminos);
	CalculadorDeNormas(ControladorIndice* controladorIndice, ArchivoTerminos* archivoTerminos);

	virtual ~CalculadorDeNormas();

	//Devuelve el coseno del �ngulo vectorial entre dos documentos o...
	//... un documento y una consulta (la consulta se toma como documento de pocos terminos)
	float calcularSimilitudConsultaDocumento(uint32_t idDocumento, std::list<uint32_t> consulta);

	void generarArchivoDeNormasDeDocumentos();

	//Busca en el archivo de normas la norma del documento por id. Se debe haber generado el archivo de
	//normas en una corrida anterior. Si el archivo de normas no existe o el idDocumento no est� en �l, devuelve cero.
	float obtenerNormaDocumentoIndexada();
};

#endif /* CALCULADORDENORMAS_H_ */