/*
 *
 * CalculadorDeNormas.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
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
//TODO sacar ControladorBiblioteca y usar a ControladorTriadas para obtener Ids de libros.
//#include "../ModuloControladores/ControladorBiblioteca.h"
#include "../ModuloDeTipos/DatoTriada.h"
#include "../ModuloDeIndices/Hash/Hash.h"
#include "../ModuloDeTipos/Termino.h"

//TODO include para testing, sacar
#include "../ModuloTesting/MockControladorIndice.h"

//Modelo de vector de documento.
//uint32_t: ID del término
//float: Peso Local del termino.
//De esta forma se evita definir un vector con tantas posiciones como términos tengamos en el diccionario.
//Es algo más enredado para codificar, pero mucho más eficiente.
typedef std::map<uint32_t, float> VectorDeDocumento;

class CalculadorDeNormas {
private:
	//ATRIBUTOS----------------------------------------------------------

	//path de trabajo
	string		pathCarpeta;

	//ControladorTriadas* controladorDeTriadas;

	ControladorIndice* controladorIndice;

	Hash* indicePesosGlobales;

	Hash* indiceNormasDocumentos;

	std::string nombreArchivoTablaPesos;
	std::string nombreArchivoCubetasPesos;

	std::string nombreArchivoTablaNormas;
	std::string nombreArchivoCubetasNormas;

	//Se usa solo para generar indices:
	ArchivoTerminos* archivoTerminos;

	int cantidadTotalDeDocumentos; //Se carga al calcular e indexar pesos globales de terminos

	//METODOS PRIVADOS---------------------------------------------------

	//Crea los archivos de indice vacios, para descartar cosas que tuvieran antes.
	//...cada vez que se ingresa un libro estos indices pierden validez y hay que vaciarlos.
	void reiniciarIndices();

	//Accede al índice de tríadas y levanta todas las ocurrencias de un término
	std::list<DatoTriada*>* levantarTriadasDeTermino(uint32_t idTermino);

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

	//Calcula el producto interno de dos vectores de documento (la consulta es tambien un vector de documento)
	float calcularProductoInterno(VectorDeDocumento* vectorDocumento1, VectorDeDocumento* vectorDocumento2);

	//Genera un índice de tipo Hash con todos los pesos globales de los términos.
	void generarIndiceDePesosGlobalesDeTerminos();

	//Toma una lista de elementos Termino* y carga un nuevo vector de documento
	VectorDeDocumento* cargarVectorDeTerminos(std::list<Termino*>* listaTerminos);

	//Este toma el Id de documento, levanta sus triadas y carga el vector.
	VectorDeDocumento* cargarVectorDeTerminos(uint32_t idDocumento);

	//Calcula la norma de un documento (deprecated)
	//float calcularNormaDeDocumento(uint32_t idDocumento);

	//Tanto para documentos como para consultas.
	float calcularNormaVectorDeTerminos(VectorDeDocumento* vectorDeTerminos);

	//Multiplica las posiciones del vector de documento por el peso global del termino
	//Se llama aparte de cargarVectorDeTerminos porque se pondera para calcular similitudes,
	//pero no de la misma manera para calcular las normas.
	void ponderarPesoLocal(VectorDeDocumento* vectorDocumento);

public:
	//CalculadorDeNormas(ControladorIndice* controladorIndice, ControladorTriadas* controladorDeTriadas, ArchivoTerminos* archivoTerminos);
	CalculadorDeNormas(ControladorIndice* controladorIndice, ArchivoTerminos* archivoTerminos);

	virtual ~CalculadorDeNormas();

	//Devuelve el coseno del ángulo vectorial entre dos documentos o...
	//... un documento y una consulta (la consulta se toma como documento de pocos terminos)
	float calcularSimilitudConsultaDocumento(uint32_t idDocumento, std::list<Termino*>* consulta);

	//TODO limpiar encabezado
	void generarArchivoDeNormasDeDocumentos();//ControladorBiblioteca* controladorBiblioteca);

	//Busca en el archivo de normas la norma del documento por id. Se debe haber generado el archivo de
	//normas en una corrida anterior. Si el archivo de normas no existe o el idDocumento no está en él, devuelve cero.
	float obtenerNormaDocumentoIndexada();
};

#endif /* CALCULADORDENORMAS_H_ */
