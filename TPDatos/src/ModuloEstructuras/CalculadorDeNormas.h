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
#include "../../Common/Constantes.h"
#include "../../Common/Utilitarios/Logger.h"
#include "../../Common/Utilitarios/ServiceClass.h"
#include "../ModuloDeArchivos/ManejadorArchivo.h"
#include "../ModuloEstructuras/Configuracion.h"
#include "../ModuloControladores/ControladorTriadas.h"
#include "../ModuloControladores/ControladorIndice.h"
#include "../ModuloDeTipos/DatoTriada.h"
#include "../ModuloDeIndices/Hash/Hash.h"
#include "../ModuloDeTipos/Termino.h"

//TODO include para testing, sacar
//#include "../ModuloTesting/MockControladorIndice.h"

//Modelo de vector de documento.
//uint32_t: ID del t�rmino
//float: Peso Local del termino.
//De esta forma se evita definir un vector con tantas posiciones como t�rminos tengamos en el diccionario.
//Es algo m�s enredado para codificar, pero mucho m�s eficiente.
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

	std::vector<std::pair<std::string, uint32_t> > listaTerminos;

	//METODOS PRIVADOS---------------------------------------------------

	//Crea los archivos de indice vacios, para descartar cosas que tuvieran antes.
	//...cada vez que se ingresa un libro estos indices pierden validez y hay que vaciarlos.
	void reiniciarIndices();

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

	//Devuelve true si el termino (string) esta en la lista de terminos de los libros y
	//carga su id cargado en la variable idTermino.
	//Se asume que en la creacion y destruccion de esta clase no se agregan terminos.
	bool buscarTerminoEnBiblioteca(string termino, uint32_t &idTermino);

	uint32_t obtenerIdTermino(string termino);

	//PESO LOCAL DE TERMINO
	//Se usa para las consultas de similitud, con las normas ya calculadas y guardadas en un archivo.
	float calcularPesoLocalDeTermino(uint32_t idDocumento, uint32_t idTermino);

	//Calcula el producto interno de dos vectores de documento (la consulta es tambien un vector de documento)
	float calcularProductoInterno(VectorDeDocumento* vectorDocumento1, VectorDeDocumento* vectorDocumento2);

	//Genera un �ndice de tipo Hash con todos los pesos globales de los t�rminos.
	void generarIndiceDePesosGlobalesDeTerminos();

	//Toma una lista de elementos Termino* y carga un nuevo vector de documento
	VectorDeDocumento* cargarVectorDeTerminos(std::list<Termino*>* listaTerminos);

	//Este toma el Id de documento, levanta sus triadas y carga el vector.
	VectorDeDocumento* cargarVectorDeTerminos(uint32_t idDocumento);

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

	//Devuelve el coseno del �ngulo vectorial entre dos documentos o...
	//... un documento y una consulta (la consulta se toma como documento de pocos terminos)
	float calcularSimilitudConsultaConDocumento(uint32_t idDocumento, std::list<Termino*>* consulta);


	void generarArchivoDeNormasDeDocumentos();

	//Busca en el archivo de normas la norma del documento por id. Se debe haber generado el archivo de
	//normas en una corrida anterior. Si el archivo de normas no existe o el idDocumento no est� en �l, devuelve cero.
	//float obtenerNormaDocumentoIndexada();

	void generarReporteDeNormas(std::list<uint32_t> listaDocumentos);
};

#endif /* CALCULADORDENORMAS_H_ */

